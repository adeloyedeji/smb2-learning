#define _GNU_SOURCE
#include <errno.h>
#include <libgen.h>
#include <stdarg.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/syscall.h>
#include "logger.h" 

#define smbl_syslog_status_out(...)
#define FOREACH_STATUS(STATUS)              \
            STATUS(STATUS_INFO)             \
            STATUS(STATUS_WARNING)          \
            STATUS(STATUS_ERROR)            \
            STATUS(STATUS_DEBUG)            \
            STATUS(STATUS_PERROR)           \
            STATUS(STATUS_NONE)             \
            STATUS(STATUS_CRITICAL)     

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_ENUM_STRING(STRING) #STRING,

pid_t gettid(void) { return (pid_t)syscall(SYS_gettid); }

enum smbl_status_type {
    FOREACH_STATUS(GENERATE_ENUM)
};

static const char* STATUS_STRING[] = {
    FOREACH_STATUS(GENERATE_ENUM_STRING)
};

static long gettid_cached(void)
{
    static __thread long tid;

    if (!tid)
        tid = gettid();

    return tid;
}

static void status_out(
    const char *file,
    const int line,
    const char *func,
    enum smbl_status_type type,
    const char *fmt,
    va_list values)
{
    // int saved_errno = errno;
    // smbl_syslog_status_out(file, line, func, gettid_cached(), type, saved_errno,
    //                        fmt, values);
    char *base_name = basename(strdupa(file));

    printf("[%s:%ld] ", STATUS_STRING[type], gettid_cached());
    printf("%s:%d::%s() ", base_name, line, func);
    vprintf(fmt, values);
    printf("\n");
}

#define IMPLEMENT_FUNCTION(fn_name_, type_)                                     \
    void smbl_log_##fn_name_##_debug(const char *file, const int line,       \
                                        const char *func, const char *fmt,      \
                                        ...)                                    \
    {                                                                           \
        va_list values;                                                         \
        va_start(values, fmt);                                                  \
        status_out(file, line, func, type_, fmt, values);                       \
        va_end(values);                                                         \
    }

IMPLEMENT_FUNCTION(debug, STATUS_DEBUG)
IMPLEMENT_FUNCTION(info, STATUS_INFO)
IMPLEMENT_FUNCTION(warning, STATUS_WARNING)
IMPLEMENT_FUNCTION(error, STATUS_ERROR)
IMPLEMENT_FUNCTION(critical, STATUS_CRITICAL)
IMPLEMENT_FUNCTION(critical_perror, STATUS_CRITICAL | STATUS_PERROR)