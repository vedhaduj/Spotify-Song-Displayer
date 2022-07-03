#include <iostream>
#include <Windows.h>

if (spotifyplayeron)
		{
			DWORD addy;
			DWORD spotpid;
			MODULEENTRY32 mod;
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
