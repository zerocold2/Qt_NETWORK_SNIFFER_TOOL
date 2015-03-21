#if !defined(AFX_HARDDISKMANAGER_H__27F8E542_FA4A_43FF_B29D_59BCD13E31C3__INCLUDED_)
#define AFX_HARDDISKMANAGER_H__27F8E542_FA4A_43FF_B29D_59BCD13E31C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>
#include <iostream>
#include <string>


using namespace std;

class CHardDiskManager  
{
public:
	CHardDiskManager();
	virtual ~CHardDiskManager();
    bool CheckFreeSpace(LPCTSTR lpDirectoryName);
    //bool CheckFreeSpace(char* lpDirectoryName);
    LPCTSTR  x;
	
	DWORD64 GetTotalNumberOfBytes(void);
	DWORD64 GetTotalNumberOfFreeBytes(void);

	double GetTotalNumberOfGBytes(void);
    double GetTotalNumberOfFreeGBytes(void);
	void userInteraction();

	 double GetTotalNumberOfMBytes(void);
	 double GetTotalNumberOfFreeMBytes(void);
	 


//private:
	   ULARGE_INTEGER m_uliFreeBytesAvailable;     // bytes disponiveis no disco associado a thread de chamada
	   ULARGE_INTEGER m_uliTotalNumberOfBytes;     // bytes no disco
	   ULARGE_INTEGER m_uliTotalNumberOfFreeBytes; // bytes livres no disco
};

#endif // !defined(AFX_HARDDISKMANAGER_H__27F8E542_FA4A_43FF_B29D_59BCD13E31C3__INCLUDED_)
