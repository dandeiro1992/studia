#include"dll.h"
int main()
{
	STARTUPINFO si = {};
	PROCESS_INFORMATION pi = {};
	//CreateProcess(NULL, "c:\\Program Files\\Microsoft SDKs\\Windows\\v7.1A\\Bin\\certmgr.exe", NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &si, &pi);
	Process p;
	char path[] = "C://programy/do inzynierki/implementacja_dll/biblioteka.dll"; // pelna sciezka modulu
	HANDLE h = CreateEvent(0, TRUE, FALSE, "mp");
	int processID = -1;
	for (int i = 0; i < 100; i++)
		printf("%c", path[i]);
	while (true)
	{
		//processID = p.GetProcessID("CertMgr.Exe");
		processID = p.GetProcessID("calc.exe");
		if (processID != -1)
			std::cout << "\n" << (p.InjectDll(path, processID) == true ? "udalo sie" : "nie udalo sie");
			WaitForSingleObject(h, 3000);
	}
	return 0;
}