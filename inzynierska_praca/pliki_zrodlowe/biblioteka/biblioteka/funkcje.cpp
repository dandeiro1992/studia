#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "funkcje.h"
#include <iostream>
#include <shellapi.h>
#include <windows.h>
#include <tchar.h>
using namespace std;
void Hello()
{
	//string filename = "\"C:/Program Files/Microsoft SDKs/Windows/v7.1A/Bin/certmgr.exe\" -add -all -c \"C:/Users/Damian/Desktop/wwwtesthttpdev.crt\" -s -r localMachine root";
	//string programname="C:\\Windows\\System32\\notepad.exe";
	//system("\"\"C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1A\\Bin\\certmgr.exe\" -add -all -c \"C:\\Users\\Damian\\Desktop\\wwwtesthttpdev.crt\" -s -r localMachine root\"");
	//system("\"C:/Program Files/Microsoft SDKs/Windows/v7.1A/Bin/certmgr.exe\" -add -all -c \"C:/Users/Damian/Desktop/wwwtesthttpdev.crt\" -s -r localMachine root");
	//MessageBox(NULL, (LPCWSTR)L"przykladowy messagebox zostal wywolany", (LPCWSTR)L"Tytul messagebox", MB_ICONINFORMATION);
	//ShellExecute(NULL, (LPCWSTR)"runas", (LPCWSTR)("C:\\Windows\\System32\cmd.exe"), (LPCWSTR)("\"\"C:\\Program Files\\Microsoft SDKs\\Windows\\v7.1A\\Bin\\certmgr.exe\" -add -all -c \"C:\\Users\\Damian\\Desktop\\wwwtesthttpdev.crt\" -s -r localMachine root\""), NULL, SW_SHOWNORMAL);
	//"c:\Program Files\Microsoft SDKs\Windows\v7.1A\Bin\certmgr.exe\" - add - all - c \"c:\Users\Damian\Desktop\wwwtesthttpdev.crt\" - s - r localMachine root"
	//ShellExecute(NULL, _T("open"), _T("C:\\Windows\\System32\\cmd.exe"), _T("c:\Program Files\Microsoft SDKs\Windows\v7.1A\Bin\certmgr.exe\" - add - all - c \"c:\Users\Damian\Desktop\wwwtesthttpdev.crt\" - s - r localMachine root"), NULL, SW_SHOWNORMAL);//(LPCWSTR)filename.c_str()
	MessageBox(NULL, (LPCWSTR)L"poczatkowy messagebox DLL-cryptbase", (LPCWSTR)L"Tytul messagebox - DLL-cryptbase", MB_ICONINFORMATION);
	STARTUPINFO startInfo = { 0 };

	PROCESS_INFORMATION processInfo = { 0 };

	BOOL bSucces = CreateProcess((LPWSTR)(L"c:\\Users\\Damian\\Desktop\\wusa\\implementacja_vhost.exe"), NULL, NULL, NULL, 0, 0, NULL, NULL, &startInfo, &processInfo);
	
	if (bSucces)
	{
		cout << "Process Started" << endl
			<< "Process ID:  " << processInfo.dwProcessId << endl;
	}
	else
	{
		cout << "Error to start a process    " << GetLastError() << endl;
	}
	MessageBox(NULL, (LPCWSTR)L"koncowy messagebox - DLL-cryptbase", (LPCWSTR)L"Tytul messagebox - DLL-cryptbase", MB_ICONINFORMATION);
	cin.get();

}