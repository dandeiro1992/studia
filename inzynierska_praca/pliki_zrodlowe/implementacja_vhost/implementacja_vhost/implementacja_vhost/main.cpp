#include "Injection.h"
#include <stdio.h>
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmd, int show)
{
	char path[] = "C://programy/do inzynierki/implementacja_dll/biblioteka.dll";
	DLLInjection *dllInjection = new DLLInjection();
	dllInjection->InjectDLLTosvchost((LPSTR)path);

	return 0;
}