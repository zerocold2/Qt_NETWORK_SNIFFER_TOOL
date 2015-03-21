#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class mem{
	public:
		long total();
		long getfree();
		long getused();
		long getbuffer();
};
