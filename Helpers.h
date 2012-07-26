/* -*- c-file-style: "bsd"; indent-tabs-mode: t; -*- */

//#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#*#* Helpers.h *#*#*#*#*#*#*#*#*# (C) 2000-2003 DEKTEC

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- License -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//
// This program is free software; You can freely use/modify this source code in any way
// you desire, including for commercial applications.
//

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Change History -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.
//      olgeni  11-02-2004      Hijacked to FreeBSD :)
//      MG      21-10-2002      Created

#ifndef __HELPERS_H
#define __HELPERS_H

//.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Include files -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-

//.-.-.-.-.-.-.-.-.-.-.-.-.-.- Type definitions and constants -.-.-.-.-.-.-.-.-.-.-.-.-.-.

// PCI write/read helpers

#define WRITE_BYTE(val, tag, handle, offset) bus_space_write_1 (tag, handle, offset, val)
#define WRITE_WORD(val, tag, handle, offset) bus_space_write_2 (tag, handle, offset, val)
#define WRITE_LONG(val, tag, handle, offset) bus_space_write_4 (tag, handle, offset, val)

#define READ_BYTE(tag, handle, offset) bus_space_read_1 (tag, handle, offset)
#define READ_WORD(tag, handle, offset) bus_space_read_2 (tag, handle, offset)
#define READ_LONG(tag, handle, offset) bus_space_read_4 (tag, handle, offset)

//-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.- Data declaration -.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-

#endif // __HELPERS_H
