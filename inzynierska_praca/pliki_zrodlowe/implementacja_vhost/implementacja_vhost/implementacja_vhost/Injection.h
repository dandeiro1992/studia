#ifndef _dllinjection_h_
#define _dllinjection_h_
#include <Windows.h>
class DLLInjection
{
public:
	DLLInjection();
	~DLLInjection();
	void InjectDLLTosvchost(LPSTR dllPath);
};

#endif