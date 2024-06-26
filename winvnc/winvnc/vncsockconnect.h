/////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2002-2024 UltraVNC Team Members. All Rights Reserved.
//  Copyright (C) 1999 AT&T Laboratories Cambridge. All Rights Reserved.
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


// vncSockConnect.h

// The vncSockConnect class creates a listening socket and binds
// it to the specified port. It then creates a listen thread which
// goes into a loop, listening on the socket.
// When the vncSockConnect object is destroyed, all resources are
// freed automatically, including the listen thread.

class vncSockConnect;

#if (!defined(_WINVNC_VNCSOCKCONNECT))
#define _WINVNC_VNCSOCKCONNECT

// Includes
#include "stdhdrs.h"
#include "vsocket.h"
#include <omnithread.h>

class vncServer;

// The vncSockConnect class itself
class vncSockConnect
{
public:
	// Constructor/destructor
	vncSockConnect();
	virtual~vncSockConnect();

	// Init
	virtual VBool Init(vncServer *server, UINT port);

	// Implementation
protected:
	// The listening socket
	VSocket m_socket;

	// The port to listen on
	UINT m_port;

	// The in-coming accept thread
	omni_thread *m_thread;
};

#endif // _WINVNC_VNCSOCKCONNECT