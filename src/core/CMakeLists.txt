set(SOURCES
    client.c
    logger.c
    hash.c
    list.c
    queue.c
    negotiate.c
    config.c)

add_library(${SMBL_COMMON_LIBS} STATIC ${SOURCES})

set_target_properties(${SMBL_COMMON_LIBS} PROPERTIES OUTPUT_NAME smbl CLEAN_DIRECT_OUTPUT 1)