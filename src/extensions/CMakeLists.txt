set(EXT_SOURCES
        string.c)

add_library(${STD_LIBRARY_EXT_NAME} STATIC ${EXT_SOURCES})

set_target_properties(${STD_LIBRARY_EXT_NAME} PROPERTIES OUTPUT_NAME smbl-extensions CLEAN_DIRECT_OUTPUT 1)

target_include_directories(${STD_LIBRARY_EXT_NAME}
                            PRIVATE
                            "${CMAKE_SOURCE_DIR}/extensions/include")