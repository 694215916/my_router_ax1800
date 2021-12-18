#
# hua.shao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=mii_mgr
PKG_REVISION:=ef06bdb2
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.gz
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:=RALINK_MT7620 RALINK_MT7621 RALINK_MT7628 MACH_MT7623 GE1_SGMII_FORCE_2500 GE2_SGMII_FORCE_2500
PKG_CONFIG_DEPENDS:=$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)))


include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/mii_mgr
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=mii_mgr/mii_mgr_cl45
  SUBMENU:=Applications
endef

define Package/mii_mgr/description
  An program.
endef


TARGET_CFLAGS += -I$(LINUX_DIR)/drivers/net/ethernet/raeth \
		$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),-DCONFIG_$(c)=$(CONFIG_$c)))		

TARGET_CFLAGS += -DCONFIG_SUPPORT_OPENWRT 
MAKE_FLAGS += CONFIG_SUPPORT_OPENWRT=y

MAKE_FLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)=$(CONFIG_$c)))
define Build/Configure
endef

define Package/mii_mgr/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mii_mgr $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mii_mgr_cl45 $(1)/usr/bin
endef


$(eval $(call BuildPackage,mii_mgr))

