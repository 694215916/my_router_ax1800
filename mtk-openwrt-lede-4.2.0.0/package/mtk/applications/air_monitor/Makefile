#
# Sirui Zhao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=air_monitor
PKG_REVISION:=be424fa9
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.bz2
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:=


include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/air_monitor
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=Air Monitor Daemon
  SUBMENU:=Applications
endef

define Package/air_monitor/description
  This is a sample daemon for test and verify function for Air Monitor in Driver.
endef



#TARGET_CFLAGS += \
#	CFLAGS="$(TARGET_CFLAGS)"

define Build/Configure
endef

define Package/air_monitor/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/AirMonitorApp $(1)/bin/air_monitor
endef


$(eval $(call BuildPackage,air_monitor))

