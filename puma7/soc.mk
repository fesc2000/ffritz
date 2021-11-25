UIMG_DIR = $(REPODIR)/tools/uimg-tool
UIMG     = $(UIMG_DIR)/uimg

$(UIMG_DIR)/Makefile:
	@git submodule init $(UIMG_DIR)
	@git submodule update $(UIMG_DIR)

$(UIMG):	$(UIMG_DIR)/Makefile
	@make -C $(UIMG_DIR)

# extrace uimg
#
$(PLAT_TMP)/uimage:	$(ORIG) $(UIMG)
	@mkdir -p $(PLAT_TMP)/uimage
	@cd $(PLAT_TMP)/uimage; tar xf $(ORIG)
	@cd $(PLAT_TMP)/uimage; $(UIMG) -u -n part var/firmware-update.uimg

# re-pack uimg
#
$(RELDIR)/$(FWFILE): $(RELDIR) atomfs armfs  
	@rm -rf $(PLAT_TMP)/var
	@cd $(PLAT_TMP); tar xf $(ORIG)
	@cp -f $(ARM_TMP)/filesystem.image $(ARM_ROOTIMG)
	@rm -f $(PLAT_TMP)/var/remote/var/tmp/filesystem.image
	@cp $(PLAT_BASE)/atom/mod/usr/bin/switch_bootbank $(PLAT_TMP)/var
	@cp -f $(ATOM_TMP)/filesystem.image $(ATOM_ROOTIMG)
ifeq ($(ENABLE_CONSOLE),1)
	@echo "PATCH  part_02_ATOM_KERNEL.bin"
	@mkdir -p $(ATOM_TMP)/mnt
	@sudo mount -o loop $(PLAT_TMP)/uimage/part_02_ATOM_KERNEL.bin $(ATOM_TMP)/mnt >/dev/null 
	@test -r $(ATOM_TMP)/mnt/EFI/BOOT/startup.nsh
	@(echo mm 0xfed94810 0x00914b49 -w 4; echo mm 0xfed94820 0x00914b49 -w 4; cat $(ATOM_TMP)/mnt/EFI/BOOT/startup.nsh) > .startup.nsh
	@sudo cp .startup.nsh $(ATOM_TMP)/mnt/EFI/BOOT/startup.nsh
	@sudo umount $(ATOM_TMP)/mnt >/dev/null 
	@rm -f .startup.nsh
endif
	@echo "PACK   firmware-update.uimg"
	@$(UIMG) -p -n $(PLAT_TMP)/uimage/part $(PLAT_TMP)/var/firmware-update.uimg
	@echo "PACK   $(PLAT_TMP)/$(FWFILE)"
	@cd $(PLAT_TMP); $(TAR) cf $(RELDIR)/$(FWFILE) var
	@echo
	@echo +++ Done +++
