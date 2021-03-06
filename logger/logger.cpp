// logger.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "logger.h"

Logger::Logger(std::string filename)
	:log{ filename, std::ios::app }, mtx{}
{}

void Logger::write(std::string message) 
{
	mtx.lock();
	log << currentDateTime() << " " << message << std::endl;
	mtx.unlock();
}

Logger::~Logger()
{
	log.close();
}

const std::string Logger::currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	localtime_s(&tstruct, &now);
	strftime(buf, sizeof(buf), "%Y-%m-%d %X", &tstruct);

	return buf;
}
