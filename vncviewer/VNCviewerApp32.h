/////////////////////////////////////////////////////////////////////////////
//  Copyright (C) 2002-2024 UltraVNC Team Members. All Rights Reserved.
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
 

#include "VNCviewerApp.h"
#include "Daemon.h"

class VNCviewerApp32 : public VNCviewerApp {
public:
	VNCviewerApp32(HINSTANCE hInstance, PSTR szCmdLine);

	void NewConnection(bool Is_Listening);
	void NewConnection(bool Is_Listening,TCHAR *host, int port);
	void NewConnection(bool Is_Listening,SOCKET sock);
	void NewConnection(bool Is_Listening,TCHAR *configFile);

	~VNCviewerApp32();
private:
	// Set up registry for program's sounds
	//void RegisterSounds();
	Daemon  *m_pdaemon;
};

