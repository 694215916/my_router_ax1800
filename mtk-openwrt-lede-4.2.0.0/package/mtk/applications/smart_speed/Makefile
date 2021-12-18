#
# hua.shao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=smart_speed
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/smart_speed
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=smart speed
  SUBMENU:=Applications
endef

define Package/smart_speed/description
	smart speed
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile/Default
endef

Build/Compile = $(Build/Compile/Default)

define Package/smart_speed/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) ./files/smart_speed_$(CONFIG_TARGET_SUBTARGET) $(1)/usr/bin/smart_speed
endef


$(eval $(call BuildPackage,smart_speed))

