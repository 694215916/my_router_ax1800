#
# MTK Autotest 
#

include $(TOPDIR)/rules.mk

PKG_NAME:=autotest
PKG_VERSION:=1
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_CONFIG_DEPENDS:=

include $(INCLUDE_DIR)/package.mk

define Package/autotest
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  SUBMENU:=Misc
  TITLE:=Autotest process
  VERSION:=$(PKG_RELEASE)-$(REVISION)
endef

define Package/autotest/description
  Autotest process
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile/Default
endef

Build/Compile = $(Build/Compile/Default)

define Package/autotest/install
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_BIN) ./files/autotest.init $(1)/etc/init.d/autotest
	$(INSTALL_DIR) $(1)/usr/share/autotest
	$(INSTALL_BIN) ./files/autotest.sh $(1)/usr/share/autotest/autotest.sh
endef


$(eval $(call BuildPackage,autotest))

