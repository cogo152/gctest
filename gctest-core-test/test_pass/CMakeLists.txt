file(GLOB_RECURSE sources 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

add_executable(test_pass)

target_sources(test_pass
    PRIVATE 
        ${sources}
)

target_link_libraries(test_pass
    PRIVATE 
        gctest::core
)

add_test(NAME "test_pass" COMMAND test_pass)