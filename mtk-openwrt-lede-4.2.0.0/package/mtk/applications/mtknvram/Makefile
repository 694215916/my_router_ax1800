#
# hua.shao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk
include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

PKG_NAME:=nvram
PKG_REVISION:=66a28550
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.gz
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:=RALINK_MT7620 RALINK_MT7621 RALINK_MT7628 MACH_MT7623 MTK_EMI_7622 SUPPORT_OPENWRT
PKG_CONFIG_DEPENDS:=$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)))

TARGET_CFLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),-DCONFIG_$(c)=$(CONFIG_$c)))

MAKE_FLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)=$(CONFIG_$c)))

MAKE_FLAGS += CONFIG_RALINKAPP_USER_NVRAMD=y
TARGET_CFLAGS += -DCONFIG_RALINKAPP_USER_NVRAMD -DCONFIG_USER_LIGHTY -DRT2860_NEW_MBSS_SUPPORT -DWSC_SUPPORT -DDBDC_MODE

ifneq ($(findstring y, $(CONFIG_RALINK_MT7621)$(CONFIG_MACH_MT7623)),)
TARGET_CFLAGS += -DNO_WIFI_SOC
endif

define Package/nvram_utils
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=mtk nvram tools
  SUBMENU:=Applications
  DEPENDS:=libnvram
endef

define Package/nvram_utils/description
  mtk nvram tools
endef

define Package/nvramd
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=mtk nvram daemon
  SUBMENU:=Applications
  DEPENDS:=libnvram
endef

define Package/nvramd/description
  mtk nvram daemon
endef


define Package/nvram_utils/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/ralink_init $(1)/usr/bin
	$(LN) ralink_init $(1)/usr/bin/nvram_get
	$(LN) ralink_init $(1)/usr/bin/nvram_set
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/sig_handlerd $(1)/usr/bin
	$(LN) sig_handlerd $(1)/usr/bin/nvram_daemon
endef

define Package/nvramd/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/bin/nvramd $(1)/usr/bin
endef


$(eval $(call BuildPackage,nvram_utils))
$(eval $(call BuildPackage,nvramd))

