file(GLOB_RECURSE sources 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(test_fail)

target_sources(test_fail
    PRIVATE 
        ${sources}
)

target_link_libraries(test_fail
    PRIVATE 
        gctest::core
)

add_test(NAME "test_fail" COMMAND test_fail)