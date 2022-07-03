#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>

MODULEENTRY32 GetModule(const char* moduleName, unsigned long ProcessID)
{
	MODULEENTRY32 modEntry = { 0 };

	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, ProcessID);

	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 curr = { 0 };

		curr.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &curr))
		{
			do
			{
				if (!strcmp(curr.szModule, moduleName))
				{
					modEntry = curr;
					break;
				}
			} while (Module32Next(hSnapshot, &curr));
		}
		CloseHandle(hSnapshot);
	}
	return modEntry;
}

DWORD GetPID(const char* ProcessName) {
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);


	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!strcmp(processInfo.szExeFile, ProcessName))
	{
		CloseHandle(processesSnapshot);
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!strcmp(processInfo.szExeFile, ProcessName))
		{
			CloseHandle(processesSnapshot);
		}
	}
	return processInfo.th32ProcessID;
}


int main()
{
	
		DWORD addy;
		DWORD spotpid;
		MODULEENTRY32 mod;
	
		//sometimes the song names will be cut-off so I just set it to a max of 50.
		char spotifysong[50] = {};

		spotpid = GetPID("Spotify.exe");
		mod = GetModule("libcef.dll", spotpid);

		HANDLE spothandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, spotpid);

		ReadProcessMemory(spothandle, (LPCVOID)(mod.modBaseAddr + 0x0883D9F4), &addy, sizeof(addy), 0);
		ReadProcessMemory(spothandle, (LPCVOID)(addy + 0x34), &addy, sizeof(addy), 0);
		ReadProcessMemory(spothandle, (LPCVOID)(addy + 0x34), &addy, sizeof(addy), 0);
		ReadProcessMemory(spothandle, (LPCVOID)(addy + 0xA0), &addy, sizeof(addy), 0);
		ReadProcessMemory(spothandle, (LPCVOID)(addy + 0x10), &addy, sizeof(addy), 0);
		ReadProcessMemory(spothandle, (LPCVOID)(addy + 0x18), &addy, sizeof(addy), 0);
		ReadProcessMemory(spothandle, (LPCVOID)(addy + 0x0), &spotifysong, sizeof(spotifysong), 0);
		printf("Spotify : %s", spotifysong);
	
}
