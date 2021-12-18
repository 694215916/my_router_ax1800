#
# hua.shao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=wpa_supplicant-2.0
PKG_REVISION:=9167bcbc
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.bz2
PKG_VERSION:=2.0
PKG_RELEASE:= 0
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:=RALINK_MT7620 RALINK_MT7621 RALINK_MT7628
PKG_CONFIG_DEPENDS:=$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)))

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/wpa_supplicant-2.0
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=WPA Supplicant V2.0
  SUBMENU:=Applications
  DEPENDS:=+libnl-tiny 
endef

define Package/wpa_supplicant-2.0/description
  WPA Supplicant V2.0
endef

CONFIGURE_VARS += \
	LIBDBI_CFLAGS="-I$(STAGING_DIR)/usr/include"

ifneq ($(wildcard $(PKG_BUILD_DIR)/.config_*),$(subst .configured_,.config_,$(STAMP_CONFIGURED)))
  define Build/Configure/rebuild
	$(FIND) $(PKG_BUILD_DIR) -name \*.o -or -name \*.a | $(XARGS) rm -f
	rm -f $(PKG_BUILD_DIR)/wpa_supplicant/wpa_supplicant
	rm -f $(PKG_BUILD_DIR)/wpa_supplican/t.config_*
	touch $(subst .configured_,.config_,$(STAMP_CONFIGURED))
  endef
endif

define Build/Configure
	$(Build/Configure/rebuild)
	$(CP) ./files/wpa_supplicant-mini.config $(PKG_BUILD_DIR)/wpa_supplicant/.config
endef

DRIVER_MAKEOPTS= \
    CONFIG_DRIVER_NL80211=y \
    CONFIG_IEEE80211N=$(HOSTAPD_IEEE80211N)

TARGET_CPPFLAGS += \
    -I$(PKG_BUILD_DIR)/src \
    -I$(PKG_BUILD_DIR)/src/utils \
    -I/include \
    -I$(STAGING_DIR)/usr/include/libnl3 \
	-I$(TOPDIR)/staging_dir/host/include/ \
	-I$(BUILD_DIR)/libnl-tiny-0.1/include/ \
    -DCONFIG_LIBNL20 \
    -D_GNU_SOURCE \
    -DCONFIG_MSG_MIN_PRIORITY=0
	
TARGET_CFLAGS += \
	-ffunction-sections \
	-fdata-sections \
	-DNO_TIMESTAMP_CHECK

TARGET_LDFLAGS += -Wl,--gc-sections -lnl-tiny
TARGET_CONFIGURE_OPTS += CONFIG_P2P=y CONFIG_INTERNAL_LIBTOMMATH=y

TARGET_CFLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),-DCONFIG_$(c)=$(CONFIG_$c)))

TARGET_CFLAGS += -DCONFIG_SUPPORT_OPENWRT
MAKE_FLAGS += CONFIG_SUPPORT_OPENWRT=y

CFLAGS="$(TARGET_CFLAGS)"

define Build/RunMake
	CFLAGS="$(TARGET_CPPFLAGS) $(TARGET_CFLAGS)" \
	$(MAKE) $(PKG_JOBS) -C $(PKG_BUILD_DIR)/$(1) \
		$(TARGET_CONFIGURE_OPTS) \
		$(DRIVER_MAKEOPTS) \
		LIBS="$(TARGET_LDFLAGS)" \
		LIBS_c="$(TARGET_LDFLAGS_C)" \
		BCHECK= \
		$(2)
endef

define Build/Compile/wpad
	echo ` \
		$(call Build/RunMake,wpa_supplicant,-s MULTICALL=1 dump_cflags) | \
		sed -e 's,-n ,,g' -e 's,$(TARGET_CFLAGS),,' \
	` > $(PKG_BUILD_DIR)/.cflags
	+$(call Build/RunMake,hostapd, \
		CFLAGS="$$$$(cat $(PKG_BUILD_DIR)/.cflags)" \
		MULTICALL=1 \
		hostapd_cli hostapd_multi.a \
	)
	+$(call Build/RunMake,wpa_supplicant, \
		CFLAGS="$$$$(cat $(PKG_BUILD_DIR)/.cflags)" \
		MULTICALL=1 \
		wpa_cli wpa_supplicant_multi.a \
	)
	$(TARGET_CC) -o $(PKG_BUILD_DIR)/wpad \
		$(TARGET_CFLAGS) \
		./files/multicall.c \
		$(PKG_BUILD_DIR)/hostapd/hostapd_multi.a \
		$(PKG_BUILD_DIR)/wpa_supplicant/wpa_supplicant_multi.a \
		$(TARGET_LDFLAGS)
endef


define Build/Compile
    $(call Build/RunMake,wpa_supplicant, \
        wpa_cli wpa_supplicant \
    )
endef

define Package/wpa_supplicant-2.0/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/wpa_supplicant/wpa_supplicant $(1)/usr/bin
	$(CP) $(PKG_BUILD_DIR)/wpa_supplicant/wpa_supplicant  $(1)/usr/bin/
	$(CP) $(PKG_BUILD_DIR)/wpa_supplicant/wpa_cli $(1)/usr/bin/

	$(INSTALL_DIR) $(1)/etc
	$(CP) files/wpa_supplicant.conf $(1)/etc/
	$(CP) files/p2p_dev.conf $(1)/etc/
	$(CP) files/p2p_dhcpd.conf $(1)/etc/
endef

$(eval $(call BuildPackage,wpa_supplicant-2.0))


