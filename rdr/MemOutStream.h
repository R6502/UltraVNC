/////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2002-2024 UltraVNC Team Members. All Rights Reserved.
//  Copyright (C) 2002 RealVNC Ltd. All Rights Reserved.
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
//  USA.
//
//  If the source code for the program is not available from the place from
//  which you received this file, check
//  https://uvnc.com/
//
////////////////////////////////////////////////////////////////////////////


//
// A MemOutStream grows as needed when data is written to it.
//

#ifndef __RDR_MEMOUTSTREAM_H__
#define __RDR_MEMOUTSTREAM_H__

#include "OutStream.h"

namespace rdr {

  class MemOutStream : public OutStream {

  public:

    MemOutStream(int len=1024) {
      start = ptr = new U8[len];
      end = start + len;
    }

    virtual ~MemOutStream() {
      delete [] start;
    }

    void writeBytes(const void* data, int length) {
      check(length);
      memcpy(ptr, data, length);
      ptr += length;
    }

    int length() { return (int)(ptr - start); }
    void clear() { ptr = start; };
    void reposition(int pos) { ptr = start + pos; }

    // data() returns a pointer to the buffer.

    const void* data() { return (const void*)start; }

  private:

    // overrun() either doubles the buffer or adds enough space for nItems of
    // size itemSize bytes.

    int overrun(int itemSize, int nItems) {
      int len = (int)(ptr - start + itemSize * nItems);
      if (len < (end - start) * 2)
        len = (int)((end - start) * 2);

      U8* newStart = new U8[len];
      memcpy(newStart, start, ptr - start);
      ptr = newStart + (ptr - start);
      delete [] start;
      start = newStart;
      end = newStart + len;

      return nItems;
    }

    U8* start;
  };

}

#endif
