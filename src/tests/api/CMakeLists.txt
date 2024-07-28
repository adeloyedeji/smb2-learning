set(SOURCES
    api.c)

set(API_TEST_NAME api_test)

add_executable(${API_TEST_NAME} ${SOURCES})

target_link_libraries(${API_TEST_NAME}
                        PUBLIC
                        ${SMBL_COMMON_LIBS})

target_include_directories(${API_TEST_NAME}
                            PUBLIC
                            "${CMAKE_SOURCE_DIR}/src/core")

install(FILES 
            "${CMAKE_CURRENT_BINARY_DIR}/api_test"
            DESTINATION "${CMAKE_SOURCE_DIR}/src/tests/api"
            PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE)

