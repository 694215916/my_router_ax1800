#
# Copyright (C) 2008-2012 OpenWrt.org
#
# This is free software, licensed under the GNU General Public License v2.
# See /LICENSE for more information.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=mtk_smc
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define KernelPackage/mtk_smc
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=MTK simple SMC driver
  SUBMENU:=Drivers
  FILES:=$(PKG_BUILD_DIR)/mtk_smc.ko
  AUTOLOAD:=$(call AutoLoad,81,mtk_smc,1)
  KCONFIG:=
endef

define KernelPackage/mtk_smc/description
  MTK simple SMC driver
endef

MAKE_OPTS:= \
        ARCH="$(LINUX_KARCH)" \
        CROSS_COMPILE="$(TARGET_CROSS)" \
        SUBDIRS="$(PKG_BUILD_DIR)"

define Build/Compile
	$(MAKE) -C "$(LINUX_DIR)" \
		$(MAKE_OPTS) \
		modules
endef

$(eval $(call KernelPackage,mtk_smc))
