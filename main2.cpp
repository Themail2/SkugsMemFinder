#include <iostream>
#include <Windows.h>

using namespace std;

int main()
{
	int readP2Win = 0;
	int readP1Win = 0;
	HWND hwnd = FindWindowA(NULL, "Skullgirls Encore");
	if (hwnd == NULL)
	{
		cout << "Cannot Find Skullgirls." << endl;
		Sleep(3000);
		exit(-1);
	}
	else
	{
		DWORD procID;
		GetWindowThreadProcessId(hwnd, &procID);
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID);

		if (procID == NULL)
		{
			cout << "Cannot Find Skullgirls Proccess ID" << endl;
			Sleep(3000);
			exit(-1);
		}
		else
		{
			cout << "Press Num Pad 0 to Exit..." << endl;
			while (true) {
				Sleep(50);
				ReadProcessMemory(handle, (PBYTE*)0x0C8C30A4, &readP1Win, sizeof(int), 0);
				ReadProcessMemory(handle, (PBYTE*)0x0C8C30AC, &readP2Win, sizeof(int), 0);
				if (readP1Win)
				{
					cout << "Player 1 Wins!" << endl;
					Sleep(3000);
				}
				if (readP2Win)
				{
					cout << "Player 2 Wins!" << endl;
					Sleep(3000);
				}
				if (!(readP2Win) && !(readP1Win))
				{
					cout << "Game In Progress..." << endl;
					Sleep(3000);
				}
				if (GetAsyncKeyState(VK_NUMPAD0)) { // Exit
					return 0;
				}
			}
		}
	}
}