#
# jie.shen@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mapd
PKG_REVISION:=7dd2f250
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.bz2
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

TARGET_CFLAGS += -DCONFIG_SUPPORT_OPENWRT
MAKE_FLAGS += CONFIG_SUPPORT_OPENWRT=y

PKG_BUILD_DEPENDS:=libmapd
define Package/mapd
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=map daemon
  SUBMENU:=Applications
  DEPENDS:=+wapp +1905daemon +libmapd
endef

define Package/mapd/description
  wifi app daemon
endef


define Package/mapd/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mapd $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mapd_cli $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bs20 $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mapd_user_iface $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc
	$(INSTALL_DIR) $(1)/etc/map
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/EasyMesh_openwrt.sh $(1)/usr/bin; \
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/config_agent.lua $(1)/usr/bin; \
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/map_config_agent.lua $(1)/usr/bin; \
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/map_cert_script.sh $(1)/usr/bin; \
	$(CP) $(PKG_BUILD_DIR)/wts_bss_info_config  $(1)/etc/map
	$(CP) $(PKG_BUILD_DIR)/mapd_user.cfg $(1)/etc/map
	$(CP) $(PKG_BUILD_DIR)/mapd_default.cfg  $(1)/etc/map
endef

$(eval $(call BuildPackage,mapd))
