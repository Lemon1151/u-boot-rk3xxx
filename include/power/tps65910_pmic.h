/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) EETS GmbH, 2017, Felix Brack <f.brack@eets.ch>
 */

#ifndef __TPS65910_PMIC_H_
#define __TPS65910_PMIC_H_

#define TPS65910_I2C_SEL_MASK		(0x1 << 4)
#define TPS65910_VDD_SR_MASK		(0x1 << 7)
#define TPS65910_GAIN_SEL_MASK		(0x3 << 6)
#define TPS65910_VDD_SEL_MASK		0x7f
#define TPS65910_VDD_SEL_MIN		3
#define TPS65910_VDD_SEL_MAX		75
#define TPS65910_SEL_MASK		(0x3 << 2)
#define TPS65910_SUPPLY_STATE_MASK	0x3
#define TPS65910_SUPPLY_STATE_OFF	0x0
#define TPS65910_SUPPLY_STATE_ON	0x1

/* TPS65910 DEVICE_CTRL bits */
#define   PWR_OFF_SEQ			BIT(7)
#define   DEV_OFF_RST			BIT(3)
#define   DEV_ON			BIT(2)
#define   DEV_OFF			BIT(0)

/* i2c registers */
enum {
	TPS65910_REG_RTC_SEC			= 0x00,
	TPS65910_REG_RTC_MIN,
	TPS65910_REG_RTC_HOUR,
	TPS65910_REG_RTC_DAY,
	TPS65910_REG_RTC_MONTH,
	TPS65910_REG_RTC_YEAR,
	TPS65910_REG_RTC_WEEK,
	TPS65910_REG_RTC_ALARM_SEC		= 0x08,
	TPS65910_REG_RTC_ALARM_MIN,
	TPS65910_REG_RTC_ALARM_HOUR,
	TPS65910_REG_RTC_ALARM_DAY,
	TPS65910_REG_RTC_ALARM_MONTH,
	TPS65910_REG_RTC_ALARM_YEAR,
	TPS65910_REG_RTC_CTRL			= 0x10,
	TPS65910_REG_RTC_STAT,
	TPS65910_REG_RTC_INT,
	TPS65910_REG_RTC_COMP_LSB,
	TPS65910_REG_RTC_COMP_MSB,
	TPS65910_REG_RTC_RESISTOR_PRG,
	TPS65910_REG_RTC_RESET_STAT,
	TPS65910_REG_BACKUP1,
	TPS65910_REG_BACKUP2,
	TPS65910_REG_BACKUP3,
	TPS65910_REG_BACKUP4,
	TPS65910_REG_BACKUP5,
	TPS65910_REG_PUADEN,
	TPS65910_REG_REF,
	TPS65910_REG_VRTC,
	TPS65910_REG_VIO			= 0x20,
	TPS65910_REG_VDD1,
	TPS65910_REG_VDD1_VAL,
	TPS65910_REG_VDD1_VAL_SR,
	TPS65910_REG_VDD2,
	TPS65910_REG_VDD2_VAL,
	TPS65910_REG_VDD2_VAL_SR,
	TPS65910_REG_VDD3,
	TPS65910_REG_VDIG1			= 0x30,
	TPS65910_REG_VDIG2,
	TPS65910_REG_VAUX1,
	TPS65910_REG_VAUX2,
	TPS65910_REG_VAUX33,
	TPS65910_REG_VMMC,
	TPS65910_REG_VPLL,
	TPS65910_REG_VDAC,
	TPS65910_REG_THERM,
	TPS65910_REG_BATTERY_BACKUP_CHARGE,
	TPS65910_REG_DCDC_CTRL			= 0x3e,
	TPS65910_REG_DEVICE_CTRL,
	TPS65910_REG_DEVICE_CTRL2,
	TPS65910_REG_SLEEP_KEEP_LDO_ON,
	TPS65910_REG_SLEEP_KEEP_RES_ON,
	TPS65910_REG_SLEEP_SET_LDO_OFF,
	TPS65910_REG_SLEEP_SET_RES_OFF,
	TPS65910_REG_EN1_LDO_ASS,
	TPS65910_REG_EM1_SMPS_ASS,
	TPS65910_REG_EN2_LDO_ASS,
	TPS65910_REG_EM2_SMPS_ASS,
	TPS65910_REG_INT_STAT			= 0x50,
	TPS65910_REG_INT_MASK,
	TPS65910_REG_INT_STAT2,
	TPS65910_REG_INT_MASK2,
	TPS65910_REG_GPIO			= 0x60,
	TPS65910_REG_JTAGREVNUM			= 0x80,
	TPS65910_NUM_REGS
};

/* chip supplies */
enum {
	TPS65910_SUPPLY_VCCIO	= 0x00,
	TPS65910_SUPPLY_VCC1,
	TPS65910_SUPPLY_VCC2,
	TPS65910_SUPPLY_VCC3,
	TPS65910_SUPPLY_VCC4,
	TPS65910_SUPPLY_VCC5,
	TPS65910_SUPPLY_VCC6,
	TPS65910_SUPPLY_VCC7,
	TPS65910_NUM_SUPPLIES
};

/* regulator unit numbers */
enum {
	TPS65910_UNIT_VRTC = 0x00,
	TPS65910_UNIT_VIO,
	TPS65910_UNIT_VDD1,
	TPS65910_UNIT_VDD2,
	TPS65910_UNIT_VDD3,
	TPS65910_UNIT_VDIG1,
	TPS65910_UNIT_VDIG2,
	TPS65910_UNIT_VPLL,
	TPS65910_UNIT_VDAC,
	TPS65910_UNIT_VAUX1,
	TPS65910_UNIT_VAUX2,
	TPS65910_UNIT_VAUX33,
	TPS65910_UNIT_VMMC,
};

/* platform data */
struct tps65910_regulator_pdata {
	u32 supply;	/* regulator supply voltage in uV */
	uint unit;	/* unit-address according to DT */
};

/* driver names */
#define TPS65910_BUCK_DRIVER	"tps65910_buck"
#define TPS65910_BOOST_DRIVER	"tps65910_boost"
#define TPS65910_LDO_DRIVER	"tps65910_ldo"
#define TPS65910_RST_DRIVER	"tps65910_rst"

/* tps65911 i2c registers */
enum {
	TPS65911_REG_VIO			= 0x20,
	TPS65911_REG_VDD1,
	TPS65911_REG_VDD1_OP,
	TPS65911_REG_VDD1_SR,
	TPS65911_REG_VDD2,
	TPS65911_REG_VDD2_OP,
	TPS65911_REG_VDD2_SR,
	TPS65911_REG_VDDCTRL,
	TPS65911_REG_VDDCTRL_OP,
	TPS65911_REG_VDDCTRL_SR,
	TPS65911_REG_LDO1			= 0x30,
	TPS65911_REG_LDO2,
	TPS65911_REG_LDO5,
	TPS65911_REG_LDO8,
	TPS65911_REG_LDO7,
	TPS65911_REG_LDO6,
	TPS65911_REG_LDO4,
	TPS65911_REG_LDO3,
};

#define TPS65911_VDD_NUM		4
#define TPS65911_LDO_NUM		8

#define TPS65911_VDD_VOLT_MAX		1500000
#define TPS65911_VDD_VOLT_MIN		600000
#define TPS65911_VDD_VOLT_BASE		562500

#define TPS65911_LDO_VOLT_MAX		3300000
#define TPS65911_LDO_VOLT_BASE		800000

#define TPS65911_LDO_SEL_MASK		(0x3f << 2)

#define TPS65911_LDO124_VOLT_MAX_HEX	0x32
#define TPS65911_LDO358_VOLT_MAX_HEX	0x19
#define TPS65911_LDO358_VOLT_MIN_HEX	0x02

#define TPS65911_LDO124_VOLT_STEP	50000
#define TPS65911_LDO358_VOLT_STEP	100000

#define TPS65911_VDD_DRIVER		"tps65911_vdd"
#define TPS65911_LDO_DRIVER		"tps65911_ldo"

#endif /* __TPS65910_PMIC_H_ */
