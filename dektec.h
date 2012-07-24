/*-
 * Copyright (c) 2012 Giacomo Olgeni. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef __DEKTEC_H
#define __DEKTEC_H

#include <sys/ioccom.h>

#define IOCTL_Dta1xxGenCtrlRegReset              _IO  ('D',  0)
#define IOCTL_Dta1xxGenCtrlRegGetFirmwareRev     _IOR ('D',  1, int)

#define IOCTL_Dta1xxRxGenCtrlRegGetFirmwareRev   _IOR ('D', 104, int)
#define IOCTL_Dta1xxRxGenCtrlRegGetTypeNumber    _IOR ('D',   2, int)
#define IOCTL_Dta1xxRxCtrlRegGetRxMode           _IOR ('D',   3, int)
#define IOCTL_Dta1xxRxCtrlRegSetRxMode           _IOW ('D',   4, int)
#define IOCTL_Dta1xxRxCtrlRegGetRxCtrl           _IOR ('D', 200, int)
#define IOCTL_Dta1xxRxCtrlRegSetRxCtrl           _IOW ('D', 201, int)

#define IOCTL_Dta1xxRxCtrlRegGetAsiInv           _IOR ('D',  5, int)
#define IOCTL_Dta1xxRxCtrlRegSetAsiInv           _IOW ('D',  6, int)
#define IOCTL_Dta1xxRxCtrlRegGetEqualise         _IO  ('D',  7)
#define IOCTL_Dta1xxRxCtrlRegSetEqualise         _IOW ('D',  8, int)
#define IOCTL_Dta1xxRxCtrlRegGetEnaPwr           _IOR ('D',  9, int)
#define IOCTL_Dta1xxRxCtrlRegSetEnaPwr           _IOW ('D', 10, int)
#define IOCTL_Dta1xxRxClrFifo                    _IO  ('D', 11)
#define IOCTL_Dta1xxRxStatusRegGetPckSize        _IOR ('D', 12, int)
#define IOCTL_Dta1xxRxStatusRegGetNumInv         _IOR ('D', 13, int)
#define IOCTL_Dta1xxRxStatusRegGetSdramSize      _IOR ('D', 14, int)
#define IOCTL_Dta1xxRxStatusRegGetAsiCD          _IOR ('D', 15, int)
#define IOCTL_Dta1xxRxStatusRegGetAsiLock        _IOR ('D', 16, int)
#define IOCTL_Dta1xxRxStatusRegGetRateOk         _IOR ('D', 17, int)
#define IOCTL_Dta1xxRxStatusRegGetAsiInv         _IOR ('D', 18, int)
#define IOCTL_Dta1xxRxGetFifoLoadReg             _IOR ('D', 19, int)

#define IOCTL_Dta1xxTxGenCtrlRegGetFirmwareRev   _IOR ('D', 20, int)
#define IOCTL_Dta1xxTxGenCtrlRegGetTypeNumber    _IOR ('D', 21, int)
#define IOCTL_Dta1xxTxCtrlRegGetTxMode           _IOR ('D', 22, int)
#define IOCTL_Dta1xxTxCtrlRegSetTxMode           _IOW ('D', 23, int)
#define IOCTL_Dta1xxTxCtrlRegGetBurstMode        _IOR ('D', 24, int)
#define IOCTL_Dta1xxTxCtrlRegSetBurstMode        _IOW ('D', 25, int)
#define IOCTL_Dta1xxTxCtrlRegGetPckStuff         _IOR ('D', 26, int)
#define IOCTL_Dta1xxTxCtrlRegSetPckStuff         _IOW ('D', 27, int)
#define IOCTL_Dta1xxTxCtrlRegGetTxCtrl           _IOR ('D', 28, int)
#define IOCTL_Dta1xxTxCtrlRegSetTxCtrl           _IOW ('D', 29, int)
#define IOCTL_Dta1xxTxCtrlRegSetEnaPwr           _IOW ('D', 30, int)
#define IOCTL_Dta1xxTxClrFifo                    _IO  ('D', 31)
#define IOCTL_Dta1xxTxCtrlSetTxAsiInv            _IOW ('D', 32, int)
#define IOCTL_Dta1xxTxStatusRegGetFifoFilled     _IOR ('D', 33, int)
#define IOCTL_Dta1xxTxStatusRegGetSdramSize      _IOR ('D', 34, int)
#define IOCTL_Dta1xxTxGetTxClockReg              _IOR ('D', 35, int)
#define IOCTL_Dta1xxTxSetTxClockReg              _IOW ('D', 36, int)
#define IOCTL_Dta1xxTxGetFifoSizeReg             _IOR ('D', 37, int)
#define IOCTL_Dta1xxTxSetFifoSizeReg             _IOW ('D', 38, int)
#define IOCTL_Dta1xxTxGetFifoLoadReg             _IOR ('D', 39, int)

#define IOCTL_Dta1xxTxSetWatermark               _IOW ('D', 40, int)
#define IOCTL_Dta1xxTxGetWatermark               _IOR ('D', 41, int)
#define IOCTL_Dta1xxRxSetWatermark               _IOW ('D', 42, int)
#define IOCTL_Dta1xxRxGetWatermark               _IOR ('D', 43, int)

#endif /* __DEKTEC_H */
