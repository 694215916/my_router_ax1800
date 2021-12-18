#FIT loadaddr
KERNEL_LOADADDR := 0x40008000

#define Device/MTK-7629-FPGA
#  DEVICE_TITLE := MTK7629 FPGA
#  DEVICE_DTS := mt7629-fpga
#  DEVICE_PACKAGES := regs
#endef

#TARGET_DEVICES += MTK-7629-FPGA

define Device/MTK-7629-EVBv10
  DEVICE_TITLE := MTK7629 EVB v10
  DEVICE_DTS := mt7629-raeth-evb
  DEVICE_PACKAGES := regs luci ppp-mod-pptp xl2tpd wireless-tools \
                luci-app-mtk luci-app-samba block-mount kmod-fs-vfat kmod-fs-ext4
endef

TARGET_DEVICES += MTK-7629-EVBv10

define Device/MTK-7629-RAETHv10
  DEVICE_TITLE := MTK7629 RAETH RFBv10
  DEVICE_DTS := mt7629-raeth-rfb1v10
  DEVICE_PACKAGES := regs luci ppp-mod-pptp xl2tpd wireless-tools \
                luci-app-mtk luci-app-samba block-mount kmod-fs-vfat kmod-fs-ext4
endef

TARGET_DEVICES += MTK-7629-RAETHv10

define Device/MTK-7629-RAETH
  DEVICE_TITLE := MTK7629 RAETH RFB
  DEVICE_DTS := mt7629-raeth-rfb1
  DEVICE_PACKAGES := regs luci ppp-mod-pptp xl2tpd wireless-tools \
                luci-app-mtk luci-app-samba block-mount kmod-fs-vfat kmod-fs-ext4
endef

TARGET_DEVICES += MTK-7629-RAETH

define Device/MTK-7629-RFBv10
  DEVICE_TITLE := MTK7629 RFBv10
  DEVICE_DTS := mt7629-rfb1-v10
  DEVICE_PACKAGES := regs luci ppp-mod-pptp xl2tpd wireless-tools \
		luci-app-mtk luci-app-samba block-mount kmod-fs-vfat kmod-fs-ext4
endef

TARGET_DEVICES += MTK-7629-RFBv10

define Device/MTK-7629-RFB
  DEVICE_TITLE := MTK7629 RFB
  DEVICE_DTS := mt7629-rfb1
  DEVICE_PACKAGES := regs luci ppp-mod-pptp xl2tpd wireless-tools \
                luci-app-mtk luci-app-samba block-mount kmod-fs-vfat kmod-fs-ext4
endef

TARGET_DEVICES += MTK-7629-RFB

define Device/MT7629-MT7531-EVB1
  DEVICE_TITLE := MTK7629 MT7531 EVB1
  DEVICE_DTS := mt7629-lynx-evb1
  DEVICE_PACKAGES := regs luci ppp-mod-pptp xl2tpd wireless-tools \
                luci-app-mtk luci-app-samba block-mount kmod-fs-vfat kmod-fs-ext4
endef

TARGET_DEVICES += MT7629-MT7531-EVB1

define Device/MT7629-MT7531-EVB2
  DEVICE_TITLE := MTK7629 MT7531 EVB2
  DEVICE_DTS := mt7629-lynx-evb2
  DEVICE_PACKAGES := regs luci ppp-mod-pptp xl2tpd wireless-tools \
                luci-app-mtk luci-app-samba block-mount kmod-fs-vfat kmod-fs-ext4
endef

TARGET_DEVICES += MT7629-MT7531-EVB2

define Device/MT7629-MT7531-RFB3
  DEVICE_TITLE := MTK7629 MT7531 RFB3
  DEVICE_DTS := mt7629-lynx-rfb3
  DEVICE_PACKAGES := regs luci ppp-mod-pptp xl2tpd wireless-tools \
                luci-app-mtk luci-app-samba block-mount kmod-fs-vfat kmod-fs-ext4
endef

TARGET_DEVICES += MT7629-MT7531-RFB3

#install vmlinux for initial develop stage
define Image/Build/Initramfs
	cp $(KDIR)/vmlinux.debug $(BIN_DIR)/$(IMG_PREFIX)-vmlinux
	cp $(KDIR)/vmlinux-initramfs $(BIN_DIR)/$(IMG_PREFIX)-Image-initramfs
endef

