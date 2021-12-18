#
# Copyright (C) 2012-2015 OpenWrt.org
# Copyright (C) 2016-2017 LEDE project
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#
include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/image.mk

# build dtb
define Build/dtb
        $(call Image/BuildDTB,$(DEVICE_DTS_DIR)/$(DEVICE_DTS).dts,$(DEVICE_DTS_DIR)/$(DEVICE_DTS).dtb)
	$(CP) $(DEVICE_DTS_DIR)/$(DEVICE_DTS).dtb $(BIN_DIR)/
endef

# build signed fit
define Build/fit-sign
  $(TOPDIR)/scripts/mkits.sh \
	-D $(DEVICE_NAME) -o $@.its -k $@ \
	$(if $(word 2,$(1)),-d $(word 2,$(1))) -C $(word 1,$(1)) \
	-a $(KERNEL_LOADADDR) -e $(if $(KERNEL_ENTRY),$(KERNEL_ENTRY),$(KERNEL_LOADADDR)) \
	-A $(LINUX_KARCH) -v $(LINUX_VERSION) \
	$(if $(word 3,$(1)),-s $(word 3,$(1))) \
	$(if $(word 4,$(1)),-S $(word 4,$(1)))
  PATH=$(LINUX_DIR)/scripts/dtc:$(PATH) mkimage -f $@.its \
	$(if $(word 5,$(1)),-k $(word 5,$(1))) \
	-r $@.new
  @mv $@.new $@
endef

# default all platform image(fit) build
define Device/Default
  PROFILES = Default $$(DEVICE_NAME)
  KERNEL_NAME := Image
  FIT_KEY_DIR :=
  FIT_KEY_NAME :=
  UBOOT_SCRIPT :=
  FILESYSTEMS := squashfs
  DEVICE_DTS_DIR := $(DTS_DIR)
  KERNEL = dtb | kernel-bin | lzma | fit lzma $$(DEVICE_DTS_DIR)/$$(DEVICE_DTS).dtb
  IMAGES := sysupgrade.bin
  IMAGE/sysupgrade.bin := append-kernel | pad-to 128k | append-rootfs | pad-rootfs | append-metadata
endef

include $(SUBTARGET).mk

$(eval $(call BuildImage))

