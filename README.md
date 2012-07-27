freebsd-dektec
==============

A FreeBSD driver for some [DekTec](http://dektec.com/) ASI boards (DTA-140,
DTA-145, DTA-2145).

- dektec.c - the actual device driver code
- dektec.h - lots of IOCTL codes used in the driver
- Dta1xxCodes.h - codes and constants from DekTec
- Dta1xxRegs.h - use to include GenRegs.h, RxRegs.h and TxRegs.h.
- GenRegs.h - definitions related to the generic control register, from DekTec, adapted to FreeBSD
- RxRegs.h - definitions related to the RX control register, from DekTec, adapted to FreeBSD
- TxRegs.h - definitions related to the TX control register, from DekTec, adapted to FreeBSD
- Plx905x.h - constants for the PLX 905x PCI controller chip (9056 in our case).

Basically, the .h files are the same as the headers distributed with the
DekTec driver for Linux, minus a few adaptations related to FreeBSD (mostly
[busdma(9)](http://www.freebsd.org/cgi/man.cgi?query=busdma&apropos=0&sektion=0&manpath=FreeBSD+9.0-RELEASE&arch=default&format=html) and [bus\_space(9)](http://www.freebsd.org/cgi/man.cgi?query=bus_space&apropos=0&sektion=0&manpath=FreeBSD+9.0-RELEASE&arch=default&format=html)).

Pretty much everything happens in dektec.c. The driver is not compatible
with DekTec's DTAPI but it supports a read/write interface with polling.

To understand what is going on you will need at least some of the following:

- Some understanding of
  [ASI](http://en.wikipedia.org/wiki/Asynchronous_serial_interface) and
  [MPEG transport streams](http://en.wikipedia.org/wiki/MPEG_transport_stream).

- A PCI 9056BA Data Book, for everything related to DMA. Newer boards use
  an FPGA with the same interface.

- A copy of the original busdma paper:
  [A Machine-Independent DMA Framework for NetBSD](http://www.netbsd.org/docs/kernel/bus_dma.pdf).
  Especially check bus\_dmamap\_sync.

- Boards register maps from DekTec, or the Linux
  [driver source code](http://dektec.com/Downloads/Drivers.asp), to check
  the value of register base addresses, etc.

Bonus items:

- A document titled "_DVB/ASI Input+Output Adapter for PCI Bus_" from
  DekTec, which will provide a broad description of the DTA-140 operations.

- A copy of _ISO/IEC 13818 Part 1_ could help when developing userland
  software.

- If you are using DVB, the relevant ETSI standards that you can grab at
  [www.etsi.org](www.etsi.org).

To actually try things out:

- An ASI source and/or ASI analyzer to handle actual streams.

- A valid MPEG2 transport stream to test the output functions. You can make
  one with ffmpeg or grab it from a TV decoder that supports TS recording.

Bugs / gotchas
==============

- None if you use it correctly :) uptimes of years have been observed in
  production, but the range of operations performed by the client software
  is quite narrow so you'd better test everything _carefully_ in your
  environment.

- Only 188-byte packet are supported.

- Lots of boards are missing, but I can only support the models that I am
  actually using. The DTA-140 could be probably considered legacy and you
  will not be able to order it anymore. Lots of code is related to the
  handling of this board, which was the first to be implemented.

- SDI operations are not supported.

- USB devices are not supported (not sure how much work it could be).

- You _might_ have noticed that there's no documentation.

- Lots of constants may be unused, but you'd better keep them for future
  use.

Todo
====

- Carefully review the dmamap callbacks for edge cases.

- Split the TX and RX channels into multiple devices. Then we should be
  able to add support for input- and output-only boards with multiple
  channels.

- Let userland software configure the programmable input/output channel on
  the DTA-145. Right now it is hardcoded as input.

- Add a few sysctl values to set the default parameters. This could be used
  to make streams accessible to shell scripts / pipes and to use netcat or
  ssh as a transport.

- Add support for 208-byte packets.

- Do something useful with the led, possibly from userland.

<!-- Local Variables: -->
<!-- fill-column: 75 -->
<!-- End: -->
