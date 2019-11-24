/* Replace "dll.h" with the name of your header */
#include "dll.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "funkcje.h"
using namespace std;




BOOL APIENTRY DllMain(HINSTANCE hInst     /* Library instance handle. */,
	DWORD reason        /* Reason this function is being called. */,
	LPVOID reserved     /* Not used. */)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		cout << "I try to attach project" << endl;
		Hello();
		break;

	case DLL_PROCESS_DETACH:
		cout << "I try to detach project" << endl;
		Hello();
		break;

	case DLL_THREAD_ATTACH:
		cout << "I try to attach thread" << endl;
		Hello();
		break;

	case DLL_THREAD_DETACH:
		cout << "I try to detach thread" << endl;
		Hello();
		break;
	}

	/* Returns TRUE <strong class="highlight">on</strong> success, FALSE <strong class="highlight">on</strong> failure */
	return TRUE;
}