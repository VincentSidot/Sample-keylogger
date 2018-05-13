#pragma once

#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>

class logger
{
public:
	logger(std::wstring file_path,bool print_to_console = false);
	~logger();

	std::wstring logfile_name() const;

	logger& operator<<(std::wstring str);
	logger& operator<<(const wchar_t* str);
	logger& operator<<(wchar_t key);

private:
	std::wstring m_logFileName;
	std::wfstream m_logFile;
	bool m_print_to_console;
	WORD current_minute;
};
