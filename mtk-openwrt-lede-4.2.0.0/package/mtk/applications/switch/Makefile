#
# hua.shao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=switch
PKG_REVISION:=34f15ebd
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.gz
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_KCONFIG:=MACH_MT7623 GE1_SGMII_FORCE_2500 SUPPORT_OPENWRT MACH_LEOPARD RALINK_MT7621 SOC_MT7621 MT753X_GSW
PKG_CONFIG_DEPENDS:=$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)))

define Package/switch
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  DEPENDS:=+libnl-tiny
  TITLE:=Command to config switch
  SUBMENU:=Applications
endef

define Package/switch/description
  An program to config switch.
endef

TARGET_CFLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),-DCONFIG_$(c)=$(CONFIG_$c)))

MAKE_FLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)=$(CONFIG_$c))) 

ifeq ($(CONFIG_LINUX_4_4),y)
TARGET_CFLAGS += \
	-I$(LINUX_DIR)/drivers/net/ethernet/raeth
else
TARGET_CFLAGS +=  \
	-I$(LINUX_DIR)/drivers/net/raeth
endif

define Build/Configure
endef


TARGET_CPPFLAGS := \
	-D_GNU_SOURCE \
	-I$(LINUX_DIR)/user_headers/include \
	-I$(STAGING_DIR)/usr/include/libnl-tiny \
	-I$(PKG_BUILD_DIR) \
	$(TARGET_CPPFLAGS) \

define Build/Compile
	CFLAGS="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS)" \
	$(MAKE) -C $(PKG_BUILD_DIR) \
		$(TARGET_CONFIGURE_OPTS) \
		LIBS="$(TARGET_LDFLAGS) -lnl-tiny -lm" \
		$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)=$(CONFIG_$(c))))
endef

define Package/switch/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/lib/network
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/switch $(1)/usr/bin
ifeq ($(CONFIG_MACH_LEOPARD),y)
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/switch_rtk $(1)/usr/bin
endif
endef

$(eval $(call BuildPackage,switch))
