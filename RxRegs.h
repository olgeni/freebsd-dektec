/* -*- c-file-style: "bsd"; indent-tabs-mode: t; -*- */

//#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*# RxRegs.h #*#*#*#*#*#*#*#*#* (C) 2000-2003 DEKTEC

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- License -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
// This program is free software; You can freely use/modify this source code in any way
// you desire, including for commercial applications.
//

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Change History -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//      olgeni  11-02-2004      Hijacked to FreeBSD :)
//      MG      15-11-2002      Created

#ifndef __RX_REGS_H
#define __RX_REGS_H

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ RX register offset +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

#define DTA1XX_RX_REG_GENCTRL                   0x0000
#define DTA1XX_RX_REG_RXCTRL                    0x0004
#define DTA1XX_RX_REG_RXSTATUS                  0x0008
#define DTA1XX_RX_REG_FIFOLOAD                  0x0018
#define DTA1XX_RX_REG_DIAG                      0x001C
#define DTA1XX_RX_REG_LOOPBKDATA                0x0020
#define DTA1XX_RX_REG_THRESHCTRL                0x0024
#define DTA1XX_RX_REG_PCKCOUNT                  0x0028
#define DTA1XX_RX_REG_CLKCOUNT                  0x002C
#define DTA1XX_RX_REG_VALIDCOUNT                0x0030
#define DTA1XX_RX_REG_VIOLCOUNT                 0x0034

#define DTA1XX_RX_REG_FIFO_FIRST                0x0040
#define DTA1XX_RX_REG_FIFO_LAST                 0x007C

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Rx register bit/field masks -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.

// Rx general control

#define DTA1XX_RX_GENCTRL_PE                    0x00000001
#define DTA1XX_RX_GENCTRL_PRE                   0x00000002
#define DTA1XX_RX_GENCTRL_RESET                 0x00000004
#define DTA1XX_RX_GENCTRL_ALTERAREV             0x0000FF00
#define DTA1XX_RX_GENCTRL_TYPENUM               0x00FF0000

// Rx control register

#define DTA1XX_RXCTRL_RXMODE                    0x00000003
#define DTA1XX_RXCTRL_ASIINV                    0x0000000C
#define DTA1XX_RXCTRL_EQUALISE                  0x00000010
#define DTA1XX_RXCTRL_RXCTRL                    0x00000020
#define DTA1XX_RXCTRL_PERINT_EN                 0x00000100
#define DTA1XX_RXCTRL_OVFINT_EN                 0x00000200
#define DTA1XX_RXCTRL_SYNCINT_EN                0x00000400
#define DTA1XX_RXCTRL_THRINT_EN                 0x00001000
#define DTA1XX_RXCTRL_RATEOVFINT_EN             0x00002000
#define DTA1XX_RXCTRL_ENAPWR                    0x00020000
#define DTA1XX_RXCTRL_LEDCTRL                   0x00080000
#define DTA1XX_RXCTRL_GREENLED                  0x00100000
#define DTA1XX_RXCTRL_REDLED                    0x00200000
#define DTA1XX_RXCTRL_CLEARFIFO                 0x00400000
#define DTA1XX_RXCTRL_RXRESET                   0x00800000

// Rx status register

#define DTA1XX_RXSTAT_PCKSIZE                   0x00000003
#define DTA1XX_RXSTAT_NUMINV                    0x0000000C
#define DTA1XX_RXSTAT_SDRAMSIZE                 0x000000F0
#define DTA1XX_RXSTAT_PERINT                    0x00000100
#define DTA1XX_RXSTAT_OVFINT                    0x00000200
#define DTA1XX_RXSTAT_SYNCINT                   0x00000400
#define DTA1XX_RXSTAT_THRINT                    0x00001000
#define DTA1XX_RXSTAT_RATEOVFINT                0x00002000
#define DTA1XX_RXSTAT_ASICD                     0x00004000
#define DTA1XX_RXSTAT_ASILOCK                   0x00008000
#define DTA1XX_RXSTAT_RATEOK                    0x00010000
#define DTA1XX_RXSTAT_ASI_INV                   0x00020000

// Rx diagnostic register

#define DTA1XX_RXDIAG_LOOPBACK                  0x00000100
#define DTA1XX_RXDIAG_RFRATEOVF                 0x00000400
#define DTA1XX_RXDIAG_SDFULL                    0x00000800

// Rx threshold control register

#define DTA1XX_RXTHRCTRL_UPD_DONE               0x00000001
#define DTA1XX_RXTHRCTRL_CMPB                   0x00000002
#define DTA1XX_RXTHRCTRL_CMPA                   0x00000004
#define DTA1XX_RXTHRCTRL_A_N_B                  0x00000008
#define DTA1XX_RXTHRCTRL_THRESHA                0x0000FF00
#define DTA1XX_RXTHRCTRL_THRESHB                0x00FF0000

// DMA Command/Status register

// NOTE: other fields in this register follow PCI905X definitions:
//   PCI905X_DMACSR_ENABLE, PCI905X_DMACSR_START, PCI905X_DMACSR_ABORT,
//   PCI905X_DMACSR_CLEARINT, PCI905X_DMACSR_DONE

#define DTA1XX_DMACSR_INTACT                    0x00000008

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ Rx register operations +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

static inline int
dta1xx_rx_get_gen_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, DTA1XX_RX_REG_GENCTRL);
}

static inline void
dta1xx_rx_set_gen_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, DTA1XX_RX_REG_GENCTRL, value);
}

static inline void
dta1xx_rx_gen_ctrl_reg_set_pe (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_rx_get_gen_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_RX_GENCTRL_PE;
	else
		value &= ~DTA1XX_RX_GENCTRL_PE;

	dta1xx_rx_set_gen_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_rx_gen_ctrl_reg_set_pre (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_rx_get_gen_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_RX_GENCTRL_PRE;
	else
		value &= ~DTA1XX_RX_GENCTRL_PRE;

	dta1xx_rx_set_gen_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_rx_gen_ctrl_reg_reset (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_rx_get_gen_ctrl_reg (tag, handle, base);

	value |= DTA1XX_RX_GENCTRL_RESET;

	dta1xx_rx_set_gen_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_rx_gen_ctrl_reg_get_firmware_rev (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_rx_get_gen_ctrl_reg (tag, handle, base);

	value &= DTA1XX_RX_GENCTRL_ALTERAREV;

	return (value >> 8);
}

static inline int
dta1xx_rx_gen_ctrl_reg_get_type_number (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_rx_get_gen_ctrl_reg (tag, handle, base);

	value &= DTA1XX_RX_GENCTRL_TYPENUM;

	return (value >> 16);
}

static inline int
dta1xx_rx_get_rx_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_RX_REG_RXCTRL);
}

static inline void
dta1xx_rx_set_rx_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_RX_REG_RXCTRL, value);
}

static inline int
dta1xx_rx_ctrl_reg_get_rx_mode (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	value &= DTA1XX_RXCTRL_RXMODE;

	return value;
}

static inline void
dta1xx_rx_ctrl_reg_set_rx_mode (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t mode)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	value &= ~DTA1XX_RXCTRL_RXMODE;
	value |= (mode & 0x3);

	dta1xx_rx_set_rx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_rx_ctrl_reg_get_asi_inv (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	value &= DTA1XX_RXCTRL_ASIINV;

	return (value >> 2);
}

static inline void
dta1xx_rx_ctrl_reg_set_asi_inv (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t invert)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	value &= ~DTA1XX_RXCTRL_ASIINV;
	value |= ((invert & 0x3) << 2);

	dta1xx_rx_set_rx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_rx_ctrl_reg_get_equalise (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_ctrl_reg (tag, handle, base) & DTA1XX_RXCTRL_EQUALISE);
}

static inline void
dta1xx_rx_ctrl_reg_set_equalise (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_RXCTRL_EQUALISE;
	else
		value &= ~DTA1XX_RXCTRL_EQUALISE;

	dta1xx_rx_set_rx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_rx_ctrl_reg_get_rx_ctrl (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_ctrl_reg (tag, handle, base) & DTA1XX_RXCTRL_RXCTRL);
}

static inline void
dta1xx_rx_ctrl_reg_set_rx_ctrl (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_RXCTRL_RXCTRL;
	else
		value &= ~DTA1XX_RXCTRL_RXCTRL;

	dta1xx_rx_set_rx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_rx_ctrl_reg_get_per_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_ctrl_reg (tag, handle, base) & DTA1XX_RXCTRL_PERINT_EN);
}

static inline void
dta1xx_rx_ctrl_reg_set_per_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_RXCTRL_PERINT_EN;
	else
		value &= ~DTA1XX_RXCTRL_PERINT_EN;

	dta1xx_rx_set_rx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_rx_ctrl_reg_get_ovf_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_ctrl_reg (tag, handle, base) & DTA1XX_RXCTRL_OVFINT_EN);
}

static inline void
dta1xx_rx_ctrl_reg_set_ovf_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_RXCTRL_OVFINT_EN;
	else
		value &= ~DTA1XX_RXCTRL_OVFINT_EN;

	dta1xx_rx_set_rx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_rx_ctrl_reg_get_sync_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_ctrl_reg (tag, handle, base) & DTA1XX_RXCTRL_SYNCINT_EN);
}

static inline void
dta1xx_rx_ctrl_reg_set_sync_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_RXCTRL_SYNCINT_EN;
	else
		value &= ~DTA1XX_RXCTRL_SYNCINT_EN;

	dta1xx_rx_set_rx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_rx_ctrl_reg_get_thr_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_ctrl_reg (tag, handle, base) & DTA1XX_RXCTRL_THRINT_EN);
}

static inline void
dta1xx_rx_ctrl_reg_set_thr_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_RXCTRL_THRINT_EN;
	else
		value &= ~DTA1XX_RXCTRL_THRINT_EN;

	dta1xx_rx_set_rx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_rx_ctrl_reg_get_rate_ovf_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_ctrl_reg (tag, handle, base) & DTA1XX_RXCTRL_RATEOVFINT_EN);
}

static inline void
dta1xx_rx_ctrl_reg_set_rate_ovf_int_en (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_RXCTRL_RATEOVFINT_EN;
	else
		value &= ~DTA1XX_RXCTRL_RATEOVFINT_EN;

	dta1xx_rx_set_rx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_rx_ctrl_reg_get_ena_pwr (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_ctrl_reg (tag, handle, base) & DTA1XX_RXCTRL_ENAPWR);
}

static inline void
dta1xx_rx_ctrl_reg_set_ena_pwr (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_RXCTRL_ENAPWR;
	else
		value &= ~DTA1XX_RXCTRL_ENAPWR;

	dta1xx_rx_set_rx_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_rx_led_control (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t ledctrl)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	value &= ~(DTA1XX_RXCTRL_LEDCTRL | DTA1XX_RXCTRL_GREENLED | DTA1XX_RXCTRL_REDLED);
	value |= (ledctrl & 0x7) << 19;

	dta1xx_rx_set_rx_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_rx_clr_fifo (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	value |= DTA1XX_RXCTRL_CLEARFIFO;

	dta1xx_rx_set_rx_ctrl_reg (tag, handle, base, value);
}

static inline void
dta1xx_rx_channel_reset (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_rx_get_rx_ctrl_reg (tag, handle, base);

	value |= DTA1XX_RXCTRL_RXRESET;

	dta1xx_rx_set_rx_ctrl_reg (tag, handle, base, value);
}

static inline int
dta1xx_rx_get_rx_status_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_RX_REG_RXSTATUS);
}

static inline void
dta1xx_rx_set_rx_status_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_RX_REG_RXSTATUS, value);
}

static inline int
dta1xx_rx_status_reg_get_pck_size (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_rx_get_rx_status_reg (tag, handle, base);

	value &= DTA1XX_RXSTAT_PCKSIZE;

	return value;
}

static inline int
dta1xx_rx_status_reg_get_num_inv (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_rx_get_rx_status_reg (tag, handle, base);

	value &= DTA1XX_RXSTAT_NUMINV;

	return (value >> 2);
}

static inline int
dta1xx_rx_status_reg_get_sdram_size (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_rx_get_rx_status_reg (tag, handle, base);

	value &= DTA1XX_RXSTAT_SDRAMSIZE;

	return (value >> 4);
}

static inline int
dta1xx_rx_status_reg_get_per_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_status_reg (tag, handle, base) & DTA1XX_RXSTAT_PERINT);
}

static inline void
dta1xx_rx_status_reg_clr_per_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	dta1xx_rx_set_rx_status_reg (tag, handle, base, DTA1XX_RXSTAT_PERINT);
}

static inline int
dta1xx_rx_status_reg_get_ovf_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_status_reg (tag, handle, base) & DTA1XX_RXSTAT_OVFINT);
}

static inline void
dta1xx_rx_status_reg_clr_ovf_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	dta1xx_rx_set_rx_status_reg (tag, handle, base, DTA1XX_RXSTAT_OVFINT);
}

static inline int
dta1xx_rx_status_reg_get_sync_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_status_reg (tag, handle, base) & DTA1XX_RXSTAT_SYNCINT);
}

static inline void
dta1xx_rx_status_reg_clr_sync_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	dta1xx_rx_set_rx_status_reg (tag, handle, base, DTA1XX_RXSTAT_SYNCINT);
}

static inline int
dta1xx_rx_status_reg_get_thr_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_status_reg (tag, handle, base) & DTA1XX_RXSTAT_THRINT);
}

static inline void
dta1xx_rx_status_reg_clr_thr_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	dta1xx_rx_set_rx_status_reg (tag, handle, base, DTA1XX_RXSTAT_THRINT);
}

static inline int
dta1xx_rx_status_reg_get_rate_ovf_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_status_reg (tag, handle, base) & DTA1XX_RXSTAT_RATEOVFINT);
}

static inline void
dta1xx_rx_status_reg_clr_rate_ovf_int (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	dta1xx_rx_set_rx_status_reg (tag, handle, base, DTA1XX_RXSTAT_RATEOVFINT);
}

static inline int
dta1xx_rx_status_reg_get_asi_cd (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_status_reg (tag, handle, base) & DTA1XX_RXSTAT_ASICD);
}

static inline int
dta1xx_rx_status_reg_get_asi_lock (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_status_reg (tag, handle, base) & DTA1XX_RXSTAT_ASILOCK);
}

static inline int
dta1xx_rx_status_reg_get_rate_ok (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_status_reg (tag, handle, base) & DTA1XX_RXSTAT_RATEOK);
}

static inline int
dta1xx_rx_status_reg_get_asi_inv (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_rx_status_reg (tag, handle, base) & DTA1XX_RXSTAT_ASI_INV);
}

static inline int
dta1xx_rx_get_fifo_load_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_RX_REG_FIFOLOAD);
}

static inline int
dta1xx_rx_get_diag_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_RX_REG_DIAG);
}

static inline void
dta1xx_rx_set_diag_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_RX_REG_DIAG, value);
}

static inline int
dta1xx_rx_diag_reg_get_loop_back (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = dta1xx_rx_get_diag_reg (tag, handle, base);

	value &= DTA1XX_RXDIAG_LOOPBACK;

	return (value >> 8);
}

static inline void
dta1xx_rx_diag_reg_set_loop_back (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = dta1xx_rx_get_diag_reg (tag, handle, base);

	if (enable)
		value |= DTA1XX_RXDIAG_LOOPBACK;
	else
		value &= ~DTA1XX_RXDIAG_LOOPBACK;

	dta1xx_rx_set_diag_reg (tag, handle, base, value);
}

static inline int
dta1xx_rx_diag_reg_get_rf_rate_ovf (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_diag_reg (tag, handle, base) & DTA1XX_RXDIAG_RFRATEOVF);
}

static inline int
dta1xx_rx_diag_reg_get_sd_full (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return (dta1xx_rx_get_diag_reg (tag, handle, base) & DTA1XX_RXDIAG_SDFULL);
}

static inline void
dta1xx_rx_set_loop_back_data (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_RX_REG_LOOPBKDATA, (value & 0xFF));
}

static inline int
dta1xx_rx_get_thresh_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_RX_REG_THRESHCTRL);
}

static inline void
dta1xx_rx_set_thresh_ctrl_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	bus_space_write_4 (tag, handle, base + DTA1XX_RX_REG_THRESHCTRL, value);
}

static inline int
dta1xx_rx_get_pck_count_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_RX_REG_PCKCOUNT);
}

static inline int
dta1xx_rx_get_clk_count_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_RX_REG_CLKCOUNT);
}

static inline int
dta1xx_rx_get_valid_count_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_RX_REG_VALIDCOUNT);
}

static inline int
dta1xx_rx_get_viol_count_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_RX_REG_VIOLCOUNT);
}

static inline int
dta1xx_rx_get_fifo_data_reg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return bus_space_read_4 (tag, handle, base + DTA1XX_RX_REG_FIFO_FIRST);
}

#endif // __RX_REGS_H
