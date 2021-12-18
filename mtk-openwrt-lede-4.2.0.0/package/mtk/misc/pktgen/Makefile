#
# MTK pktgen
#

include $(TOPDIR)/rules.mk

PKG_NAME:=pktgen
PKG_RELEASE:=1

PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk

TARGET_CFLAGS += -DCONFIG_SUPPORT_OPENWRT

define Package/pktgen
  CATEGORY:=MTK Properties
  SUBMENU:=Misc
  TITLE:=packet generator
endef

define Build/Compile
	$(MAKE) -C $(PKG_BUILD_DIR) \
		CC="$(TARGET_CC)" \
		CFLAGS="$(TARGET_CFLAGS) -Wall" \
		LDFLAGS="$(TARGET_LDFLAGS)"
endef

define Package/pktgen/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/ethernet_pt $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,pktgen))
