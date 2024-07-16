#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <stdio.h>

#define DECLARE_LOGGER_PROTO(type_, ...)                    \
        void smbl_log_##type_##_debug(const char *file,     \
                    const int line_number,                  \
                    const char *function_name,              \
                    const char *fmt,                        \
                    ...)                                    \
                        __attribute__((format(printf, 4, 5)))   \
                        __attribute__((noinline,cold))          \
                        __VA_ARGS__;     

DECLARE_LOGGER_PROTO(debug)
DECLARE_LOGGER_PROTO(info)
DECLARE_LOGGER_PROTO(warning)
DECLARE_LOGGER_PROTO(error)
DECLARE_LOGGER_PROTO(critical)
DECLARE_LOGGER_PROTO(critical_perror)
// DECLARE_LOGGER_PROTO(critical, __attribute__((noreturn)))
// DECLARE_LOGGER_PROTO(critical_perror, __attribute__((noreturn)))

#define smbl_log_debug(fmt, ...)        \
        smbl_log_debug_debug(__FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__) 
#define smbl_log_info(fmt, ...)         \
        smbl_log_info_debug(__FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#define smbl_log_warning(fmt, ...)      \
        smbl_log_warning_debug(__FILE__, __LINE__, __FUNCTION__, fmt, ##_VA_ARGS__)
#define smbl_log_error(fmt, ...)        \
        smbl_log_error_debug(__FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#define smbl_log_critical(fmt, ...)     \
        smbl_log_critical_debug(__FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)
#define smbl_log_critical_perror(fmt, ...)  \
        smbl_log_critical_perror_debug(__FILE__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)

#endif //_LOGGER_H_