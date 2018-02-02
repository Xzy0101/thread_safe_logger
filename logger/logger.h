#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif

#include <fstream>
#include <string>
#include <mutex>

class LOGGER_API Logger {
public:
	explicit Logger(std::string filename);
	void write(std::string message);
	~Logger();
private:
	std::ofstream log;
	std::mutex mtx;
	const std::string currentDateTime();
};

#endif