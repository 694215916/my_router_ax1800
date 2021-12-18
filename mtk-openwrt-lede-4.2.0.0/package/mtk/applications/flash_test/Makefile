#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=flash_test
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/kernel.mk

define Package/flash_test
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  TITLE:=Mediatek flash test tools/scripts
  SUBMENU:=Applications
  DEPENDS:=+lmbench +lmbench-lmdd
endef

define Package/flash_test/description
  Some Mediatek flash tools to do test for SNOR/NAND/eMMC flash
endef

define Package/flash_test/install
	$(INSTALL_DIR) $(1)/usr/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/mtdc_test $(1)/usr/bin
	$(INSTALL_BIN) ./files/sd_rw_test.sh $(1)/usr/bin
endef


$(eval $(call BuildPackage,flash_test))

