PKGDIR=$(shell while test -f package.mk && echo $$PWD && exit 0; [ $$PWD != / ]; do cd ..; done)

SRCDIR		= $(TOPDIR)/src
CONFTYPE	= legacy
#MAKE_OPTIONS	= "CFLAGS=-DLIBC_LOCATION=\\\"/lib/libc.so\\\" -DD_DNS"
MAKE_OPTIONS	= CFLAGS="-DD_DNS -DDEBUG"
INSTALL_LIB	= $(BUILDDIR)/libmultid.so $(BUILDDIR)/libmultid.so.0.0.0

all:

include $(PKGDIR)/package.mk
