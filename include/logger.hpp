#ifndef __LOGGER_HPP__
#define __LOGGER_HPP__
#include <time.h>
#include <string.h>

// define log level
#define NO_LOG 0x00
#define ERROR_LEVEL 0x01
#define WARN_LEVEL 0x02
#define INFO_LEVEL 0x03
#define DEBUG_LEVEL 0x04

// set log_level defaul
#ifndef LOG_LEVEL
#define LOG_LEVEL INFO_LEVEL
#endif

static inline char* get_time(){
    static char buffer[64];
    time_t t_now = time(nullptr);
    struct tm* timeinfo = localtime(&t_now);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", timeinfo);
    return buffer;
}

#define LOG_FMT  "%s | %-7s | %-7s | %-5d | %-7s | %-15s |\n"
#define LOG_PRINT(fmt, ... ) fprintf(stderr, fmt, __VA_ARGS__) 

#if LOG_LEVEL >= DEBUG_LEVEL 
#define LOG_DEBUG(message) LOG_PRINT(LOG_FMT, get_time(), __FILE__, __FUNCTION__, __LINE__, "DEBUG", message )
#else
#define LOG_DEBUG(message)
#endif

#if LOG_LEVEL >= INFO_LEVEL
#define LOG_INFO(message) LOG_PRINT(LOG_FMT, get_time(), __FILE__, __FUNCTION__, __LINE__, "INFO",  message)
#else
#define LOG_INFO(message)
#endif

#if LOG_LEVEL >= WARN_LEVEL
#define LOG_WARN(message) LOG_PRINT(LOG_FMT, get_time(), __FILE__, __FUNCTION__, __LINE__, "WARN", message)
#else
#define LOG_WARN(message)
#endif

#if LOG_LEVEL >= ERROR_LEVEL
#define LOG_ERROR(message) LOG_PRINT(LOG_FMT, get_time(), __FILE__, __FUNCTION__, __LINE__, "ERROR", message)
#else
#define LOG_ERROR(message)
#endif


#endif