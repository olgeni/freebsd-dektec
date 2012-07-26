/* -*- c-file-style: "bsd"; indent-tabs-mode: t; -*- */

//#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*# TxRegs.h #*#*#*#*#*#*#*#*#* (C) 2000-2003 DEKTEC

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- License -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
// This program is free software; You can freely use/modify this source code in any way
// you desire, including for commercial applications.
//

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Change History -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//      olgeni  11-02-2004      Hijacked to FreeBSD :)
//      MG      15-11-2002      Created

#ifndef __TX_REGS_H
#define __TX_REGS_H

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ TX register offset +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

#define DTA1XX_TX_REG_GENCTRL                   0x0000
#define DTA1XX_TX_REG_TXCTRL                    0x0004
#define DTA1XX_TX_REG_TXSTATUS                  0x0008
#define DTA1XX_TX_REG_TXCLOCK                   0x000C
#define DTA1XX_TX_REG_CLOCKCNT                  0x0010
#define DTA1XX_TX_REG_FIFOSIZE                  0x0014
#define DTA1XX_TX_REG_FIFOLOAD                  0x0018
#define DTA1XX_TX_REG_DIAG                      0x001C
#define DTA1XX_TX_REG_LOOPBKDATA                0x0020
#define DTA1XX_TX_REG_THRESHCTRL                0x0024
#define DTA1XX_TX_REG_FIFO_FIRST                0x0040
#define DTA1XX_TX_REG_FIFO_LAST                 0x007C

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.- TX register bit/field masks -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

// Tx general control

#define DTA1XX_TX_GENCTRL_PE                    0x00000001
#define DTA1XX_TX_GENCTRL_PRE                   0x00000002
#define DTA1XX_TX_GENCTRL_RESET                 0x00000004
#define DTA1XX_TX_GENCTRL_ALTERAREV             0x0000FF00
#define DTA1XX_TX_GENCTRL_TYPENUM               0x00FF0000

// Tx control register

#define DTA1XX_TXCTRL_TXMODE                    0x00000003
#define DTA1XX_TXCTRL_BURSTMODE                 0x00000004
#define DTA1XX_TXCTRL_TXMODE_EXT                0x00000008
#define DTA1XX_TXCTRL_PCKSTUFF                  0x00000010
#define DTA1XX_TXCTRL_TXCTRL                    0x00000060
#define DTA1XX_TXCTRL_TXDIS                     0x00000080
#define DTA1XX_TXCTRL_PERINT_EN                 0x00000100
#define DTA1XX_TXCTRL_UFLINT_EN                 0x00000200
#define DTA1XX_TXCTRL_SYNCINT_EN                0x00000400
#define DTA1XX_TXCTRL_SHORTINT_EN               0x00000800
#define DTA1XX_TXCTRL_THRINT_EN                 0x00001000
#define DTA1XX_TXCTRL_USE_EXTCLOCK              0x00010000
#define DTA1XX_TXCTRL_ENAPWR                    0x00020000
#define DTA1XX_TXCTRL_SHORTERROR                0x00040000
#define DTA1XX_TXCTRL_LEDCTRL                   0x00080000
#define DTA1XX_TXCTRL_GREENLED                  0x00100000
#define DTA1XX_TXCTRL_REDLED                    0x00200000
#define DTA1XX_TXCTRL_CLEARFIFO                 0x00400000
#define DTA1XX_TXCTRL_TXRESET                   0x00800000
#define DTA1XX_TXCTRL_TXINVASI                  0x01000000
#define DTA1XX_TXCTRL_SDI_MODE  		0x02000000
#define DTA1XX_TXCTRL_OUT_EN			0x08000000

// Tx status register

#define DTA1XX_TXSTAT_FIFOFILLED                0x00000001
#define DTA1XX_TXSTAT_SDRAMSIZE                 0x000000F0
#define DTA1XX_TXSTAT_PERINT                    0x00000100
#define DTA1XX_TXSTAT_UFLINT                    0x00000200
#define DTA1XX_TXSTAT_SYNCINT                   0x00000400
#define DTA1XX_TXSTAT_SHORTINT                  0x00000800
#define DTA1XX_TXSTAT_THRINT                    0x00001000

// Tx diagnostic register

#define DTA1XX_TXDIAG_SFDATA                    0x000000FF
#define DTA1XX_TXDIAG_LOOPBACK                  0x00000100
#define DTA1XX_TXDIAG_SFDTVALID                 0x00000200
#define DTA1XX_TXDIAG_BF_FULL                   0x00000400
#define DTA1XX_TXDIAG_DMAREQ                    0x00000800
#define DTA1XX_TXDIAG_BFCANBURST                0x00001000
#define DTA1XX_TXDIAG_SFCANBURST                0x00002000
#define DTA1XX_TXDIAG_SFLOAD                    0x00FC0000
#define DTA1XX_TXDIAG_BFLOAD                    0xFF000000

// Tx threshold control register

#define DTA1XX_TXTHRCTRL_UPD_DONE               0x00000001
#define DTA1XX_TXTHRCTRL_CMPB                   0x00000002
#define DTA1XX_TXTHRCTRL_CMPA                   0x00000004
#define DTA1XX_TXTHRCTRL_A_N_B                  0x00000008
#define DTA1XX_TXTHRCTRL_THRESHA                0x0000FF00
#define DTA1XX_TXTHRCTRL_THRESHB                0x00FF0000

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ Tx register operations +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

static inline int
dta1xx_tx_get_gen_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_TX_REG_GENCTRL);
}

static inline void
dta1xx_tx_set_gen_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_TX_REG_GENCTRL, value);
}

static inline void
dta1xx_tx_gen_ctrl_reg_set_pe (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_tx_get_gen_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_TX_GENCTRL_PE;
	else
		value &= ~DTA1XX_TX_GENCTRL_PE;

	dta1xx_tx_set_gen_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_tx_gen_ctrl_reg_set_pre (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_tx_get_gen_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_TX_GENCTRL_PRE;
	else
		value &= ~DTA1XX_TX_GENCTRL_PRE;

	dta1xx_tx_set_gen_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_tx_gen_ctrl_reg_reset (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_gen_ctrl_reg (tag, handle, base);

	value |= DTA1XX_TX_GENCTRL_RESET;

	dta1xx_tx_set_gen_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_tx_gen_ctrl_reg_get_firmware_rev (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_gen_ctrl_reg (tag, handle, base);

	value &= DTA1XX_TX_GENCTRL_ALTERAREV;

	return (value >> 8);
}

static inline int
dta1xx_tx_gen_ctrl_reg_get_type_number (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_gen_ctrl_reg (tag, handle, base);

	value &= DTA1XX_TX_GENCTRL_TYPENUM;

	return (value >> 16);
}

static inline int
dta1xx_tx_get_tx_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_TX_REG_TXCTRL);
}

static inline void
dta1xx_tx_set_tx_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_TX_REG_TXCTRL, value);
}

static inline int
dta1xx_tx_ctrl_reg_get_tx_mode (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	int txmode = (value & DTA1XX_TXCTRL_TXMODE);

	txmode |= ((value & DTA1XX_TXCTRL_TXMODE_EXT) >> 1);

	return txmode;
}

static inline void
dta1xx_tx_ctrl_reg_set_tx_mode (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t txmode)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	value &= ~(DTA1XX_TXCTRL_TXMODE_EXT | DTA1XX_TXCTRL_TXMODE);
	value |= txmode & 0x3;
	value |= (txmode & 0x4) << 1;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_tx_ctrl_reg_get_burst_mode (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	value &= DTA1XX_TXCTRL_BURSTMODE;

	return (value >> 2);
}

static inline void
dta1xx_tx_ctrl_reg_set_burst_mode (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_TXCTRL_BURSTMODE;
	else
		value &= ~DTA1XX_TXCTRL_BURSTMODE;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_tx_ctrl_reg_get_pck_stuff (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	value &= DTA1XX_TXCTRL_PCKSTUFF;

	return (value >> 4);
}

static inline void
dta1xx_tx_ctrl_reg_set_pck_stuff (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_TXCTRL_PCKSTUFF;
	else
		value &= ~DTA1XX_TXCTRL_PCKSTUFF;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_tx_ctrl_reg_get_tx_ctrl (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	value &= DTA1XX_TXCTRL_TXCTRL;

	return (value >> 5);
}

static inline void
dta1xx_tx_ctrl_reg_set_tx_ctrl (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t txctrl)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	value &= ~DTA1XX_TXCTRL_TXCTRL;
	value |= (txctrl & 0x3) << 5 ;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_tx_ctrl_reg_get_tx_dis (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	value &= DTA1XX_TXCTRL_TXDIS;

	return (value >> 7);
}

static inline void
dta1xx_tx_ctrl_reg_set_tx_dis (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t disable)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	if (disable)
		value |= DTA1XX_TXCTRL_TXDIS;
	else
		value &= ~DTA1XX_TXCTRL_TXDIS;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_tx_ctrl_reg_set_per_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_TXCTRL_PERINT_EN;
	else
		value &= ~DTA1XX_TXCTRL_PERINT_EN;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_tx_ctrl_reg_set_ufl_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_TXCTRL_UFLINT_EN;
	else
		value &= ~DTA1XX_TXCTRL_UFLINT_EN;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_tx_ctrl_reg_set_sync_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_TXCTRL_SYNCINT_EN;
	else
		value &= ~DTA1XX_TXCTRL_SYNCINT_EN;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_tx_ctrl_reg_set_short_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_TXCTRL_SHORTINT_EN;
	else
		value &= ~DTA1XX_TXCTRL_SHORTINT_EN;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_tx_ctrl_reg_set_thr_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_TXCTRL_THRINT_EN;
	else
		value &= ~DTA1XX_TXCTRL_THRINT_EN;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_tx_ctrl_reg_get_use_ext_clk (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	value &= DTA1XX_TXCTRL_USE_EXTCLOCK;

	return (value >> 16);
}

static inline void
dta1xx_tx_ctrl_reg_set_use_ext_clk (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t use)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	if (use)
		value |= DTA1XX_TXCTRL_USE_EXTCLOCK;
	else
		value &= ~DTA1XX_TXCTRL_USE_EXTCLOCK;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_tx_ctrl_reg_set_ena_pwr (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_TXCTRL_ENAPWR;
	else
		value &= ~DTA1XX_TXCTRL_ENAPWR;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_tx_led_control (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t ledctrl)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	value &= ~(DTA1XX_TXCTRL_LEDCTRL | DTA1XX_TXCTRL_GREENLED | DTA1XX_TXCTRL_REDLED);
	value |= (ledctrl & 0x7) << 19;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_tx_clr_fifo (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	value |= DTA1XX_TXCTRL_CLEARFIFO;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_tx_channel_reset (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	value |= DTA1XX_TXCTRL_TXRESET;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_tx_ctrl_set_tx_asi_inv (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_TXCTRL_TXINVASI;
	else
		value &= ~DTA1XX_TXCTRL_TXINVASI;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_tx_get_tx_status_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_TX_REG_TXSTATUS);
}

static inline void
dta1xx_tx_set_tx_status_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_TX_REG_TXSTATUS, value);
}

static inline int
dta1xx_tx_status_reg_get_fifo_filled (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_tx_get_tx_status_reg (tag, handle, base) & DTA1XX_TXSTAT_FIFOFILLED);
}

static inline int
dta1xx_tx_status_reg_get_sdram_size (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_tx_status_reg (tag, handle, base);

	value &= DTA1XX_TXSTAT_SDRAMSIZE;

	return (value << 4);
}

static inline int
dta1xx_tx_status_reg_get_per_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_tx_get_tx_status_reg (tag, handle, base) & DTA1XX_TXSTAT_PERINT);
}

static inline void
dta1xx_tx_status_reg_clr_per_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	dta1xx_tx_set_tx_status_reg (tag, handle, base, DTA1XX_TXSTAT_PERINT);
}

static inline int
dta1xx_tx_status_reg_get_ufl_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_tx_get_tx_status_reg (tag, handle, base) & DTA1XX_TXSTAT_UFLINT);
}

static inline void
dta1xx_tx_status_reg_clr_ufl_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	dta1xx_tx_set_tx_status_reg (tag, handle, base, DTA1XX_TXSTAT_UFLINT);
}

static inline int
dta1xx_tx_status_reg_get_sync_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_tx_get_tx_status_reg (tag, handle, base) & DTA1XX_TXSTAT_SYNCINT);
}

static inline void
dta1xx_tx_status_reg_clr_sync_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	dta1xx_tx_set_tx_status_reg (tag, handle, base, DTA1XX_TXSTAT_SYNCINT);
}

static inline int
dta1xx_tx_status_reg_get_short_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_tx_get_tx_status_reg (tag, handle, base) & DTA1XX_TXSTAT_SHORTINT);
}

static inline void
dta1xx_tx_status_reg_clr_short_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	dta1xx_tx_set_tx_status_reg (tag, handle, base, DTA1XX_TXSTAT_SHORTINT);
}

static inline int
dta1xx_tx_status_reg_get_thr_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_tx_get_tx_status_reg (tag, handle, base) & DTA1XX_TXSTAT_THRINT);
}

static inline void
dta1xx_tx_status_reg_clr_thr_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	dta1xx_tx_set_tx_status_reg (tag, handle, base, DTA1XX_TXSTAT_THRINT);
}

static inline int
dta1xx_tx_get_tx_clock_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_TX_REG_TXCLOCK);
}

static inline void
dta1xx_tx_set_tx_clock_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_TX_REG_TXCLOCK, value);
}

static inline int
dta1xx_tx_get_clk_count_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_TX_REG_CLOCKCNT);
}

static inline int
dta1xx_tx_get_fifo_size_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_TX_REG_FIFOSIZE);
}

static inline void
dta1xx_tx_set_fifo_size_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_TX_REG_FIFOSIZE, value);
}

static inline int
dta1xx_tx_get_fifo_load_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_TX_REG_FIFOLOAD);
}

static inline int
dta1xx_tx_get_diag_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_TX_REG_DIAG);
}

static inline void
dta1xx_tx_set_diag_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_TX_REG_DIAG, value);
}

static inline int
dta1xx_tx_diag_reg_get_sf_data (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_diag_reg (tag, handle, base);

	value &= DTA1XX_TXDIAG_SFDATA;

	return value;
}

static inline int
dta1xx_tx_diag_reg_get_loop_back (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_diag_reg (tag, handle, base);

	value &= DTA1XX_TXDIAG_LOOPBACK;

	return (value >> 8);
}

static inline void
dta1xx_tx_diag_reg_set_loop_back (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_tx_get_diag_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_TXDIAG_LOOPBACK;
	else
		value &= ~DTA1XX_TXDIAG_LOOPBACK;

	dta1xx_tx_set_diag_reg (tag, handle, base, value);
}

static inline int
dta1xx_tx_diag_reg_get_sf_dt_valid (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_tx_get_diag_reg (tag, handle, base) & DTA1XX_TXDIAG_SFDTVALID);
}

static inline int
dta1xx_tx_diag_reg_get_dma_req (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_tx_get_diag_reg (tag, handle, base) & DTA1XX_TXDIAG_DMAREQ);
}

static inline int
dta1xx_tx_diag_reg_get_bf_can_burst (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_tx_get_diag_reg (tag, handle, base) & DTA1XX_TXDIAG_BFCANBURST);
}

static inline int
dta1xx_tx_diag_reg_get_sf_can_burst (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_tx_get_diag_reg (tag, handle, base) & DTA1XX_TXDIAG_SFCANBURST);
}

static inline int
dta1xx_tx_diag_reg_get_sf_load (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_diag_reg (tag, handle, base);

	value |= DTA1XX_TXDIAG_SFLOAD;

	return (value >> 14);
}

static inline int
dta1xx_tx_diag_reg_get_bf_load (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_tx_get_diag_reg (tag, handle, base);

	value |= DTA1XX_TXDIAG_BFLOAD;

	return (value >> 24);
}

static inline int
dta1xx_tx_get_loop_back_data_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_TX_REG_LOOPBKDATA);
}

static inline int
dta1xx_tx_get_thresh_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_TX_REG_THRESHCTRL);
}

static inline void
dta1xx_tx_set_thresh_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_TX_REG_THRESHCTRL, value);
}

static inline void
dta1xx_tx_set_fifo_data_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_TX_REG_FIFO_FIRST, value);
}

static inline int
dta1xx_tx_ctrl_reg_get_output_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_tx_get_tx_ctrl_reg (tag, handle, base) & DTA1XX_TXCTRL_OUT_EN) ? 1 : 0;
}

static inline void
dta1xx_tx_ctrl_reg_set_output_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_tx_get_tx_ctrl_reg (tag, handle, base);

	if (enable)
		value |=  DTA1XX_TXCTRL_OUT_EN;
	else
		value &= ~DTA1XX_TXCTRL_OUT_EN;

	dta1xx_tx_set_tx_ctrl_reg (tag, handle, base, value);
}

#endif // __TX_REGS_H
