//#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*# RxRegs.h #*#*#*#*#*#*#*#*#* (C) 2000-2003 DEKTEC

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- License -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
// This program is free software; You can freely use/modify this source code in any way
// you desire, including for commercial applications.
//

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Change History -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
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

static inline int Dta1xxRxGetGenCtrlReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value;
	READ_LONG (value, tag, handle, DTA1XX_RX_REG_GENCTRL);
	return value;
}

static inline void Dta1xxRxSetGenCtrlReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	WRITE_LONG (value, tag, handle, DTA1XX_RX_REG_GENCTRL);
}

static inline void Dta1xxRxGenCtrlRegSetPE (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = Dta1xxRxGetGenCtrlReg (tag, handle, base);
	if (enable == 1)
	{
		value |= DTA1XX_RX_GENCTRL_PE;
	}
	else
	{
		value &= ~DTA1XX_RX_GENCTRL_PE;
	}
	Dta1xxRxSetGenCtrlReg (tag, handle, base, value);
}

static inline void Dta1xxRxGenCtrlRegSetPRE (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = Dta1xxRxGetGenCtrlReg (tag, handle, base);
	if (enable==1) {
		value |= DTA1XX_RX_GENCTRL_PRE;
	} else {
		value &= ~DTA1XX_RX_GENCTRL_PRE;
	}
	Dta1xxRxSetGenCtrlReg (tag, handle, base, value);
}

static inline void Dta1xxRxGenCtrlRegReset (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetGenCtrlReg (tag, handle, base);
	value |= DTA1XX_RX_GENCTRL_RESET;
	Dta1xxRxSetGenCtrlReg (tag, handle, base, value);
}

static inline int Dta1xxRxGenCtrlRegGetFirmwareRev (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetGenCtrlReg (tag, handle, base);
	value &= DTA1XX_RX_GENCTRL_ALTERAREV;
	return (value>>8);
}

static inline int Dta1xxRxGenCtrlRegGetTypeNumber (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetGenCtrlReg (tag, handle, base);
	value &= DTA1XX_RX_GENCTRL_TYPENUM;
	return (value>>16);
}

static inline int Dta1xxRxGetRxCtrlReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value;
	READ_LONG (value, tag, handle, base + DTA1XX_RX_REG_RXCTRL);
	return value;
}

static inline void Dta1xxRxSetRxCtrlReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	WRITE_LONG (value, tag, handle, base + DTA1XX_RX_REG_RXCTRL);
}

static inline int Dta1xxRxCtrlRegGetRxMode (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	value &= DTA1XX_RXCTRL_RXMODE;
	return value;
}

static inline int Dta1xxRxCtrlRegSetRxMode (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nMode)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	value &= ~DTA1XX_RXCTRL_RXMODE;
	value |= (nMode&0x3);
	Dta1xxRxSetRxCtrlReg (tag, handle, base, value);
	return 0;
}

static inline int Dta1xxRxCtrlRegGetAsiInv (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	value &= DTA1XX_RXCTRL_ASIINV;
	return (value>>2);
}

static inline void Dta1xxRxCtrlRegSetAsiInv (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t invert)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	value &= ~DTA1XX_RXCTRL_ASIINV;
	value |= ((invert&0x3)<<2);
	Dta1xxRxSetRxCtrlReg (tag, handle, base, value);
}

static inline int Dta1xxRxCtrlRegGetEqualise (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXCTRL_EQUALISE)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxRxCtrlRegSetEqualise (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=enable) {
		value |= DTA1XX_RXCTRL_EQUALISE;
	} else {
		value &= ~DTA1XX_RXCTRL_EQUALISE;
	}
	Dta1xxRxSetRxCtrlReg (tag, handle, base, value);
}

static inline int Dta1xxRxCtrlRegGetRxCtrl (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXCTRL_RXCTRL)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxRxCtrlRegSetRxCtrl (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=enable) {
		value |= DTA1XX_RXCTRL_RXCTRL;
	} else {
		value &= ~DTA1XX_RXCTRL_RXCTRL;
	}
	Dta1xxRxSetRxCtrlReg (tag, handle, base, value);
}

static inline int Dta1xxRxCtrlRegGetPerIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXCTRL_PERINT_EN)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxRxCtrlRegSetPerIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=enable) {
		value |= DTA1XX_RXCTRL_PERINT_EN;
	} else {
		value &= ~DTA1XX_RXCTRL_PERINT_EN;
	}
	Dta1xxRxSetRxCtrlReg (tag, handle, base, value);
}

static inline int Dta1xxRxCtrlRegGetOvfIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXCTRL_OVFINT_EN)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxRxCtrlRegSetOvfIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=enable) {
		value |= DTA1XX_RXCTRL_OVFINT_EN;
	} else {
		value &= ~DTA1XX_RXCTRL_OVFINT_EN;
	}
	Dta1xxRxSetRxCtrlReg (tag, handle, base, value);
}

static inline int Dta1xxRxCtrlRegGetSyncIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0 != (value & DTA1XX_RXCTRL_SYNCINT_EN))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static inline void Dta1xxRxCtrlRegSetSyncIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=enable)
	{
		value |= DTA1XX_RXCTRL_SYNCINT_EN;
	}
	else
	{
		value &= ~DTA1XX_RXCTRL_SYNCINT_EN;
	}
	Dta1xxRxSetRxCtrlReg (tag, handle, base, value);
}

static inline int Dta1xxRxCtrlRegGetThrIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXCTRL_THRINT_EN))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static inline void Dta1xxRxCtrlRegSetThrIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=enable)
	{
		value |= DTA1XX_RXCTRL_THRINT_EN;
	}
	else
	{
		value &= ~DTA1XX_RXCTRL_THRINT_EN;
	}
	Dta1xxRxSetRxCtrlReg (tag, handle, base, value);
}

static inline int Dta1xxRxCtrlRegGetRateOvfIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXCTRL_RATEOVFINT_EN))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

static inline void Dta1xxRxCtrlRegSetRateOvfIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=enable) {
		value |= DTA1XX_RXCTRL_RATEOVFINT_EN;
	} else {
		value &= ~DTA1XX_RXCTRL_RATEOVFINT_EN;
	}
	Dta1xxRxSetRxCtrlReg (tag, handle, base, value);
}

static inline int Dta1xxRxCtrlRegGetEnaPwr (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXCTRL_ENAPWR)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxRxCtrlRegSetEnaPwr (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	if (0!=enable) {
		value |= DTA1XX_RXCTRL_ENAPWR;
	} else {
		value &= ~DTA1XX_RXCTRL_ENAPWR;
	}
	Dta1xxRxSetRxCtrlReg (tag, handle, base, value);
}

static inline void Dta1xxRxLedControl (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nLedCtrl)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	value &= ~(DTA1XX_RXCTRL_LEDCTRL | DTA1XX_RXCTRL_GREENLED | DTA1XX_RXCTRL_REDLED);
	value |= (nLedCtrl & 0x7) << 19;
	Dta1xxRxSetRxCtrlReg (tag, handle, base, value);
}

static inline void Dta1xxRxClrFifo (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	value |= DTA1XX_RXCTRL_CLEARFIFO;
	Dta1xxRxSetRxCtrlReg (tag, handle, base, value);
}

static inline void Dta1xxRxChannelReset (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxCtrlReg (tag, handle, base);
	value |= DTA1XX_RXCTRL_RXRESET;
	Dta1xxRxSetRxCtrlReg (tag, handle, base, value);
}

static inline int Dta1xxRxGetRxStatusReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value;
	READ_LONG (value, tag, handle, base + DTA1XX_RX_REG_RXSTATUS);
	return value;
}

static inline void Dta1xxRxSetRxStatusReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	WRITE_LONG (value, tag, handle, base + DTA1XX_RX_REG_RXSTATUS);
}

static inline int Dta1xxRxStatusRegGetPckSize (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxStatusReg (tag, handle, base);
	value &= DTA1XX_RXSTAT_PCKSIZE;
	return value;
}

static inline int Dta1xxRxStatusRegGetNumInv (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxStatusReg (tag, handle, base);
	value &= DTA1XX_RXSTAT_NUMINV;
	return (value>>2);
}

static inline int Dta1xxRxStatusRegGetSdramSize (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxStatusReg (tag, handle, base);
	value &= DTA1XX_RXSTAT_SDRAMSIZE;
	return (value>>4);
}


static inline int Dta1xxRxStatusRegGetPerInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxStatusReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXSTAT_PERINT)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxRxStatusRegClrPerInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	Dta1xxRxSetRxStatusReg (tag, handle, base, DTA1XX_RXSTAT_PERINT);
}

static inline int Dta1xxRxStatusRegGetOvfInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxStatusReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXSTAT_OVFINT)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxRxStatusRegClrOvfInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	Dta1xxRxSetRxStatusReg (tag, handle, base, DTA1XX_RXSTAT_OVFINT);
}

static inline int Dta1xxRxStatusRegGetSyncInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxStatusReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXSTAT_SYNCINT)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxRxStatusRegClrSyncInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	Dta1xxRxSetRxStatusReg (tag, handle, base, DTA1XX_RXSTAT_SYNCINT);
}

static inline int Dta1xxRxStatusRegGetThrInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxStatusReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXSTAT_THRINT)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxRxStatusRegClrThrInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	Dta1xxRxSetRxStatusReg (tag, handle, base, DTA1XX_RXSTAT_THRINT);
}

static inline int Dta1xxRxStatusRegGetRateOvfInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxStatusReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXSTAT_RATEOVFINT)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxRxStatusRegClrRateOvfInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	Dta1xxRxSetRxStatusReg (tag, handle, base, DTA1XX_RXSTAT_RATEOVFINT);
}

static inline int Dta1xxRxStatusRegGetAsiCD (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxStatusReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXSTAT_ASICD)) {
		return 1;
	} else {
		return 0;
	}
}

static inline int Dta1xxRxStatusRegGetAsiLock (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxStatusReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXSTAT_ASILOCK)) {
		return 1;
	} else {
		return 0;
	}
}

static inline int Dta1xxRxStatusRegGetRateOk (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxStatusReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXSTAT_RATEOK)) {
		return 1;
	} else {
		return 0;
	}
}

static inline int Dta1xxRxStatusRegGetAsiInv (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetRxStatusReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXSTAT_ASI_INV)) {
		return 1;
	} else {
		return 0;
	}
}

static inline int Dta1xxRxGetFifoLoadReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value;
	READ_LONG (value, tag, handle, base + DTA1XX_RX_REG_FIFOLOAD);
	return value;
}

static inline int Dta1xxRxGetDiagReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value;
	READ_LONG (value, tag, handle, base + DTA1XX_RX_REG_DIAG);
	return value;
}

static inline void Dta1xxRxSetDiagReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	WRITE_LONG (value, tag, handle, base + DTA1XX_RX_REG_DIAG);
}

static inline int Dta1xxRxDiagRegGetLoopBack (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetDiagReg (tag, handle, base);
	value &= DTA1XX_RXDIAG_LOOPBACK;
	return (value >> 8);
}

static inline int Dta1xxRxDiagRegSetLoopBack (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = Dta1xxRxGetDiagReg (tag, handle, base);
	if (0!=enable)
	{
		value |= DTA1XX_RXDIAG_LOOPBACK;
	}
	else
	{
		value &= ~DTA1XX_RXDIAG_LOOPBACK;
	}
	Dta1xxRxSetDiagReg (tag, handle, base, value);
	return 0;
}

static inline int Dta1xxRxDiagRegGetRfRateOvf (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetDiagReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXDIAG_RFRATEOVF)) {
		return 1;
	} else {
		return 0;
	}
}

static inline int Dta1xxRxDiagRegGetSdFull (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value = Dta1xxRxGetDiagReg (tag, handle, base);
	if (0!=(value & DTA1XX_RXDIAG_SDFULL)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxRxSetLoopBackData (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	WRITE_LONG ((value&0xFF), tag, handle, base + DTA1XX_RX_REG_LOOPBKDATA);
}

static inline int Dta1xxRxGetThreshCtrlReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value;
	READ_LONG (value, tag, handle, base + DTA1XX_RX_REG_THRESHCTRL);
	return value;
}

static inline void Dta1xxRxSetThreshCtrlReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t value)
{
	WRITE_LONG (value, tag, handle, base + DTA1XX_RX_REG_THRESHCTRL);
}

static inline int Dta1xxRxGetPckCountReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value;
	READ_LONG (value, tag, handle, base + DTA1XX_RX_REG_PCKCOUNT);
	return value;
}

static inline int Dta1xxRxGetClkCountReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value;
	READ_LONG (value, tag, handle, base + DTA1XX_RX_REG_CLKCOUNT);
	return value;
}

static inline int Dta1xxRxGetValidCountReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value;
	READ_LONG (value, tag, handle, base + DTA1XX_RX_REG_VALIDCOUNT);
	return value;
}

static inline int Dta1xxRxGetViolCountReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value;
	READ_LONG (value, tag, handle, base + DTA1XX_RX_REG_VIOLCOUNT);
	return value;
}

static inline int Dta1xxRxGetFifoDataReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t value;
	READ_LONG (value, tag, handle, base + DTA1XX_RX_REG_FIFO_FIRST);
	return value;
}

#endif // __RX_REGS_H
