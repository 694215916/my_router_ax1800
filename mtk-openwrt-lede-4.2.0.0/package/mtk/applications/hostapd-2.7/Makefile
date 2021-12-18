#
# hua.shao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=hostapd-2.7
PKG_REVISION:=3d70affa
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.bz2
PKG_VERSION:=2.7
PKG_RELEASE:= 0
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:=RALINK_MT7621
PKG_CONFIG_DEPENDS:=$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),CONFIG_$(c)))

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/hostapd-2.7
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=WPA hostapd V2.7
  SUBMENU:=Applications
  DEPENDS:= +libnl-tiny +libopenssl
endef

define Package/hostapd-2.7/description
  WPA hostapd V2.7
endef

CONFIGURE_VARS += \
	LIBDBI_CFLAGS="-I$(STAGING_DIR)/usr/include"

ifneq ($(wildcard $(PKG_BUILD_DIR)/.config_*),$(subst .configured_,.config_,$(STAMP_CONFIGURED)))
  define Build/Configure/rebuild
	$(FIND) $(PKG_BUILD_DIR) -name \*.o -or -name \*.a | $(XARGS) rm -f
	rm -f $(PKG_BUILD_DIR)/hostapd/hostapd
	rm -f $(PKG_BUILD_DIR)/hostapd/t.config_*
	touch $(subst .configured_,.config_,$(STAMP_CONFIGURED))
  endef
endif

define Build/Configure
	$(Build/Configure/rebuild)
	$(CP) ./files/hostapd-mini.config $(PKG_BUILD_DIR)/hostapd/.config
endef

DRIVER_MAKEOPTS= \
    CONFIG_DRIVER_NL80211=y
#    CONFIG_IEEE80211N=$(HOSTAPD_IEEE80211N)

TARGET_CPPFLAGS += \
    -I$(PKG_BUILD_DIR)/src \
    -I$(PKG_BUILD_DIR)/src/utils \
    -I/include \
    -I$(STAGING_DIR)/usr/include/libnl3 \
    -I$(STAGING_DIR)/usr/include/openssl \
    -I$(STAGING_DIR)/usr/include \
	-I$(BUILD_DIR)/libnl-tiny-0.1/include/ \
	-I$(BUILD_DIR)/openssl-1.0.2n/include \
    -DCONFIG_LIBNL20 \
    -D_GNU_SOURCE \
    -DCONFIG_MSG_MIN_PRIORITY=0
	
TARGET_CFLAGS += \
	-ffunction-sections \
	-fdata-sections \
	-DNO_TIMESTAMP_CHECK

TARGET_LDFLAGS += -Wl,--gc-sections -lnl-tiny -lssl -lcrypto
TARGET_CONFIGURE_OPTS += CONFIG_P2P=y CONFIG_INTERNAL_LIBTOMMATH=y

TARGET_CFLAGS += \
	$(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),-DCONFIG_$(c)=$(CONFIG_$c)))

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

# define Build/Compile/wpad
	# echo ` \
		# $(call Build/RunMake,hostapd,-s MULTICALL=1 dump_cflags) | \
		# sed -e 's,-n ,,g' -e 's,$(TARGET_CFLAGS),,' \
	# ` > $(PKG_BUILD_DIR)/.cflags
	# +$(call Build/RunMake,hostapd, \
		# CFLAGS="$$$$(cat $(PKG_BUILD_DIR)/.cflags)" \
		# MULTICALL=1 \
		# hostapd_cli hostapd_multi.a \
	# )
	# +$(call Build/RunMake,hostapd, \
		# CFLAGS="$$$$(cat $(PKG_BUILD_DIR)/.cflags)" \
		# MULTICALL=1 \
		# wpa_cli hostapd_multi.a \
	# )
	# $(TARGET_CC) -o $(PKG_BUILD_DIR)/wpad \
		# $(TARGET_CFLAGS) \
		# ./files/multicall.c \
		# $(PKG_BUILD_DIR)/hostapd/hostapd_multi.a \
		# $(PKG_BUILD_DIR)/hostapd/hostapd.a \
		# $(TARGET_LDFLAGS)
# endef


define Build/Compile
    $(call Build/RunMake,hostapd, \
        hostapd_cli hostapd \
    )
endef

define Package/hostapd-2.7/install
	$(INSTALL_DIR) $(1)/usr/bin
#	$(CP) $(PKG_BUILD_DIR)/hostapd/hostapd $(PKG_BUILD_DIR)/hostapd/hostapd-2-7
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/hostapd/hostapd $(1)/usr/bin
	$(CP) $(PKG_BUILD_DIR)/hostapd/hostapd  $(1)/usr/bin/
	$(CP) $(PKG_BUILD_DIR)/hostapd/hostapd_cli $(1)/usr/bin/

	$(INSTALL_DIR) $(1)/etc
	$(CP) files/hostapd.conf $(1)/etc/
	$(CP) files/hostapd_ra0_open.conf $(1)/etc/
	$(CP) files/hostapd_rai0_open.conf $(1)/etc/
	$(CP) files/hostapd_ra0_wpa2psk.conf $(1)/etc/
	$(CP) files/hostapd_rai0_wpa2psk.conf $(1)/etc/
	$(CP) files/hostapd_ra0_map.conf $(1)/etc/
	$(CP) files/hostapd_ra1_map.conf $(1)/etc/
	$(CP) files/hostapd_ra2_map.conf $(1)/etc/
	$(CP) files/hostapd_ra3_map.conf $(1)/etc/
	$(CP) files/hostapd_rax0_map.conf $(1)/etc/
	$(CP) files/hostapd_rax1_map.conf $(1)/etc/
	$(CP) files/hostapd_rax2_map.conf $(1)/etc/
	$(CP) files/hostapd_rax3_map.conf $(1)/etc/
#	$(CP) files/hostapd-wpa3  $(1)/usr/bin/
#	$(CP) files/hostapd-wpa3_cli $(1)/usr/bin/
	$(CP) files/hostapd_ra0_sae.conf $(1)/etc/
	$(CP) files/hostapd_rai0_sae.conf $(1)/etc/
	$(CP) files/hostapd_ra0_owe.conf $(1)/etc/
	$(CP) files/hostapd_rai0_owe.conf $(1)/etc/
	$(CP) files/hostapd_ra0_wpa3.conf $(1)/etc/
	$(CP) files/hostapd_rai0_wpa3.conf $(1)/etc/
	$(CP) files/hostapd_ra0_owe_sigma.conf $(1)/etc/
	$(CP) files/hostapd_rai0_owe_sigma.conf $(1)/etc/
	$(CP) files/hostapd_ra0_wpa3_sigma.conf $(1)/etc/
	$(CP) files/hostapd_rai0_wpa3_sigma.conf $(1)/etc/
endef

$(eval $(call BuildPackage,hostapd-2.7))


