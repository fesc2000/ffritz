
CONFTYPE	= legacy

NO_MAKE_INSTALL = 1
MAKE_OPTIONS    =  ARCH=x86 CROSS_COMPILE=i686-linux- modules
CUSTOM_DEP      = .prep.stamp

include ../../package.mk

.prep.stamp:
	cp x86_avm_defconfig $(BUILDDIR)/arch/x86/configs/
	make -C $(BUILDDIR) ARCH=x86 CROSS_COMPILE=i686-linux- x86_avm_defconfig
	touch $@

config:
	make -C $(BUILDDIR) ARCH=x86 CROSS_COMPILE=i686-linux- menuconfig savedefconfig

bzImage:
	PATH=$(TOOLCHAIN):$(PATH) make -C $(BUILDDIR) ARCH=x86 CROSS_COMPILE=i686-linux- bzImage


test:
	make -C $(BUILDDIR) ARCH=x86 CROSS_COMPILE=i686-linux- puma7-crash-kernel_defconfig

install-modules:
