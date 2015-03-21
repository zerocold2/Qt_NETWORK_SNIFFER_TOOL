#include "util/MEMORY_HANDEL.h"
#include <Windows.h>
#include <windef.h>
using namespace std;
typedef long long ll;
// Use to convert bytes to MB
#define DIV 1048576

// Use to convert bytes to MB
//#define DIV 1024

// Specify the width of the field in which to print the numbers.
// The asterisk in the format specifier "%*I64d" takes an integer
// argument and uses it to pad and right justify the number.
#define WIDTH 7

#define WINVER 0x0500
#include <windows.h>


MEMORYSTATUSEX statex;

long mem::getfree(){
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);
    ll size=statex.ullAvailPhys/DIV;
    return size;
}

long mem::total(){
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);
    ll size=statex.ullTotalPhys/DIV;
    return size;
}
long mem::getused(){
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);
    ll size=(statex.ullTotalPhys/DIV)-mem::getfree();
    return size;
}
long mem::getbuffer(){
    statex.dwLength = sizeof (statex);
    GlobalMemoryStatusEx (&statex);
    ll size=statex.ullAvailVirtual/DIV;
    return size;
}
