#ifndef _dllinjection_h_
#define _dllinjection_h_

#include<windows.h>
#include <tlhelp32.h>
#include<iostream>

class Process
{
public:
	int GetProcessID(char * fileName);
	bool InjectDll(char * dllPath, unsigned int processID);
};
#endif