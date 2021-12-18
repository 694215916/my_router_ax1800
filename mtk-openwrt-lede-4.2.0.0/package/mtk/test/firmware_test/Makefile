#
# Copyright (C) Hua Shao <nossiac@163.com>
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=firmware_test
PKG_VERSION:=1
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(KERNEL_BUILD_DIR)/$(PKG_NAME)
PKG_MAINTAINER:=Hua Shao <nossiac@163.com>


define KernelPackage/firmware_test
  CATEGORY:=MTK Properties
  SUBMENU:=Misc
  TITLE:=Test firmware loading 
  FILES:=$(PKG_BUILD_DIR)/src/firmware_test.ko
  MENU:=1
endef

define Package/firmware_test/description
  Test firmware loading 
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) -r ./src $(PKG_BUILD_DIR)/src
endef

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" V=1 \
		CROSS_COMPILE="$(TARGET_CROSS)" \
		ARCH="$(LINUX_KARCH)" \
		SUBDIRS="$(PKG_BUILD_DIR)/src" \
		modules
endef

$(eval $(call KernelPackage,firmware_test))
