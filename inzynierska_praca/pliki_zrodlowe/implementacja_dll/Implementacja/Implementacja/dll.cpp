#include"dll.h"
#include <iostream>

using namespace std;

int Process::GetProcessID(char * fileName)
{
	static int pid = -1;
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		std::cout << "\nBlad funkcji CreateToolhelp32Snapshot";
		return -1;
	}
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);
	if (!Process32First(hProcessSnap, &pe32))
	{
		std::cout << "\nBlad funkcji Process32First";
		CloseHandle(hProcessSnap);
		return -1;
	}
	else
	{
		std::cout << "\nProcess ID " << pe32.th32ProcessID;
		std::cout << "\nProcess executable file " << pe32.szExeFile;
		if ((strcmp(pe32.szExeFile, fileName) == 0) && pid != pe32.th32ProcessID)
		{
			pid = pe32.th32ProcessID;
			return pe32.th32ProcessID;
		}
	}
	while (Process32Next(hProcessSnap, &pe32))
	{
		std::cout << "\nProcess ID " << pe32.th32ProcessID;
		std::cout << "\nProcess executable file " << pe32.szExeFile;
		if((strcmp(pe32.szExeFile, fileName) == 0) && pid != pe32.th32ProcessID)
		{
			pid = pe32.th32ProcessID;
			return pe32.th32ProcessID;
		}
	}
	return -1;
	CloseHandle(hProcessSnap);
}
bool Process::InjectDll(char * dllName, unsigned int processID)
{
	cout << "process id:   " << processID << endl;
	HANDLE pHandle = OpenProcess(PROCESS_ALL_ACCESS, false, processID);
	if (pHandle == NULL)//INVALID_HANDLE_VALUE)
	{
		
		cout << "problem z uchwytem" << endl;
		return false;
	}
		
	void * address = VirtualAllocEx(pHandle, NULL, strlen(dllName), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (address == NULL)
	{
		cout << "error:    " << GetLastError() << endl;
	}
	if (!WriteProcessMemory(pHandle, address, (LPVOID)dllName, strlen(dllName), NULL))
	{
		cout << "problem z WriteProcessmemowy" << endl;
		return false;
	}
	HMODULE hK32 = GetModuleHandle("Kernel32");
	HANDLE tHandle = CreateRemoteThread(pHandle, NULL, 0,
		(LPTHREAD_START_ROUTINE)GetProcAddress(hK32, "LoadLibraryA"),
		address, 0, NULL);
	WaitForSingleObject(tHandle, INFINITE);
	DWORD dllAddress;
	GetExitCodeThread(tHandle, &dllAddress);
	CloseHandle(tHandle);
	VirtualFreeEx(pHandle, address, 0, MEM_RELEASE);
	tHandle = CreateRemoteThread(pHandle, NULL, 0,
		(LPTHREAD_START_ROUTINE)GetProcAddress(hK32, "FreeLibrary"), (void*
		)&dllAddress, 0, NULL);
	WaitForSingleObject(tHandle, INFINITE);
	CloseHandle(tHandle);
	return true;
}