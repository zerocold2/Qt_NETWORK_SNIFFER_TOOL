// HardDiskManager.cpp: implementation of the CHardDiskManager class.
//
//////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <string>
#include "DESK_INFO/HardDiskManager.h"
#include <WinNT.h>
#include <iostream>

CHardDiskManager::CHardDiskManager()
{

	// bytes available to caller
	m_uliFreeBytesAvailable.QuadPart     = 0L;
	// bytes on disk
	m_uliTotalNumberOfBytes.QuadPart     = 0L;
	// free bytes on disk
	m_uliTotalNumberOfFreeBytes.QuadPart = 0L;
}


CHardDiskManager::~CHardDiskManager()
{
}

bool CHardDiskManager::CheckFreeSpace(LPCTSTR lpDirectoryName)
{
	if( !GetDiskFreeSpaceEx(
        lpDirectoryName,                  // directory name
        &m_uliFreeBytesAvailable,         // bytes available to caller
		&m_uliTotalNumberOfBytes,         // bytes on disk
		&m_uliTotalNumberOfFreeBytes) )   // free bytes on disk
		return false;

	return true;
}

DWORD64 CHardDiskManager::GetTotalNumberOfBytes(void)

{ 
	return m_uliTotalNumberOfBytes.QuadPart;
}

DWORD64 CHardDiskManager::GetTotalNumberOfFreeBytes(void)
{ 
	return m_uliTotalNumberOfFreeBytes.QuadPart;
}

double CHardDiskManager::GetTotalNumberOfGBytes(void)
{
    return (double)( (signed __int64)(m_uliTotalNumberOfBytes.QuadPart)/(1024*1024*1024) );
}

double CHardDiskManager::GetTotalNumberOfFreeGBytes(void)
{ 
	return (double)( (signed __int64)(m_uliTotalNumberOfFreeBytes.QuadPart)/(1024*1024*1024) ); 
}

// functions to get size with MegaBytes


double CHardDiskManager::GetTotalNumberOfMBytes(void)
{ 
	return (double)( (signed __int64)(m_uliTotalNumberOfBytes.QuadPart)/(1024*1024) );     
}

double CHardDiskManager::GetTotalNumberOfFreeMBytes(void)
{ 
	return (double)( (signed __int64)(m_uliTotalNumberOfFreeBytes.QuadPart)/(1024*1024) ); 
}



//User Interaction fucnctions 

void CHardDiskManager::userInteraction()
{

	string m;
	double size=0;
	double maxFileSize=0;

	cout << "Enter the storage type (MB or GB)" << endl;
	cin >> m;

	cout << "Enter the required space " << endl;
	cin >> maxFileSize;


	if(m=="MB")
	{
		if(maxFileSize>CHardDiskManager::GetTotalNumberOfFreeMBytes())
		{
			cout << "No Available space "<< endl;
		}
		else 
			cout << "Allocated " << endl;
	}
	else if(m=="GB")
	{
		if(maxFileSize>CHardDiskManager::GetTotalNumberOfFreeGBytes())
		{
			cout << "No Available space " << endl;
		}
		else 
			cout << "Allocated " << endl;
	}

}
