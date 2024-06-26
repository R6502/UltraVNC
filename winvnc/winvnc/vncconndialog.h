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


class vncConnDialog;

#if (!defined(_WINVNC_VNCCONNDIALOG))
#define _WINVNC_VNCCONNDIALOG

#pragma once

#include "vncserver.h"

// Outgoing connection dialog. This allows people running UltraVNC Servers on
// Win32 platforms to _push_ their displays out to other people's screens
// rather than having to _pull_ them across.

class vncConnDialog  
{
public:

	// Create an outgoing-connection dialog
	vncConnDialog(vncServer *server);

	// Destructor
	virtual ~vncConnDialog();

	// Once a dialog object is created, either delete it again, or
	// call DoDialog. DoDialog will run the object and delete it when done
	//adzm 2009-06-20 - Return the result
	INT_PTR DoDialog(bool rep = false);

	// Internal stuffs
private:

	// Routine to call when a dialog event occurs
	static BOOL CALLBACK vncConnDlgProc(HWND hwndDlg,
										UINT uMsg, 
										WPARAM wParam,
										LPARAM lParam);

	// Pointer back to the server object
	vncServer *m_server;

	//adzm 2009-06-20
	HICON m_hicon;
	HFONT m_hfont;
	bool m_repeater;
};

#endif
