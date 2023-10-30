file(GLOB_RECURSE test_sources 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

set(test_name "${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}_test")

add_executable(${test_name})

target_include_directories(${test_name}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${test_name}
    PRIVATE 
        ${test_sources}
)

target_link_libraries(${test_name}
    PRIVATE
        ${GCTEST_PROJECT_NAME}
)

target_compile_definitions(${test_name}
    PRIVATE
        __NOT_MAIN__
)

add_test(NAME ${test_name} COMMAND ${test_name})