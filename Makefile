# $Colby: erlang/drv_dektec/BSDMakefile,v 1.5 2008/05/23 09:47:17 olgeni Exp $

KMOD=	dektec
SRCS=	dektec.c \
	dektec.h \
	Dta1xxCodes.h \
	Dta1xxRegs.h \
	GenRegs.h \
	Helpers.h \
	Plx905x.h \
	RxRegs.h \
	TxRegs.h \
	device_if.h \
	bus_if.h \
	pci_if.h

.include <bsd.kmod.mk>

check-syntax:
	$(CC) $(CFLAGS) -o /dev/null -S $(CHK_SOURCES)
