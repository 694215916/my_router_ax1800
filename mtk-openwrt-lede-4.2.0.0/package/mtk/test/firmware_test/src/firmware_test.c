/*
 * firmware_example.c -
 *
 * Copyright (c) 2006 Victor Hugo <victor@vhugo.net>
 * Based on firmware_sample_driver.c by Manuel Estrada Sainz
 * Sample code on how to use request_firmware() from drivers.
 *
 */

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/string.h>
#include <linux/firmware.h>
#include <linux/slab.h>

static void sample_firmware_load(const char *firmware, int size)
{
    u8 *buf = kmalloc(size + 1, GFP_KERNEL);
    memcpy(buf, firmware, size);
    buf[size] = '\0';
    printk(KERN_INFO "firmware_example: Firmware: %s\n", buf);
    kfree(buf);
}

static void sample_probe(struct device *dev)
{
    /* uses the default method to get the firmware */
    const struct firmware *fw_entry;
    printk(KERN_INFO "firmware_example: ghost device inserted\n");

    if (request_firmware(&fw_entry, "fw.bin", dev) != 0) {
        printk(KERN_ERR "firmware_example: Firmware not vailable\n");
        return;
    }

    sample_firmware_load(fw_entry->data, fw_entry->size);

    release_firmware(fw_entry);

    /* finish setting up the device */
}

static void ghost_release(struct device *dev)
{
    printk(KERN_DEBUG "firmware_example : ghost device released\n");
}

static struct device ghost_device = {
    .init_name = "ghost0",
    .release = ghost_release
};

static int __init test_init(void)
{
    device_register(&ghost_device);
    sample_probe(&ghost_device);
    return 0;
}
static void __exit test_exit(void)
{
    device_unregister(&ghost_device);
}

module_init(test_init);
module_exit(test_exit);

MODULE_LICENSE("GPL");
