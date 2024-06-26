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


#include <winsock2.h>
#include <windows.h>
#include <tchar.h>
#include <crtdbg.h>

#include "IPC.h"

const static LPCTSTR g_szIPCSharedMMF = _T("{34F673E0-878F-11D5-B98A-00B0D07B8C7C}");
const static LPCTSTR g_szIPCSharedMMFBitmap = _T("{34F673E0-878F-11D5-B98A-57B0D07B8C7C}");
int oldcounter=0;
//***********************************************
CIPC::CIPC() 
{
	m_hFileMap=NULL;
	m_hFileMapBitmap=NULL;
	pBitmap=NULL;
	plist=NULL;
	m_FileView=0;
	m_FileViewBitmap=0;
	CreateIPCMMF();
	OpenIPCMMF();
}

//***********************************************
CIPC::~CIPC()
{
	CloseIPCMMF();
	CloseIPCMMFBitmap();
}
//***********************************************
bool CIPC::CreateIPCMMF(void)
{
	bool bCreated = false;
	int listsize=sizeof(mystruct);
	try
	{
		if(m_hFileMap != NULL)
			return false;	// Already created
		
		// Create an in-memory 4KB memory mapped file to share data
		m_hFileMap = CreateFileMapping(INVALID_HANDLE_VALUE,
			NULL,
			PAGE_READWRITE,
			0,
			listsize,
			g_szIPCSharedMMF);
		if(m_hFileMap != NULL)
			bCreated = true;
	}
	catch(...) {}

	return bCreated;
}
//***********************************************
bool CIPC::CreateIPCMMFBitmap(int size)
{
	bool bCreatedBitmap = false;

	try
	{
		if(m_hFileMapBitmap != NULL)
			return false;	// Already created

		// Create an in-memory 4KB memory mapped file to share data
		m_hFileMapBitmap = CreateFileMapping(INVALID_HANDLE_VALUE,
			NULL,
			PAGE_READWRITE,
			0,
			size,
			g_szIPCSharedMMFBitmap);
		if(m_hFileMapBitmap != NULL)
			bCreatedBitmap = true;
	}
	catch(...) {}

	return bCreatedBitmap;
}

//***********************************************
bool CIPC::OpenIPCMMF(void)
{
	bool bOpened = false;

	try
	{
		if(m_hFileMap == NULL)
		{

		m_hFileMap = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
			FALSE,
			g_szIPCSharedMMF);
		}

		if(m_hFileMap != NULL)
		{
			bOpened = true;
			m_FileView = MapViewOfFile(m_hFileMap,
			FILE_MAP_READ | FILE_MAP_WRITE,
			0, 0, 0);
			if (m_FileView==0) bOpened = false;
			plist=(mystruct*) m_FileView;

		}
	}
	catch(...) {}

	return bOpened;
}
//***********************************************
bool CIPC::OpenIPCMMFBitmap(void)
{
	bool bOpenedBitmap = false;

	try
	{
		if(m_hFileMapBitmap == NULL)
		{

		m_hFileMapBitmap = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE,
			FALSE,
			g_szIPCSharedMMFBitmap);
		}

		if(m_hFileMapBitmap != NULL)
		{
			bOpenedBitmap = true;
			m_FileViewBitmap = MapViewOfFile(m_hFileMapBitmap,
			FILE_MAP_READ | FILE_MAP_WRITE,
			0, 0, 0);
			if (m_FileViewBitmap==0) bOpenedBitmap = false;
			pBitmap=(byte*) m_FileViewBitmap;

		}
	}
	catch(...) {}

	return bOpenedBitmap;
}
//***********************************************
void CIPC::CloseIPCMMF(void)
{
	try
	{
		if (m_FileView) UnmapViewOfFile(m_FileView);
		if(m_hFileMap != NULL)
			CloseHandle(m_hFileMap), m_hFileMap = NULL;
	}
	catch(...) {}
}
//***********************************************
void CIPC::CloseIPCMMFBitmap(void)
{
	try
	{
		if (m_FileViewBitmap) UnmapViewOfFile((LPVOID)m_FileViewBitmap);
			m_FileViewBitmap=NULL;
		if(m_hFileMapBitmap != NULL)
			CloseHandle(m_hFileMapBitmap);
		m_hFileMapBitmap = NULL;
	}
	catch(...) {}
}
mystruct* CIPC::listall()
{
	return plist;
}
//***********************************************