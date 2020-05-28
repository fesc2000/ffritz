# Generates application image for atom
#
# Options: 
#	CASH    relative path to cash tool
#	FFAD    relative path to ffad tool
#       NOSTRIP Set to 1 to not strip binaries (for debugging)
#
ARCHDIR=$(shell while test -f arch.mk && echo $$PWD && exit 0; test $$PWD != /; do cd ..; done)
include $(ARCHDIR)/../paths.mk

BR_TGT	    = $(realpath $(BUILDROOT)/output/target)
BR_TGT_LIB1 = $(BR_TGT)/lib
BR_TGT_LIB  = $(BR_TGT)/usr/lib
BR_TGT_BIN  = $(BR_TGT)/usr/bin
BR_TGT_SBIN = $(BR_TGT)/usr/sbin

BINFILES   += $(wildcard bin/*)
BINFILES   += $(wildcard $(CMNDIR)/ffritz/bin/*)
BINFILES   += $(wildcard $(CMNDIR)/ffritz/bin$(BR_VERSION)/*)
ETCFILES    = etc/ffritz-env.sh etc/mpd.conf etc/ff_atom_startup etc/ffservices etc/mkusers
ETCFILES   += etc/lirc_options_dfl.conf
ETCFILES   += etc/upmpdcli.conf-dist
ETCFILES   += etc/usrmount etc/fflogrotate etc/ffshutdown
ETCFILES   += etc/init.d
ETCFILES   += etc/shairport-sync.conf.dfl
ETCFILES   += etc/exports

## XXX binaries that seem to require /lib as first entry in /LD_LIBRARY_PATH
## This is the default for <= FritzOS 7.13 / BR2019-05.
## For FOS 7.19 / BR2020-02, it is not, except some exceptions
##
## Maybe this can be properly fixed once the 7.19 OS package is available.
# 
## OpenVPN/OpenSSL fails to initialize RNG otherwise
#
FFWRAP_FORCE_LIB += openvpn

OUTPUTDIR   = $(TOPDIR)/output$(BR_VERSION)
STAGEDIR    = $(OUTPUTDIR)/ffritz

BRCOPY       = $(STAGEDIR)/buildroot

VERSION     = $(shell cat version)

ifneq ($(BR_VERSION),-2019.05)
FOS_SUB_VERSION=19
endif

IMAGE       = ffritz-app-$(VERSION)-fos7$(FOS_SUB_VERSION).tar
CSUM	    = ffritz-app-$(VERSION)-fos7$(FOS_SUB_VERSION).sha256sum

-include conf.mk

ifeq ($(INSTDIR),)
    INSTDIR=$(STAGEDIR)
endif

ifeq ($(MODULES),)
MODULES   += nfs
MODULES   += bt
MODULES   += prtg
MODULES   += modules
MODULES   += wireguard-tools
MODULES   += shairport-sync
MODULES   += unfs
MODULES   += ftl
MODULES   += libmultid
MODULES   += pi-hole
endif

## Packages with (build/)install target
#
INSTDIRS   += src/install
INSTDIRS   += $(MODULES:%=../%/install)

ifeq ($(CASH),)
CASH=$(shell ls -d ../cash/build/.. 2>/dev/null)
endif

ifneq ($(CASH),)
SUBDIRS    += $(CASH)
INSTDIRS   += $(CASH)/install
endif

ifeq ($(FFAD),)
FFAD=$(shell ls -d ../ffad/build/.. 2>/dev/null)
endif

ifneq ($(FFAD),)
SUBDIRS    += $(FFAD)
INSTDIRS   += $(FFAD)/install
endif

ifeq ($(NOSTRIP),)
NOSTRIP	    = 1
endif

.PHONY:	$(SUBDIRS) $(INSTDIRS) $(IMAGE) $(INSTDIR)

all:	buildroot $(INSTDIR) $(SUBDIRS) $(IMAGE)

buildroot:
	make -C $(BRBUILDDIR)

$(INSTDIR):
	mkdir -p $(INSTDIR)
	rm -rf $(INSTDIR)/*
	mkdir -p $(INSTDIR)/etc
	mkdir -p $(INSTDIR)/bin
	mkdir -p $(INSTDIR)/share
	mkdir -p $(BRCOPY)
	cd $(BRCOPY); tar xf $(BR_TGT)/../images/rootfs.tar 
	cd $(INSTDIR); ln -s buildroot/usr/lib .

$(SUBDIRS):	
	mkdir -p $(DLDIR)
	make -C $@

$(INSTDIRS):
	make -C `dirname $@` install DESTDIR=$(STAGEDIR) INSTDIR=$(STAGEDIR)

$(IMAGE): ffimage.bin
	sha256sum ffimage.bin | sed -e 's/ .*//' > $(CSUM)
	cp ../../../*.md .
#	cp ../libdvbfi/README.txt README-dvb.txt 
#	cp ../libdvbfi/fwd .
	cp $(CSUM) ffimage.sha256sum
	tar cf $(IMAGE) ffimage.bin ffimage.sha256sum *.md glibc-version
	rm -f ffimage.sha256sum
	@echo
	@echo +++ DONE +++
	@echo "Atom image file: $(TOPDIR)/$(IMAGE)"
	@echo "Image checksum:  `cat $(CSUM)`"
	@echo

ffimage.bin: $(BINFILES) $(ETCFILES) stage
	rm -f $@
	cd $(OUTPUTDIR); mksquashfs ffritz ../$@ -all-root -no-progress -no-exports -no-sparse -b 65536 

# Install everything to target
# LD_LIBRARY_PATH needs to be set correctly for binaries. This is done by the ffwrap wrapper script,
# which is linked to for each binary. This makes the package position independent, i.e.
# it can be installed to /var/media/ftp, or integrated into the atom squashfs (to /usr/local).
#
stage: $(BINFILES) $(ETCFILES) $(INSTDIRS)
	cp -a $(BINFILES) $(INSTDIR)/bin
	cp -r $(ETCFILES) $(INSTDIR)/etc
	cp -ar etc/openvpn $(INSTDIR)/etc
	sed -i -e 's@^rundir=.*@rundir=/var/media/ftp/ffritz@' $(INSTDIR)/etc/ff_atom_startup
	cd $(BRCOPY)/usr/lib; ln -s ../../lib/libutil* . || true
	mv $(INSTDIR)/bin/ffwrap* $(BRCOPY)/usr/bin
	cp $(BRCOPY)/usr/bin/ffwrap* $(BRCOPY)/usr/sbin
	# Move our binaries to buildroot
	@cd $(INSTDIR)/bin; \
	    for f in `ls | xargs file | grep ELF | grep -v cash_wrap.so | sed -e 's/:.*//'`; do\
		test `basename $$f` != cash -a $(NOSTRIP) -eq 0 && strip $$f;\
		mv $$f $(BRCOPY)/usr/bin/$$f;\
	    done
	# Make buildroot usr/bin available for host
	@cd $(BRCOPY)/usr/bin; \
	    for f in `ls | xargs file -L | grep ELF | grep -v cash_wrap.so | sed -e 's/:.*//'`; do\
		test -e ../../../bin/$$f || ln -s ../buildroot/usr/bin/ffwrap ../../../bin/$$f;\
	    done;
	# /usr/bin non-ELF
	@cd $(BRCOPY)/usr/bin; \
	    for f in `ls | xargs file -L | grep -v ELF | sed -e 's/:.*//'`; do\
		test -e ../../../bin/$$f || ln -s ../buildroot/usr/bin/$$f ../../../bin/$$f;\
	    done
	# Make buildroot usr/sbin available for host
	@cd $(BRCOPY)/usr/sbin; \
	    for f in `ls | xargs file -L | grep ELF | sed -e 's/:.*//'`; do\
		test -e ../../../bin/$$f || ln -s ../buildroot/usr/sbin/ffwrap ../../../bin/$$f;\
	    done
	# /usr/sbin non-ELF
	@cd $(BRCOPY)/usr/sbin; \
	    for f in `ls | xargs file -L | grep -v ELF | sed -e 's/:.*//'`; do\
		test -e ../../../bin/$$f || ln -s ../buildroot/usr/sbin/$$f ../../../bin/$$f;\
	    done
	# strip libraries
	@if [ $(NOSTRIP) -eq 0 ]; then \
	    cd $(INSTDIR)/lib; \
	    for l in `ls | xargs file | grep ELF | sed -e 's/:.*//'`; do\
		strip $$l;\
	    done; fi
	# LD_LIBRARY_PATH fixups
	@cd $(INSTDIR)/bin; for f in $(FFWRAP_FORCE_LIB); do \
		if [ -L $$f ]; then nlink=`readlink $$f`-hlib; \
		if [ -r $$nlink ]; then ln -sfv $$nlink $$f; fi; fi; \
	done
	# shairport does not like those
	rm -f $(INSTDIR)/bin/avahi*
	# Provide terminfo database
	cd $(INSTDIR)/share; ln -s ../buildroot/usr/share/terminfo .
	readlink ${BR_TGT}/lib/libc.so.* | xargs basename > glibc-version || exit 1
	
clean: 
	rm -rf $(OUTPUTDIR) $(IMAGE) ffimage.bin
	for d in $(SUBDIRS) $(INSTDIRS:%/install=%); do make -k -C $$d clean || true; done

cleanall: clean
	make -C $(BUILDROOT) clean
