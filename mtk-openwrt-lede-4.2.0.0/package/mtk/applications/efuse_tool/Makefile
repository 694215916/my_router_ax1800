#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=efuse_tool
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/efuse_tool
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=efuse tool
  SUBMENU:=Applications
  DEPENDS:=+kmod-mtk_smc
endef

define Build/Compile
endef

define Package/efuse_tool/description
  efuse tool to read/write efuse
endef

define Package/efuse_tool/install
	$(INSTALL_DIR) $(1)/usr/sbin
	$(INSTALL_BIN) ./files/efuse_tool.sh $(1)/usr/sbin
endef

$(eval $(call BuildPackage,efuse_tool))

