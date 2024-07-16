set(SOURCES
    api.c)

add_executable(api_test ${SOURCES})
include_directories("${CMAKE_SOURCE_DIR}/src/core")

install(PROGRAMS "${CMAKE_CURRENT_BINARY_DIR}/api_test"
    DESTINATION "${CMAKE_SOURCE_DIR}/src/tests/api")

target_link_libraries(api_test
    ${SMBL_COMMON_LIBS})