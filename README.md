freebsd-dektec
==============

A FreeBSD driver for some [DekTec](http://dektec.com/) ASI boards (DTA-140, DTA-145, DTA-2145).

- dektec.c - the actual device driver code
- dektec.h - lots of IOCTL codes used in the driver
- Dta1xxCodes.h - codes and constants from DekTek
- Dta1xxRegs.h - use to include GenRegs.h, Helpers.h, RxRegs.h, TxRegs.h.
- Helpers.h - helper functions from DekTek, adapted to FreeBSD (write byte, read word, etc.)
- GenRegs.h - definitions related to the generic control register, from DekTek, adapted to FreeBSD
- RxRegs.h - definitions related to the RX control register, from DekTek, adapted to FreeBSD
- TxRegs.h - definitions related to the TX control register, from DekTek, adapted to FreeBSD
- Plx905x.h - constants for the PLX 905x PCI controller chip (9056 in our case).

Basically, the .h files are the same as the headers distributed with the
DekTek driver for Linux, minus a few adaptations related to FreeBSD (mostly
busdma(9) and bus_space(9)).

Pretty much everything happens in dektec.c. The driver is not compatible
with DekTek's DTAPI but it supports a read/write interface with polling.

To understand what is going on you will need at least the following:

- Some understanding of
  [ASI](http://en.wikipedia.org/wiki/Asynchronous_serial_interface) and
  [MPEG transport streams](http://en.wikipedia.org/wiki/MPEG_transport_stream).

- A PLX 9056 data sheet, for everything related to DMA. Newer boards use an
  FPGA with the same interface.

- Boards register maps from DekTek, or the Linux driver source code, to
  check the value of register base addresses, etc.

To try things out:

- An ASI source or ASI analyzer to try things out with an actual signal.

- A valid MPEG2 transport stream to test the output functions. You can make one with ffmpeg.

Bugs
====

- None if you use it correctly :) uptimes of years have been observed in
  production, but the range of operations performed by the client software
  is quite narrow so you'd better test everything _carefully_ in your
  environment.

- Lots of boards are missing, but I can only support the models that I am
  actually using. The DTA-140 could be probably considered legacy and you
  will not be able to order it anymore. Lots of code is related to the
  handling of this board, which was the first to be implemented.

- SDI operations are not yet supported.

- You _might_ have noticed that there's no documentation.

- USB devices are not supported. Not sure how much work it could be.

Todo
====

- Carefully review the dmamap callbacks for edge cases.

- Split the TX and RX channels into multiple devices. Then we should be
  able to add support for input- and output-only boards with multiple
  channels.

- Let userland software configure the programmable input/output channel on
  the DTA-145. Right now it is hardcoded as input.

- Add a few sysctl values to set the default parameters. This could be used
  to make streams accessible to shell scripts / pipes and to use netcat or ssh as
  a transport.

- Do something useful with the led, possibly from userland.
