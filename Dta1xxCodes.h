//#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* Dta1xxCodes.h *#*#*#*#*#*#*#*# (C) 2000-2003 DEKTEC

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- License -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
// This program is free software; You can freely use/modify this source code in any way
// you desire, including for commercial applications.
//

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Change History -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//      MG      2003.06.30      Added definitions for reception mode store MP2 and for timestamping
//      MG      21-10-2002      Created 

#ifndef __DTA1XXCODES_H
#define __DTA1XXCODES_H

typedef unsigned long DTA1XX_RESULT;

//+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ Common control/status codes +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Channel Definitions -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#define  DTA1XX_GEN_REGS                -1      // Special value for GENERIC registers
#define  DTA1XX_TS_TX_CHANNEL           0       // Transport-Stream Transmit Channel
#define  DTA1XX_TS_RX_CHANNEL           1       // Transport-Stream Receive Channel

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Hardware-Function Types -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#define  DTA1XX_TS_OUTPUT               1
#define  DTA1XX_TS_INPUT                2

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- LED Control -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#define  DTA1XX_LED_OFF                 1
#define  DTA1XX_LED_GREEN               3
#define  DTA1XX_LED_RED                 5
#define  DTA1XX_LED_YELLOW              7
#define  DTA1XX_LED_HARDWARE            0

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Loop-Back Mode -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#define  DTA1XX_NO_LOOPBACK             0
#define  DTA1XX_LOOPBACK_MODE           1

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Reset Mode -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#define  DTA1XX_RST_CLEARFIFO           0
#define  DTA1XX_RST_CHANNEL             1

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Power Mode -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#define  DTA1XX_POWER_OFF               0
#define  DTA1XX_POWER_ON                1

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Target Adapter Present -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#define  DTA1XX_NO_CONNECTION           0
#define  DTA1XX_DVB_SPI_SINK            1       // For output channels
#define  DTA1XX_DVB_SPI_SOURCE          1       // For input channels
#define  DTA1XX_TARGET_PRESENT          2
#define  DTA1XX_TARGET_UNKNOWN          3

//=+=+=+=+=+=+=+=+=+=+=+=+ Transmit channel control/status codes +=+=+=+=+=+=+=+=+=+=+=+=+

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Packet Transmit Mode -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#define  DTA1XX_TXMODE_188              0
#define  DTA1XX_TXMODE_204              1
#define  DTA1XX_TXMODE_ADD16            2
#define  DTA1XX_TXMODE_RAW              3
#define  DTA1XX_TXMODE_192              4       // Supported on DTA-102 Fw Rev>= 2
#define  DTA1XX_TXMODE_130              5       // Supported on DTA-102 Fw Rev>= 7
#define  DTA1XX_TXMODE_MIN16            6       // Supported on DTA-102 Fw Rev>= 8
                                                //              DTA-100 Fw Rev >=5
                                                //              DTA-140 Fw Rev >=0
#define  DTA1XX_TXMODE_MASK             0x0F    // Mask for TxMode without burst flag
#define  DTA1XX_TXMODE_BURST            0x10    // Can be OR-ed with one of 188/192/204/ADD16/RAW

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Burst mode -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#define  DTA1XX_BURSTMODE_OFF           0
#define  DTA1XX_BURSTMODE_ON            1

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Packet stuff mode -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#define  DTA1XX_STUFFMODE_OFF           0
#define  DTA1XX_STUFFMODE_ON            1

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Transmit Polarity -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#define  DTA1XX_TXPOL_NORMAL            0
#define  DTA1XX_TXPOL_INVERTED          1

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Status Flags -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#define  DTA1XX_TX_DMA_PENDING          1
#define  DTA1XX_TX_FIFO_UFL             2
#define  DTA1XX_TX_SYNC_ERR             4
#define  DTA1XX_TX_READBACK_ERR         8
#define  DTA1XX_TX_TARGET_ERR           16

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Transmit Control -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#define  DTA1XX_TXCTRL_IDLE             0
#define  DTA1XX_TXCTRL_HOLD             1
#define  DTA1XX_TXCTRL_SEND             3

//+=+=+=+=+=+=+=+=+=+=+=+=+ Receive channel control/status codes +=+=+=+=+=+=+=+=+=+=+=+=+

//-.-.-.-.-.-.-.-.-.-.-.-.-.- DVB/ASI Polarity-Control Status -.-.-.-.-.-.-.-.-.-.-.-.-.-.
#define  DTA1XX_ASIINV_NORMAL           0
#define  DTA1XX_ASIINV_INVERT           1

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- DVB/ASI Input-Clock Lock -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#define  DTA1XX_ASI_NOLOCK              0
#define  DTA1XX_ASI_INLOCK              1

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Clock Detector -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#define  DTA1XX_CLKDET_FAIL             0
#define  DTA1XX_CLKDET_OK               1

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Input Rate Ok -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#define  DTA1XX_INPRATE_LOW             0
#define  DTA1XX_INPRATE_OK              1

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- #Invalid Bytes per Packet -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#define  DTA1XX_NUMINV_NONE             0
#define  DTA1XX_NUMINV_16               1
#define  DTA1XX_NUMINV_OTHER            2

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Packet Size -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#define  DTA1XX_PCKSIZE_INV             0
#define  DTA1XX_PCKSIZE_188             2
#define  DTA1XX_PCKSIZE_204             3

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Receive Control -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#define  DTA1XX_RXCTRL_IDLE             0
#define  DTA1XX_RXCTRL_RCV              1

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Receive Mode -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#define  DTA1XX_RXMODE_ST188            0
#define  DTA1XX_RXMODE_ST204            1
#define  DTA1XX_RXMODE_STMP2            2
#define  DTA1XX_RXMODE_STRAW            3
#define  DTA1XX_RX_TIMESTAMP            8

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Status Flags -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#define  DTA1XX_RX_DMA_PENDING          1
#define  DTA1XX_RX_FIFO_OVF             2
#define  DTA1XX_RX_SYNC_ERR             4
#define  DTA1XX_RX_RATE_OVF             8

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Clock-Generator Modes -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#define  DTA1XX_TXCLOCK_INTERNAL        0
#define  DTA1XX_TXCLOCK_EXTERNAL        1

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Equaliser Settings -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
#define  DTA1XX_EQUALISER_OFF           0
#define  DTA1XX_EQUALISER_ON            1

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Polarity Control -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-
#define  DTA1XX_POLARITY_AUTO           0
#define  DTA1XX_POLARITY_NORMAL         2
#define  DTA1XX_POLARITY_INVERTED       3

//+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+ Result codes +=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+

// Feature not supported
#define  DTA1XX_NOT_SUPPORTED           -1

#define  DTA1XX_OK                      0
#define  DTA1XX_E                       0x1000
#define  DTA1XX_E_ATTACHED              (DTA1XX_E + 0)
#define  DTA1XX_E_BUF_TOO_SMALL         (DTA1XX_E + 1)
#define  DTA1XX_E_DEV_DRIVER            (DTA1XX_E + 2)
#define  DTA1XX_E_EEPROM_FULL           (DTA1XX_E + 3)
#define  DTA1XX_E_EEPROM_READ           (DTA1XX_E + 4)
#define  DTA1XX_E_EEPROM_WRITE          (DTA1XX_E + 5)
#define  DTA1XX_E_EEPROM_FORMAT         (DTA1XX_E + 6)
#define  DTA1XX_E_FIFO_FULL             (DTA1XX_E + 7)
#define  DTA1XX_E_IN_USE                (DTA1XX_E + 8)
#define  DTA1XX_E_INVALID_BUF           (DTA1XX_E + 9)
#define  DTA1XX_E_INVALID_CGMODE        (DTA1XX_E + 10)
#define  DTA1XX_E_INVALID_FLAGS         (DTA1XX_E + 11)
#define  DTA1XX_E_INVALID_MODE          (DTA1XX_E + 12)
#define  DTA1XX_E_INVALID_RATE          (DTA1XX_E + 13)
#define  DTA1XX_E_INVALID_SIZE          (DTA1XX_E + 14)
#define  DTA1XX_E_KEYWORD               (DTA1XX_E + 15)
#define  DTA1XX_E_NO_DTA_CARD           (DTA1XX_E + 16)
#define  DTA1XX_E_NO_LOOPBACK           (DTA1XX_E + 17)
#define  DTA1XX_E_NO_SUCH_DEVICE        (DTA1XX_E + 18)
#define  DTA1XX_E_NO_SUCH_OUTPUT        (DTA1XX_E + 19)
#define  DTA1XX_E_NO_TS_OUTPUT          (DTA1XX_E + 20)
#define  DTA1XX_E_NOT_ATTACHED          (DTA1XX_E + 21)
#define  DTA1XX_E_NOT_FOUND             (DTA1XX_E + 22)
#define  DTA1XX_E_NOT_SUPPORTED         (DTA1XX_E + 23)
#define  DTA1XX_E_PCICARD               (DTA1XX_E + 24)
#define  DTA1XX_E_TOO_LONG              (DTA1XX_E + 25)
#define  DTA1XX_E_UNDERFLOW             (DTA1XX_E + 26)
#define  DTA1XX_E_NO_SUCH_INPUT         (DTA1XX_E + 27)
#define  DTA1XX_E_NO_TS_INPUT           (DTA1XX_E + 28)

#endif // __DTA1XXCODES_H
