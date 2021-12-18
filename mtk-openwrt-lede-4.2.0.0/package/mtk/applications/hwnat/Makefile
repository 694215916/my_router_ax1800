#
# hua.shao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=hwnat
PKG_REVISION:=5467d09e
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.gz
PKG_RELEASE:=4200

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:=RALINK_MT7620 RALINK_MT7621 RALINK_MT7628 RALINK_MT7623 HNAT_V2 \
		HW_NAT_MANUAL_MODE HW_NAT_SEMI_AUTO_MODE PPE_MCAST PPE_MIB
PKG_CONFIG_DEPENDS:=$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)))


include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/hwnat
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=Hardware NAT command
  DEPENDS:=@PACKAGE_kmod-hw_nat
  SUBMENU:=Applications
endef

define Package/hwnat/description
  An program to query info from hwnat driver
endef

TARGET_CFLAGS += -I$(LINUX_DIR)/drivers/net/ethernet/raeth
TARGET_CFLAGS += \
	-I$(LINUX_DIR)/net/nat/hw_nat/ \
        $(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),-DCONFIG_$(c)=$(CONFIG_$c))) \

MAKE_FLAGS += \
	CFLAGS="$(TARGET_CFLAGS)"

TARGET_CFLAGS += -DCONFIG_SUPPORT_OPENWRT 
MAKE_FLAGS += CONFIG_SUPPORT_OPENWRT=y

define Build/Configure
endef

define Package/hwnat/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_DIR) $(1)/etc/init.d/
	$(INSTALL_DIR) $(1)/etc/config/
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/hwnat $(1)/bin
	$(INSTALL_BIN) ./files/hwnat $(1)/etc/init.d/hwnat
	$(INSTALL_BIN) ./files/hwnat.uci $(1)/etc/config/hwnat
endef


$(eval $(call BuildPackage,hwnat))

