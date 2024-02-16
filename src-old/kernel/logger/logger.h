#ifndef __LOGGER_H
#define __LOGGER_H

#include <stdarg.h>

enum LogType {
    LT_INFO,
    LT_WARNING,
    LT_ERROR,
    LT_LENGTH
};

extern void (*logger_write)(enum LogType, int, char *, int);

void __internal_log(char *file, char *line, enum LogType type, char *message, ...);
void log_nofileinfo(enum LogType type, char *message, ...);

void logger_setenabled(int enabled);
int logger_isenabled();

#define STRINGIZE(x) STRINGIZE2(x)
#define STRINGIZE2(x) #x
#define log(type, cmp, message, ...) { __internal_log(cmp, STRINGIZE(__LINE__), type, message, ##__VA_ARGS__); }

#endif