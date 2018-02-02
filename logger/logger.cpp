// logger.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "logger.h"

#include <process.h>

Logger* logger_init(const char* filename) {
	Logger* l = new Logger;
	int res = fopen_s(&(l->file), filename, "a");
	if (res) {
		printf("fopen error: %d\n", res);
		delete l;
		return NULL;
	}
	l->mtx = CreateMutex(
		NULL,              // default security attributes
		FALSE,             // initially not owned
		NULL);             // unnamed mutex
	if (l->file == NULL) {
		printf("CreateMutex error: %d\n", GetLastError());
		fclose(l->file);
		delete l;
		return NULL;
	}
	return l;
}

int logger_lock(Logger* logger) {
	DWORD res;
	res = WaitForSingleObject(logger->mtx, INFINITE);
	switch (res) {
	case WAIT_OBJECT_0:
		return TRUE;
	case WAIT_ABANDONED:
		return FALSE;
	}
	return FALSE;
}

int logger_unlock(Logger* logger) {
	return ReleaseMutex(logger->mtx);
}

void logger_cleanup(Logger* logger) {
	CloseHandle(logger->mtx);
	fclose(logger->file);
	delete logger;
}