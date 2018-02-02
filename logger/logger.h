#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#ifdef LOGGER_EXPORTS
#define LOGGER_API __declspec(dllexport)
#else
#define LOGGER_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <process.h>
#include <Windows.h>

	typedef struct LOGGER_API {
		FILE* file;
		HANDLE mtx;
	} Logger;

	LOGGER_API Logger* logger_init(const char* filename);
	LOGGER_API int logger_lock(Logger* logger);
	LOGGER_API int logger_unlock(Logger* logger);
	LOGGER_API void logger_cleanup(Logger* logger);

	
#ifdef __cplusplus
}
#endif

#endif