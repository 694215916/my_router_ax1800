#
# hua.shao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=long_loop
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)


include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/longloopd
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=Daemon to monitor switch link for long distance(>100m)
  SUBMENU:=Applications
endef

define Package/longloopd/description
  Daemon to monitor switch link for long distance(>100m)
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
endef

define Build/Compile/Default
endef

Build/Compile = $(Build/Compile/Default)

define Package/longloopd/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_DIR) $(1)/etc/longloopd
	-$(CP) ./files/*.sh  $(1)/etc/longloopd/
	$(INSTALL_BIN) ./files/long_loop_$(CONFIG_TARGET_SUBTARGET) $(1)/usr/bin/long_loop
endef


$(eval $(call BuildPackage,longloopd))

