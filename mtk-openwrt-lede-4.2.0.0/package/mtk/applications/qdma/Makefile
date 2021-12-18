#
# hua.shao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=qdma
PKG_REVISION:=5aab86d1
PKG_SOURCE:=$(PKG_NAME)-$(PKG_REVISION).tar.gz
PKG_RELEASE:=1
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:=RALINK_MT7621 HW_SFQ MTK_EMI_7622 MTK_FPGA

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/qdma
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  DEPENDS:=@(TARGET_ramips_mt7621||TARGET_mediatek)
  TITLE:=QDMA configuration tool
  SUBMENU:=Applications
endef

define Package/qdma/description
  QDMA configuration tool
endef


TARGET_CFLAGS += -I$(LINUX_DIR)/drivers/net/ethernet/raeth
TARGET_CFLAGS += $(foreach c, $(PKG_KCONFIG),$(if $(CONFIG_$c),-DCONFIG_$(c)=$(CONFIG_$c)))
TARGET_CFLAGS += -Wall
TARGET_CFLAGS += -Wno-error=format-security -DCONFIG_SUPPORT_OPENWRT

MAKE_FLAGS += CONFIG_SUPPORT_OPENWRT=y
ifeq ($(CONFIG_LINUX_4_4),y)
MAKE_FLAGS += CONFIG_DEFAULTS_KERNEL_4_4=y
endif

define Build/Configure
endef

define Package/qdma/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/qdma $(1)/usr/bin
endef


$(eval $(call BuildPackage,qdma))

