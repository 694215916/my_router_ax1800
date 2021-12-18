/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
 
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/of_mdio.h>
#include <linux/of_platform.h>
#include <linux/mfd/syscon.h>
#include <linux/regmap.h> 

#define INFRA_PHY 0x710
#define GE_FE_PHY_EN 0x10000820

struct mtk_gphy {
        struct device           *dev;
        struct mii_bus          *bus;
        struct regmap        *infra;
};

static struct mtk_gphy *_gphy;

static unsigned int mii_mgr_read(unsigned int phy_addr,unsigned int phy_register,unsigned int *read_data)
{
        struct mii_bus *bus = _gphy->bus;

        *read_data = mdiobus_read(bus, phy_addr, phy_register);

        return 0;
}

static unsigned int mii_mgr_write(unsigned int phy_addr,unsigned int phy_register,unsigned int write_data)
{
        struct mii_bus *bus =  _gphy->bus;

        mdiobus_write(bus, phy_addr, phy_register, write_data);

        return 0;
}

#include "mtk_gphy_cal.c"

static const struct of_device_id mtk_gphy_match[] = {
        { .compatible = "mediatek,eth-fe-gphy" },
        {},
};

MODULE_DEVICE_TABLE(of, mtk_gphy_match);

static int gphy_probe(struct platform_device *pdev)
{
        struct device_node *np = pdev->dev.of_node;
        struct device_node *mdio;
        struct mii_bus *mdio_bus;
        struct mtk_gphy *gphy;
 	

        mdio = of_parse_phandle(np, "mediatek,mdio", 0);

        if (!mdio)
                return -EINVAL;

        mdio_bus = of_mdio_find_bus(mdio);


        if (!mdio_bus)
                return -EPROBE_DEFER;

        gphy = devm_kzalloc(&pdev->dev, sizeof(struct mtk_gphy), GFP_KERNEL);

        if (!gphy)
                return -ENOMEM;


        gphy->dev = &pdev->dev;

        gphy->bus = mdio_bus;

   	gphy->infra = syscon_regmap_lookup_by_phandle(pdev->dev.of_node,
                                                           "mediatek,infracfg");	
	_gphy = gphy;

	if (IS_ERR(gphy->infra))
                printk("gphy no infra support");
        else {
		 //enable fe/gphy for calibration	
                regmap_write(gphy->infra, INFRA_PHY, GE_FE_PHY_EN);
        }

	leopard_ephy_cal();
		
        platform_set_drvdata(pdev, gphy);

        return 0;		
}

static int gphy_remove(struct platform_device *pdev)
{
        platform_set_drvdata(pdev, NULL);      

        return 0;
}

static struct platform_driver fe_gphy_driver = {
        .probe = gphy_probe,
        .remove = gphy_remove,
        .driver = {
                .name = "mtk-fe-gphy",
                .owner = THIS_MODULE,
                .of_match_table = mtk_gphy_match,
        },
};

module_platform_driver(fe_gphy_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mark Lee <marklee0201@gmail.com>");
MODULE_DESCRIPTION("mtk internal gphy driver");

