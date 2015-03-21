//#include "systeminfo.h"

//SystemInfo::SystemInfo(QObject *parent) :
//    QObject(parent)
//{
//    getSysInfo();
//}

//void SystemInfo::getSysInfo()
//{
//    // get the computer name
//    TCHAR nameBuf[MAX_COMPUTERNAME_LENGTH + 2];
//    DWORD nameBufSize;

//    nameBufSize = sizeof nameBuf - 1;
//    if (GetComputerName(nameBuf, &nameBufSize) == TRUE) {
//        //_tprintf(_T("Your computer name is %s\n"), nameBuf);
//        ComputerName=QString::fromStdWString(nameBuf);

//    }

//    // get the operating system name
//    OSVERSIONINFO osvi;
//    //    BOOL bIsWindowsXPorLater;

//    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
//    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

//    GetVersionEx(&osvi);

//    if(osvi.dwMajorVersion==6&&osvi.dwMinorVersion==2){
//        cout << " OS: Windows 8" << endl;
//        OSName =tr("Windows 8");
//    }
//    else if(osvi.dwMajorVersion==6&&osvi.dwMinorVersion==1){
//        cout << "OS: Windows 7" << endl;
//        OSName =tr("Windows 7");
//    }
//    else if(osvi.dwMajorVersion==6&&osvi.dwMinorVersion==0){
//        cout << "OS: Windows Vista" << endl;
//        OSName =tr("Windows Vista ");
//    }
//    else if(osvi.dwMajorVersion==5&&osvi.dwMinorVersion==1){
//        cout << "OS: Windows XP" << endl;
//        OSName =tr("Windows XP ");
//    }
//    else {
//        cout << "OS: UNKNOWN " << endl;
//        //        cout << osvi.szCSDVersion << endl;
//        OSName =tr("Windows XP ");
//    }
//    /* ******************************************* */

//    // get the cpu type and the dedicated memory
//    int CPUInfo[4] = {-1};
//    unsigned   nExIds, i =  0;
//    char CPUBrandString[0x40];
//    // Get the information associated with each extended ID.
//    __cpuid(CPUInfo, 0x80000000);
//    nExIds = CPUInfo[0];
//    for (i=0x80000000; i<=nExIds; ++i)
//    {
//        __cpuid(CPUInfo, i);
//        // Interpret CPU brand string
//        if  (i == 0x80000002)
//            memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
//        else if  (i == 0x80000003)
//            memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
//        else if  (i == 0x80000004)
//            memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
//    }
//    //string includes manufacturer, model and clockspeed
//    cout << "CPU Type: " << CPUBrandString << endl;
//    CPUName = QString::fromStdString(CPUBrandString);

//    SYSTEM_INFO sysInfo;
//    GetSystemInfo(&sysInfo);
//    cout << "Number of Cores: " << sysInfo.dwNumberOfProcessors << endl;

//    MEMORYSTATUSEX statex;
//    statex.dwLength = sizeof (statex);
//    GlobalMemoryStatusEx(&statex);
//    cout << "Total System Memory: " << (statex.ullTotalPhys/1024)/1024 << "MB" << endl;

//    //MemorySize = tr(QString::number((statex.ullTotalPhys/1024)/1024)+" MB" );

//}

//QString SystemInfo::getComputerName()
//{
//    return ComputerName;
//}

//QString SystemInfo::getOSName()
//{
//    return OSName;
//}

//QString SystemInfo::getCPU()
//{
//    return CPUName;
//}

//QString SystemInfo::getMemory()
//{
//    return MemorySize;
//}
