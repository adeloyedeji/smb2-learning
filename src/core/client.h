#ifndef _CLIENT_H_
#define _CLIENT_H_

#define FOREACH_FRUIT(FRUIT)    \
        FRUIT(apple)            \
        FRUIT(orange)           \
        FRUIT(grape)            \
        FRUIT(banana)           \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING

#define INFO 1
#define ERR 2
#define LOG_MESSAGE(prio, stream, msg, ...)                                 \
        do {                                                                \
            char *str;                                                      \
            if (prio == INFO)                                               \
                str = "INFO";                                               \
            else                                                            \
                str = "ERR";                                                \
            fprintf(stream, "[%s][%s]:\t%s:%d: "msg" \n",                   \
                    __TIME__, str, __FILE__, __LINE__, ##__VA_ARGS__);      \
        } while(0)                                                          \

enum FRUIT_ENUM {
    FOREACH_FRUIT(GENERATE_ENUM)
};

void smbl_init(char *config);

#endif //_CLIENT_H_