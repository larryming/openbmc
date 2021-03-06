/*
 * Copyright 2017-present Facebook. All Rights Reserved.
 *
 * This file contains code to provide addendum functionality over the I2C
 * device interfaces to utilize additional driver functionality.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#ifndef _OPENBMC_I2C_DEV_H_
#define _OPENBMC_I2C_DEV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Include all the functions for smbus transactions.
 */
#include <openbmc/smbus.h>

/*
 * I2C sysfs related interfaces.
 */
#define I2C_SYSFS_DEVICES		"/sys/bus/i2c/devices"
#define I2C_SYSFS_DRIVERS		"/sys/bus/i2c/drivers"
#define I2C_SYSFS_BUS_DIR(num)		I2C_SYSFS_DEVICES"/i2c-"#num
#define I2C_SYSFS_DEV_DIR(dev)		I2C_SYSFS_DEVICES"/"#dev
#define I2C_SYSFS_DEV_ENTRY(dev, ent)	I2C_SYSFS_DEVICES"/"#dev"/"#ent

/*
 * Extract i2c bus and device address from sysfs path "<bus>-<addr>".
 *
 * Return:
 *   0 for success, and -1 on failures.
 */
int i2c_sysfs_path_parse(const char *i2c_device, int *i2c_bus, int *i2c_addr);

/*
 * Issue read/write transactions to the given i2c device.
 *
 * Return:
 *   0 for success, and -1 on failures.
 */
int i2c_rdwr_msg_transfer(int file, __u8 addr, __u8 *tbuf, 
			  __u8 tcount, __u8 *rbuf, __u8 rcount);

#ifdef __cplusplus
} // extern "C"
#endif

#endif /* _OPENBMC_I2C_DEV_H_ */
