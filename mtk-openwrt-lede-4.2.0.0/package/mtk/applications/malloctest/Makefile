#
# Sirui Zhao@mediatek.com
#
# MTK Property Software.
#

include $(TOPDIR)/rules.mk

PKG_NAME:=malloctest
PKG_RELEASE:=1

PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)
PKG_KCONFIG:=
PKG_CONFIG_DEPENDS:=

include $(INCLUDE_DIR)/package.mk

define Package/malloctest
  SECTION:=MTK Properties
  CATEGORY:=MTK Properties
  DEPENDS:=+libpthread
  TITLE:=malloc test Daemon
  SUBMENU:=Applications
endef

define Package/malloctest/description
  This is a sample daemon for test and verify function for malloc.
endef

define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)/
endef


define Build/Configure
endef

define Package/malloctest/install
	$(INSTALL_DIR) $(1)/bin
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/multithread_malloc_testcode $(1)/bin/multithread_malloc_testcode
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/multithread_malloc_testcode_t1 $(1)/bin/multithread_malloc_testcode_t1
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/multithread_malloc_testcode_t2 $(1)/bin/multithread_malloc_testcode_t2
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/multithread_malloc_testcode_t2 $(1)/bin/multithread_malloc_testcode_t0
endef

$(eval $(call BuildPackage,malloctest))

