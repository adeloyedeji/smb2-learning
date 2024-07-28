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

target_link_libraries(${SMBL_COMMON_LIBS}
                        PUBLIC
                        ${STD_LIBRARY_EXT_NAME})

target_include_directories(${SMBL_COMMON_LIBS}
                            PRIVATE
                            "${CMAKE_SOURCE_DIR}/extensions/include")