set(SOURCES
    client.c
    logger.c
    hash.c
    list.c
    queue.c
    negotiate.c)
add_library(${SMBL_COMMON_LIBS} STATIC ${SOURCES})

set_target_properties(${SMBL_COMMON_LIBS} PROPERTIES OUTPUT_NAME smbl CLEAN_DIRECT_OUTPUT 1)

install(TARGETS ${SMBL_COMMON_LIBS}
        DESTINATION ${CMAKE_BINARY_DIR})

install(FILES
            client.h
            hash.h
            list.h
            logger.h
            negotiate.h
            queue.h
            util.h
            common.h
            smbl.h
    DESTINATION "${CMAKE_BINARY_DIR}/smbl")