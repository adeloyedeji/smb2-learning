#ifndef _UTIL_H_
#define _UTIL_H_


#define LIKELY_IS(x, y) __builtin_expect((x), (y))
#define LIKELY(x) LIKELY_IS(!!(x), 1)
#define UNLIKELY(x) LIKELY_IS((x), 0)
#define _U_ __attribute__((unused))
typedef enum _bool {
    FALSE = 0,
    TRUE
} bool_t;

#endif //_UTIL_H_   