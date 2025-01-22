#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__

#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <iostream>
// Define log levels
#define NO_LOG 0x00
#define ERROR_LEVEL 0x01
#define WARN_LEVEL 0x02
#define INFO_LEVEL 0x03
#define DEBUG_LEVEL 0x04

// Default log level
#ifndef LOG_LEVEL
#define LOG_LEVEL DEBUG_LEVEL
#endif

// Function to get current time as a string
static inline char* get_time() {
    static char buffer[64];
    time_t t_now = time(nullptr);
    struct tm* timeinfo = localtime(&t_now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return buffer;
}

static inline void print_log(const char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
}

// Define the log format
#define LOG_FMT "%s | %-7s | %-7s | %-5d | %-7s | %s\n"

// Macro to print logs
#define LOG_PRINT(fmt, ...) print_log(fmt, __VA_ARGS__)

#if LOG_LEVEL >= DEBUG_LEVEL
#define LOG_DEBUG(message, ...) LOG_PRINT(LOG_FMT, get_time(), __FILE__, __FUNCTION__, __LINE__, "DEBUG", message, ##__VA_ARGS__)
#else
#define LOG_DEBUG(message, ...)
#endif

#if LOG_LEVEL >= INFO_LEVEL
#define LOG_INFO(message, ...) LOG_PRINT(LOG_FMT, get_time(), __FILE__, __FUNCTION__, __LINE__, "INFO", message, ##__VA_ARGS__)
#else
#define LOG_INFO(message, ...)
#endif

#if LOG_LEVEL >= WARN_LEVEL
#define LOG_WARN(message, ...) LOG_PRINT(LOG_FMT, get_time(), __FILE__, __FUNCTION__, __LINE__, "WARN", message, ##__VA_ARGS__)
#else
#define LOG_WARN(message, ...)
#endif

#if LOG_LEVEL >= ERROR_LEVEL
#define LOG_ERROR(message, ...) LOG_PRINT(LOG_FMT, get_time(), __FILE__, __FUNCTION__, __LINE__, "ERROR", message, ##__VA_ARGS__)
#else
#define LOG_ERROR(message, ...)
#endif

#endif
