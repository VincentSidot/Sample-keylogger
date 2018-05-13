#include "logger.h"




logger::logger(std::wstring file_path, bool print_to_console)
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	m_logFileName = file_path;
	m_logFile.open(m_logFileName, std::ios::out | std::ios::app);
	m_print_to_console = print_to_console;
}

logger::~logger()
{
	m_logFile.close();
}

std::wstring logger::logfile_name() const
{
	return this->m_logFileName;
}

logger & logger::operator<<(std::wstring str)
{
	/*
	SYSTEMTIME st;
	GetSystemTime(&st);
	std::string nstr;
	*/

	// [ 22/09/99 | 14:23:32 ] -> str
	
	/*
	if (st.wMinute - current_minute > 2)
	{
		nstr = "[ " + std::to_string(st.wDay) + "/" + std::to_string(st.wMonth) + "/" + std::to_string(st.wYear) + " | " + std::to_string(st.wHour) + ":" + std::to_string(st.wMinute) + ":" + std::to_string(st.wSecond) + " ] -> " + str + "\n";
		current_minute = st.wMinute;
	}
	else
	{
		nstr = str;
	}
	*/

	this->m_logFile << str;
	if (this->m_print_to_console)
		std::wcout << str;
	return *this;
}

logger & logger::operator<<(const wchar_t* str)
{
	return this->operator<<(std::wstring(str));
}

logger & logger::operator<<(const wchar_t key)
{
	this->m_logFile << key;
	if (this->m_print_to_console)
		std::wcout << key;
	return *this;
}