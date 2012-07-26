/* -*- c-file-style: "bsd"; indent-tabs-mode: t; -*- */

//#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* GenRegs.h *#*#*#*#*#*#*#*#*# (C) 2000-2003 DEKTEC

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- License -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
// This program is free software; You can freely use/modify this source code in any way
// you desire, including for commercial applications.
//

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Change History -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//      olgeni  11-02-2004      Hijacked to FreeBSD :)
//      MG      2003.04.23      Added functions for writing to PE and PRE bit-field
//      MG      16-01-2003      Correct definitions of some DTA1XX_GENCTRL_ constants
//      MG      25-11-2002      Created

//+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ General register offset +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

#define DTA1XX_GENERAL_BASE_ADDRESS 0x0000

// Generic Registers: BYTE offset

#define DTA1XX_GEN_REG_GENCTRL     0x0000
#define DTA1XX_GEN_REG_GENSTATUS   0x0004
#define DTA1XX_GEN_REG_PROGRAMMING 0x0008
#define DTA1XX_GEN_REG_REFCLKCNT   0x000C
#define DTA1XX_GEN_REG_EPCSCTRL    0x0010
#define DTA1XX_GEN_REG_EPCSDATA    0x0014
#define DTA1XX_GEN_REG_REFCLKCNTH  0x0018
#define DTA1XX_GEN_REG_SPICTRL     0x0024
#define DTA1XX_GEN_REG_SPIDATA     0x0028
#define DTA1XX_GEN_REG_CONTROL0    0x0030
#define DTA1XX_GEN_REG_CONTROL1    0x0034
#define DTA1XX_GEN_REG_STATUS0     0x0038
#define DTA1XX_GEN_REG_STATUS1     0x003C
#define DTA1XX_GEN_REG_LICSERIAL   0x0070
#define DTA1XX_GEN_REG_LICCODE     0x0074
#define DTA1XX_GEN_REG_LICSTATUS1  0x0078
#define DTA1XX_GEN_REG_LICSTATUS2  0x007C

//-.-.-.-.-.-.-.-.-.-.-.-.-.- General register bit/field masks -.-.-.-.-.-.-.-.-.-.-.-.-.-

// General control register

#define DTA1XX_GENCTRL_PE         0x00000001
#define DTA1XX_GENCTRL_PRE        0x00000002
#define DTA1XX_GENCTRL_RESET      0x00000004
#define DTA1XX_GENCTRL_PERINT_EN  0x00000010
#define DTA1XX_GENCTRL_PERINT_VAL 0x000000E0
#define DTA1XX_GENCTRL_ALTERAREV  0x0000FF00
#define DTA1XX_GENCTRL_TYPENUM    0x00FF0000
#define DTA1XX_GENCTRL_LEDCTRL    0x01000000
#define DTA1XX_GENCTRL_GREENLED   0x02000000
#define DTA1XX_GENCTRL_REDLED     0x04000000

// General status register

#define DTA1XX_GENSTAT_PERINT 0x00000010

// Programming register

#define DTA1XX_PROG_TRST   0x00000001
#define DTA1XX_PROG_TDO    0x00000002
#define DTA1XX_PROG_TMS    0x00000004
#define DTA1XX_PROG_TCK    0x00000008
#define DTA1XX_PROG_TDI    0x00000010
#define DTA1XX_PROG_PRGEPC 0x00000020

// DMA registers

#define DTA1XX_DMA_DESCPTR_REG   0x004
#define DTA1XX_DMA_CMDSTAT_REG   0x008
#define DTA1XX_DMA_PCIUPADDR_REG 0x00C
#define DTA1XX_DMA_TIMEOUT_REG   0x014

// Watchdog control

#define DTA1XX_GEN_CONTROL1_WATCHDOG 0x00000001

//+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ General register operations +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

static inline int
dta1xx_gen_get_gen_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_GEN_REG_GENCTRL);
}

static inline void
dta1xx_gen_set_gen_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_GEN_REG_GENCTRL, value);
}

static inline void
dta1xx_gen_ctrl_reg_set_pe (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_gen_get_gen_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_GENCTRL_PE;
	else
		value &= ~DTA1XX_GENCTRL_PE;

	dta1xx_gen_set_gen_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_gen_ctrl_reg_get_pe (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_gen_get_gen_ctrl_reg (tag, handle, base) & DTA1XX_GENCTRL_PE);
}

static inline void
dta1xx_gen_ctrl_reg_set_pre (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_gen_get_gen_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_GENCTRL_PRE;
	else
		value &= ~DTA1XX_GENCTRL_PRE;

	dta1xx_gen_set_gen_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_gen_ctrl_reg_get_pre (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_gen_get_gen_ctrl_reg (tag, handle, base) & DTA1XX_GENCTRL_PRE);
}

static inline void
dta1xx_gen_ctrl_reg_reset (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_gen_get_gen_ctrl_reg (tag, handle, base);

	value |= DTA1XX_GENCTRL_RESET;

	dta1xx_gen_set_gen_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_gen_ctrl_reg_get_firmware_rev (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_gen_get_gen_ctrl_reg (tag, handle, base);

	value &= DTA1XX_GENCTRL_ALTERAREV;

	return ((value >> 8) & 0xFF);
}

static inline int
dta1xx_gen_ctrl_reg_get_per_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_gen_get_gen_ctrl_reg (tag, handle, base) & DTA1XX_GENCTRL_PERINT_EN);
}

static inline void
dta1xx_gen_ctrl_reg_set_per_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_gen_get_gen_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_GENCTRL_PERINT_EN;
	else
		value &= ~DTA1XX_GENCTRL_PERINT_EN;

	dta1xx_gen_set_gen_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_gen_ctrl_reg_get_per_int_val (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_gen_get_gen_ctrl_reg (tag, handle, base) & DTA1XX_GENCTRL_PERINT_VAL) >> 5;
}

static inline void
dta1xx_gen_ctrl_reg_set_per_int_val (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t intval)
{
	int32_t value = dta1xx_gen_get_gen_ctrl_reg (tag, handle, base);

	value &= ~DTA1XX_GENCTRL_PERINT_VAL;
	value |= (intval & 0x7) << 5;

	dta1xx_gen_set_gen_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_gen_led_control (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t ledctrl)
{
	int32_t value = dta1xx_gen_get_gen_ctrl_reg (tag, handle, base);

	value &= ~(DTA1XX_GENCTRL_LEDCTRL | DTA1XX_GENCTRL_GREENLED | DTA1XX_GENCTRL_REDLED);
	value |= (ledctrl & 0x7) << 24;

	dta1xx_gen_set_gen_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_gen_get_gen_status_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_GEN_REG_GENSTATUS);
}

static inline void
dta1xx_gen_set_gen_status_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_GEN_REG_GENSTATUS, value);
}

static inline int
dta1xx_gen_status_reg_get_per_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_gen_get_gen_status_reg (tag, handle, base) & DTA1XX_GENSTAT_PERINT);
}

static inline void
dta1xx_gen_status_reg_clr_per_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	dta1xx_gen_set_gen_status_reg (tag, handle, base, DTA1XX_GENSTAT_PERINT);
}

static inline int32_t
dta1xx_gen_get_control1_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_GEN_REG_CONTROL1);
}

static inline void
dta1xx_gen_set_control1_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_GEN_REG_CONTROL1, value);
}

static inline void
dta1xx_gen_toggle_watchdog (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_gen_get_control1_reg (tag, handle, base);

	if (value & DTA1XX_GEN_CONTROL1_WATCHDOG)
		value = value & ~DTA1XX_GEN_CONTROL1_WATCHDOG;
	else
		value = value | DTA1XX_GEN_CONTROL1_WATCHDOG;

	dta1xx_gen_set_control1_reg (tag, handle, base, value);
}

static inline void
dta1xx_gen_pulse_watchdog (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	/* Pulse watchdog 1->0->1 or 0->1->0 */

	int32_t value = dta1xx_gen_get_control1_reg (tag, handle, base);

	if (value & DTA1XX_GEN_CONTROL1_WATCHDOG)
		dta1xx_gen_set_control1_reg (tag, handle, base, value & ~DTA1XX_GEN_CONTROL1_WATCHDOG);
	else
		dta1xx_gen_set_control1_reg (tag, handle, base, value | DTA1XX_GEN_CONTROL1_WATCHDOG);

	dta1xx_gen_set_control1_reg (tag, handle, base, value);
}

static inline void
dta1xx_dma_timeout_set (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, unsigned int value)
{
	/* value = in 2^14 clock cycle increments */

	int enable = (value != 0);

	value = value & 0xFF;

	if (enable)
		value = value | (1 << 8);

	bus_space_write_4 (tag, handle, base + DTA1XX_DMA_TIMEOUT_REG, value);
}
