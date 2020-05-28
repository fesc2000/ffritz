## Template for integrating "3rd prty" tool
##
## Tool specific options for configuring, building and installing 
## are listed in ../../package.mk
##
## By default,
## - tarball/git repository is downloaded (../../url-mypackage or ../../git-mypackage must exist)
## - extracted/cloned below "build",
## - patched with all .patch files located here
## - configured according to CONFTYPE
## - built below build
## - installed (make install) according to INSTALL_ rules
##
## make clean deletes the build directory
##
## To integrate the build result into the application package, add
## this to ../ffritz/Makefile:
##
## INSTDIRS   += ../mypackage/install
##
## Missing libraries etc. should first be searched for in buildroot and
## added via "make userconfig" there.
##
############################################################################

# Find directory containing package.mk upwards
#
PKGDIR=$(shell while test -f package.mk && echo $$PWD && exit 0; [ $$PWD != / ]; do cd ..; done)

MAKE_OPTIONS = LIBS="-pthread -lrt -L$(TGTDIR)/usr/lib -lhogweed -lgmp -lnettle" SETCAP="echo > $(TOPDIR)/output$$PREFIX/bin/ftl-cap" PREFIX=
MAKE_INSTALL_OPTIONS = $(MAKE_OPTIONS)

CONFTYPE            =  legacy
PKG_CONFIGURE_FLAGS =
INSTALL_BIN         = 

include $(PKGDIR)/package.mk
