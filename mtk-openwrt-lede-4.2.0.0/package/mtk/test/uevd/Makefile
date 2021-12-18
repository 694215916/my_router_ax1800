#
# Hua Shao <nossiac@163.com> 
#

include $(TOPDIR)/rules.mk

PKG_NAME:=uevd
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_CONFIG_DEPENDS:=

include $(INCLUDE_DIR)/package.mk

define Package/uevd
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=Dump kernel uevent
  SUBMENU:=Internal
endef

define Package/uevd/description
  Dump kernel uevent
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef

TARGET_CFLAGS += -Wall
TARGET_CFLAGS += -Wno-error=format-security 

define Build/Configure
endef

define Package/uevd/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/uevd $(1)/usr/bin
endef


$(eval $(call BuildPackage,uevd))

