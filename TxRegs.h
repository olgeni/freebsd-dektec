//#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*# TxRegs.h #*#*#*#*#*#*#*#*#* (C) 2000-2003 DEKTEC

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- License -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
// This program is free software; You can freely use/modify this source code in any way
// you desire, including for commercial applications.
//

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Change History -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
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

static inline int Dta1xxTxGetGenCtrlReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val;
	READ_LONG (val, tag, handle, base + DTA1XX_TX_REG_GENCTRL);
	return val;
}

static inline void Dta1xxTxSetGenCtrlReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t val)
{
	WRITE_LONG (val, tag, handle, base + DTA1XX_TX_REG_GENCTRL);
}

static inline void Dta1xxTxGenCtrlRegSetPE (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nEna)
{
	int32_t val = Dta1xxTxGetGenCtrlReg (tag, handle, base);
	if (nEna==1) {
		val |= DTA1XX_TX_GENCTRL_PE;
	} else {
		val &= ~DTA1XX_TX_GENCTRL_PE;
	}
	Dta1xxTxSetGenCtrlReg (tag, handle, base, val);
}

static inline void Dta1xxTxGenCtrlRegSetPRE (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nEna)
{
	int32_t val = Dta1xxTxGetGenCtrlReg (tag, handle, base);
	if (nEna==1) {
		val |= DTA1XX_TX_GENCTRL_PRE;
	} else {
		val &= ~DTA1XX_TX_GENCTRL_PRE;
	}
	Dta1xxTxSetGenCtrlReg (tag, handle, base, val);
}

static inline void Dta1xxTxGenCtrlRegReset (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetGenCtrlReg (tag, handle, base);
	val |= DTA1XX_TX_GENCTRL_RESET;
	Dta1xxTxSetGenCtrlReg (tag, handle, base, val);
}

static inline int Dta1xxTxGenCtrlRegGetFirmwareRev (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetGenCtrlReg (tag, handle, base);
	val &= DTA1XX_TX_GENCTRL_ALTERAREV;
	return (val>>8);
}

static inline int Dta1xxTxGenCtrlRegGetTypeNumber (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetGenCtrlReg (tag, handle, base);
	val &= DTA1XX_TX_GENCTRL_TYPENUM;
	return (val>>16);
}

static inline int Dta1xxTxGetTxCtrlReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val;
	READ_LONG (val, tag, handle, base + DTA1XX_TX_REG_TXCTRL);
	return val;
}

static inline void Dta1xxTxSetTxCtrlReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t val)
{
	WRITE_LONG (val, tag, handle, base + DTA1XX_TX_REG_TXCTRL);
}

static inline int Dta1xxTxCtrlRegGetTxMode (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int nTxMode;
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	nTxMode = (val & DTA1XX_TXCTRL_TXMODE);
	nTxMode |= ((val & DTA1XX_TXCTRL_TXMODE_EXT)>>1);
	return nTxMode;
}

static inline void Dta1xxTxCtrlRegSetTxMode (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nTxMode)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	val &= ~(DTA1XX_TXCTRL_TXMODE_EXT | DTA1XX_TXCTRL_TXMODE);
	val |= nTxMode&0x3;
	val |= (nTxMode&0x4) << 1;
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline int Dta1xxTxCtrlRegGetBurstMode (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	val &= DTA1XX_TXCTRL_BURSTMODE;
	return (val >> 2);
}

static inline void Dta1xxTxCtrlRegSetBurstMode (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nEna)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	if (nEna==1) {
		val |= DTA1XX_TXCTRL_BURSTMODE;
	} else {
		val &= ~DTA1XX_TXCTRL_BURSTMODE;
	}
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline int Dta1xxTxCtrlRegGetPckStuff (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	val &= DTA1XX_TXCTRL_PCKSTUFF;
	return (val >> 4);
}

static inline void Dta1xxTxCtrlRegSetPckStuff (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nEna)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	if (nEna==1) {
		val |= DTA1XX_TXCTRL_PCKSTUFF;
	} else {
		val &= ~DTA1XX_TXCTRL_PCKSTUFF;
	}
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline int Dta1xxTxCtrlRegGetTxCtrl (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	val &= DTA1XX_TXCTRL_TXCTRL;
	return (val>>5);
}

static inline void Dta1xxTxCtrlRegSetTxCtrl (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nTxCtrl)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	val &= ~DTA1XX_TXCTRL_TXCTRL;
	val |= (nTxCtrl&0x3) << 5 ;
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline int Dta1xxTxCtrlRegGetTxDis (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	val &= DTA1XX_TXCTRL_TXDIS;
	return (val>>7);
}


static inline void Dta1xxTxCtrlRegSetTxDis (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nDis)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	if (nDis==1) {
		val |= DTA1XX_TXCTRL_TXDIS;
	} else {
		val &= ~DTA1XX_TXCTRL_TXDIS;
	}
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline void Dta1xxTxCtrlRegSetPerIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nEna)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	if (nEna==1) {
		val |= DTA1XX_TXCTRL_PERINT_EN;
	} else {
		val &= ~DTA1XX_TXCTRL_PERINT_EN;
	}
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline void Dta1xxTxCtrlRegSetUflIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nEna)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	if (nEna==1) {
		val |= DTA1XX_TXCTRL_UFLINT_EN;
	} else {
		val &= ~DTA1XX_TXCTRL_UFLINT_EN;
	}
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline void Dta1xxTxCtrlRegSetSyncIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nEna)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	if (nEna==1) {
		val |= DTA1XX_TXCTRL_SYNCINT_EN;
	} else {
		val &= ~DTA1XX_TXCTRL_SYNCINT_EN;
	}
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline void Dta1xxTxCtrlRegSetShortIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nEna)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	if (nEna==1) {
		val |= DTA1XX_TXCTRL_SHORTINT_EN;
	} else {
		val &= ~DTA1XX_TXCTRL_SHORTINT_EN;
	}
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline void Dta1xxTxCtrlRegSetThrIntEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nEna)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	if (nEna==1) {
		val |= DTA1XX_TXCTRL_THRINT_EN;
	} else {
		val &= ~DTA1XX_TXCTRL_THRINT_EN;
	}
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline int Dta1xxTxCtrlRegGetUseExtClk (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	val &= DTA1XX_TXCTRL_USE_EXTCLOCK;
	return (val >> 16);
}

static inline void Dta1xxTxCtrlRegSetUseExtClk (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nUse)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	if (1==nUse) {
		val |= DTA1XX_TXCTRL_USE_EXTCLOCK;
	} else {
		val &= ~DTA1XX_TXCTRL_USE_EXTCLOCK;
	}
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline void Dta1xxTxCtrlRegSetEnaPwr (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nEna)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	if (nEna==1) {
		val |= DTA1XX_TXCTRL_ENAPWR;
	} else {
		val &= ~DTA1XX_TXCTRL_ENAPWR;
	}
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline void Dta1xxTxLedControl (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nLedCtrl)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	val &= ~(DTA1XX_TXCTRL_LEDCTRL | DTA1XX_TXCTRL_GREENLED | DTA1XX_TXCTRL_REDLED);
	val |= (nLedCtrl & 0x7) << 19;
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline void Dta1xxTxClrFifo (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	val |= DTA1XX_TXCTRL_CLEARFIFO;
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline void Dta1xxTxChannelReset (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	val |= DTA1XX_TXCTRL_TXRESET;
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline void Dta1xxTxCtrlSetTxAsiInv (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nEna)
{
	int32_t val = Dta1xxTxGetTxCtrlReg (tag, handle, base);
	if (nEna==1) {
		val |= DTA1XX_TXCTRL_TXINVASI;
	} else {
		val &= ~DTA1XX_TXCTRL_TXINVASI;
	}
	Dta1xxTxSetTxCtrlReg (tag, handle, base, val);
}

static inline int Dta1xxTxGetTxStatusReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val;
	READ_LONG (val, tag, handle, base + DTA1XX_TX_REG_TXSTATUS);
	return val;
}

static inline void Dta1xxTxSetTxStatusReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t val)
{
	WRITE_LONG (val, tag, handle, base + DTA1XX_TX_REG_TXSTATUS);
}

static inline int Dta1xxTxStatusRegGetFifoFilled (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxStatusReg (tag, handle, base);
	if (0!=(val & DTA1XX_TXSTAT_FIFOFILLED)) {
		return 1;
	} else {
		return 0;
	}
}

static inline int Dta1xxTxStatusRegGetSdramSize (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxStatusReg (tag, handle, base);
	val &= DTA1XX_TXSTAT_SDRAMSIZE;
	return (val << 4);
}

static inline int Dta1xxTxStatusRegGetPerInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxStatusReg (tag, handle, base);
	if (0!=(val & DTA1XX_TXSTAT_PERINT)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxTxStatusRegClrPerInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	Dta1xxTxSetTxStatusReg (tag, handle, base, DTA1XX_TXSTAT_PERINT);
}

static inline int Dta1xxTxStatusRegGetUflInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxStatusReg (tag, handle, base);
	if (0!=(val & DTA1XX_TXSTAT_UFLINT)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxTxStatusRegClrUflInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	Dta1xxTxSetTxStatusReg (tag, handle, base, DTA1XX_TXSTAT_UFLINT);
}

static inline int Dta1xxTxStatusRegGetSyncInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxStatusReg (tag, handle, base);
	if (0!=(val & DTA1XX_TXSTAT_SYNCINT)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxTxStatusRegClrSyncInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	Dta1xxTxSetTxStatusReg (tag, handle, base, DTA1XX_TXSTAT_SYNCINT);
}

static inline int Dta1xxTxStatusRegGetShortInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxStatusReg (tag, handle, base);
	if (0!=(val & DTA1XX_TXSTAT_SHORTINT)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxTxStatusRegClrShortInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	Dta1xxTxSetTxStatusReg (tag, handle, base, DTA1XX_TXSTAT_SHORTINT);
}

static inline int Dta1xxTxStatusRegGetThrInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetTxStatusReg (tag, handle, base);
	if (0!=(val & DTA1XX_TXSTAT_THRINT)) {
		return 1;
	} else {
		return 0;
	}
}

static inline void Dta1xxTxStatusRegClrThrInt (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	Dta1xxTxSetTxStatusReg (tag, handle, base, DTA1XX_TXSTAT_THRINT);
}

static inline int Dta1xxTxGetTxClockReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val;
	READ_LONG (val, tag, handle, base + DTA1XX_TX_REG_TXCLOCK);
	return val;
}

static inline void Dta1xxTxSetTxClockReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t val)
{
	WRITE_LONG (val, tag, handle, base + DTA1XX_TX_REG_TXCLOCK);
}

static inline int Dta1xxTxGetClkCountReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val;
	READ_LONG (val, tag, handle, base + DTA1XX_TX_REG_CLOCKCNT);
	return val;
}

static inline int Dta1xxTxGetFifoSizeReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val;
	READ_LONG (val, tag, handle, base + DTA1XX_TX_REG_FIFOSIZE);
	return val;
}

static inline void Dta1xxTxSetFifoSizeReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t val)
{
	WRITE_LONG (val, tag, handle, base + DTA1XX_TX_REG_FIFOSIZE);
}

static inline int Dta1xxTxGetFifoLoadReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val;
	READ_LONG (val, tag, handle, base + DTA1XX_TX_REG_FIFOLOAD);
	return val;
}

static inline int Dta1xxTxGetDiagReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val;
	READ_LONG (val, tag, handle, base + DTA1XX_TX_REG_DIAG);
	return val;
}

static inline void Dta1xxTxSetDiagReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t val)
{
	WRITE_LONG (val, tag, handle, base + DTA1XX_TX_REG_DIAG);
}

static inline int Dta1xxTxDiagRegGetSfData (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetDiagReg (tag, handle, base);
	val &= DTA1XX_TXDIAG_SFDATA;
	return val;
}

static inline int Dta1xxTxDiagRegGetLoopBack (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetDiagReg (tag, handle, base);
	val &= DTA1XX_TXDIAG_LOOPBACK;
	return (val >> 8);
}

static inline int Dta1xxTxDiagRegSetLoopBack (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t nEna)
{
	int32_t val = Dta1xxTxGetDiagReg (tag, handle, base);
	if (0 != nEna) {
		val |= DTA1XX_TXDIAG_LOOPBACK;
	} else {
		val &= ~DTA1XX_TXDIAG_LOOPBACK;
	}
	Dta1xxTxSetDiagReg (tag, handle, base, val);
	return 0;
}

static inline int Dta1xxTxDiagRegGetSfDtValid (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetDiagReg (tag, handle, base);
	if (0!=(val & DTA1XX_TXDIAG_SFDTVALID)) {
		return 1;
	} else {
		return 0;
	}
}

static inline int Dta1xxTxDiagRegGetDmaReq (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetDiagReg (tag, handle, base);
	if (0!=(val & DTA1XX_TXDIAG_DMAREQ)) {
		return 1;
	} else {
		return 0;
	}
}

static inline int Dta1xxTxDiagRegGetBfCanBurst (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetDiagReg (tag, handle, base);
	if (0!=(val & DTA1XX_TXDIAG_BFCANBURST)) {
		return 1;
	} else {
		return 0;
	}
}

static inline int Dta1xxTxDiagRegGetSfCanBurst (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetDiagReg (tag, handle, base);
	if (0!=(val & DTA1XX_TXDIAG_SFCANBURST)) {
		return 1;
	} else {
		return 0;
	}
}

static inline int Dta1xxTxDiagRegGetSfLoad (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetDiagReg (tag, handle, base);
	val |= DTA1XX_TXDIAG_SFLOAD;
	return (val >> 14);
}

static inline int Dta1xxTxDiagRegGetBfLoad (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val = Dta1xxTxGetDiagReg (tag, handle, base);
	val |= DTA1XX_TXDIAG_BFLOAD;
	return (val >> 24);
}

static inline int Dta1xxTxGetLoopBackDataReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val;
	READ_LONG (val, tag, handle, base + DTA1XX_TX_REG_LOOPBKDATA);
	return val;
}

static inline int Dta1xxTxGetThreshCtrlReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	int32_t val;
	READ_LONG (val, tag, handle, base + DTA1XX_TX_REG_THRESHCTRL);
	return val;
}

static inline void Dta1xxTxSetThreshCtrlReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t val)
{
	WRITE_LONG (val, tag, handle, base + DTA1XX_TX_REG_THRESHCTRL);
}

static inline void Dta1xxTxSetFifoDataReg (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t val)
{
	WRITE_LONG (val, tag, handle, base + DTA1XX_TX_REG_FIFO_FIRST);
}

static inline int Dta1xxTxCtrlRegGetOutputEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base)
{
	return ((Dta1xxTxGetTxCtrlReg (tag, handle, base) & DTA1XX_TXCTRL_OUT_EN) != 0) ? 1 : 0;
}

static inline void Dta1xxTxCtrlRegSetOutputEn (bus_space_tag_t tag, bus_space_handle_t handle, int32_t base, int32_t enable)
{
	int32_t value = Dta1xxTxGetTxCtrlReg (tag, handle, base);

	if (enable != 0)
		value |=  DTA1XX_TXCTRL_OUT_EN;
	else
		value &= ~DTA1XX_TXCTRL_OUT_EN;

	Dta1xxTxSetTxCtrlReg (tag, handle, base, value);
}

#endif // __TX_REGS_H
