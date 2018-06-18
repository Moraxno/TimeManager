#include "TimeManager.h"
#include <QtWidgets/QApplication>

#include <ctime>
#include <Windows.h>

#include <TlHelp32.h>
#include <vector>

#include <UIAutomation.h>
#include <atlbase.h>

#include <iostream>
#include <string>

#include <regex>

/**
 *	Namespace containing everything regarding the TimeManager.
 *
**/
namespace TMgr
{
	/**
	 *	Work-In-Progress Solution for a List of Processes that need to be terminated if they are unsuitable.
	 *	Should be replaced by some form of config.
	**/
	std::vector<std::wstring> badProcesses =
	{
		L"notepad.exe",
	};

	std::vector<std::wstring> badURLs =
	{
		L"bing.com",
	};

	std::wstring getTabName()
	{
		CComQIPtr<IUIAutomation> uia;
		if (FAILED(uia.CoCreateInstance(CLSID_CUIAutomation)) || !uia)
		{
			return L"ERROR";
		}

		CComPtr<IUIAutomationCondition> cond;
		uia->CreatePropertyCondition(UIA_ControlTypePropertyId, CComVariant(0xC354), &cond);

		HWND hwnd = NULL;
		while (true)
		{
			hwnd = FindWindowEx(NULL, hwnd, L"Chrome_WidgetWin_1", NULL);
			if (!hwnd)
			{
				return L"[ERROR] Can't find Window";
			}

			if (!IsWindowVisible(hwnd))
			{
				continue;
			}

			CComPtr<IUIAutomationElement> root;
			if (FAILED(uia->ElementFromHandle(hwnd, &root)) || !root)
			{
				return L"[ERROR] Can't find RootElement";
			}

			CComPtr<IUIAutomationElement> urlBox;
			if (FAILED(root->FindFirst(TreeScope_Descendants, cond, &urlBox)) || !urlBox)
			{
				continue;
			}

			CComVariant url;
			urlBox->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &url);
			
			return url.bstrVal;
		}
	}

	void killProcessesByName(const wchar_t* processName)
	{
		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, 0);

		PROCESSENTRY32 entry;
		entry.dwSize = sizeof(entry);

		bool hasEntry = Process32First(snapshot, &entry);

		while (hasEntry)
		{
			if (wcscmp(processName, entry.szExeFile) == 0)
			{
				std::wcout << "Die! " << processName << std::endl;
				HANDLE process = OpenProcess(PROCESS_TERMINATE, 0, entry.th32ProcessID);
				if (process != NULL)
				{
					TerminateProcess(process, 0);
					CloseHandle(process);
				}
			}

			hasEntry = Process32Next(snapshot, &entry);

		}

		CloseHandle(snapshot);
	}

	void killProcesses()
	{
		for (size_t i = 0; i < badProcesses.size(); i++)
		{
			killProcessesByName(badProcesses[i].data());
		}
	}

	void killTabs()
	{
		std::wstring tabName = getTabName();
		for (int i = 0; i < badURLs.size(); i++)
		{
			std::wregex regex(badURLs[i]);
			if (std::regex_search(tabName, regex))
			{
				killProcessesByName(L"chrome.exe");
				std::wcout << L"Böse Seite! Geh weg!!!!" << std::endl;
				std::wcout << L"Page:  " << tabName << std::endl;
				std::wcout << L"Match: " << badURLs[i] << std::endl;
				std::wcout << std::endl;
			}
		}
	}

	[[noreturn]]
	void start()
	{

		CoInitialize(NULL);

		while (true)
		{
			time_t rawTime;
			time(&rawTime);

			tm timeInfo;
			localtime_s(&timeInfo, &rawTime);

			int weekday = timeInfo.tm_wday;
			int hour = timeInfo.tm_hour;

			if (weekday >= 1 && weekday <= 5 && hour >= 7 && hour <= 23)
			{

			}
			killProcesses();
			killTabs();
			std::wcout << getTabName() << std::endl;

			Sleep(250);
		}

	}
}

int main(int argc, char *argv[])
{
	// detach from the current console window
	// if launched from a console window, that will still run waiting for the new console (below) to close
	// it is useful to detach from Qt Creator's <Application output> panel
	FreeConsole();

	// create a separate new console window
	AllocConsole();

	// attach the new console to this application's process
	AttachConsole(GetCurrentProcessId());

	// reopen the std I/O streams to redirect I/O to the new console
	freopen("CON", "w", stdout);
	freopen("CON", "w", stderr);
	freopen("CON", "r", stdin);

	QApplication a(argc, argv);
	TimeManager w;

	w.show();

	TMgr::start();

	return a.exec();
}
