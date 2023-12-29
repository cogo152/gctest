set(gctest_interface_library_test "${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}-${gctest_interface_library}_test")
set(gctest_static_library_test "${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}-${gctest_static_library}_test")
set(gctest_shared_library_test "${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}-${gctest_shared_library}_test")

file(GLOB_RECURSE test_sources 
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

set(gctest_test_include_directories
    ${CMAKE_CURRENT_SOURCE_DIR}
)

set(gctest_test_sources
    ${test_sources}
)

# test if PRIVATE for compile options, definitions, etc..

add_executable(${gctest_interface_library_test})

target_include_directories(${gctest_interface_library_test}
    PRIVATE 
        ${gctest_test_include_directories}
)

target_sources(${gctest_interface_library_test}
    PRIVATE 
        ${gctest_test_sources}
)

target_compile_definitions(${gctest_interface_library_test}
    PRIVATE
        ${gctest_test_compile_definitions}
)

target_link_libraries(${gctest_interface_library_test}
    PRIVATE
        ${gctest_interface_library}
)

add_executable(${gctest_static_library_test})

target_include_directories(${gctest_static_library_test}
    PRIVATE 
        ${gctest_test_include_directories}
)

target_sources(${gctest_static_library_test}
    PRIVATE 
        ${gctest_test_sources}
)

target_compile_definitions(${gctest_static_library_test}
    PRIVATE
        ${gctest_test_compile_definitions}
)

target_link_libraries(${gctest_static_library_test}
    PRIVATE
        ${gctest_static_library}
)

add_executable(${gctest_shared_library_test})

target_include_directories(${gctest_shared_library_test}
    PRIVATE 
        ${gctest_test_include_directories}
)

target_sources(${gctest_shared_library_test}
    PRIVATE 
        ${gctest_test_sources}
)

target_compile_definitions(${gctest_shared_library_test}
    PRIVATE
        ${gctest_test_compile_definitions}
)

target_link_libraries(${gctest_shared_library_test}
    PRIVATE
        ${gctest_shared_library}
)

if(ARM32 OR ARM64)
    add_test(NAME ${gctest_interface_library_test} COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} ${GCTEST_CROSSCOMPILING_EMULATOR_PARAMETERS} ${gctest_interface_library_test})
    add_test(NAME ${gctest_static_library_test} COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} ${GCTEST_CROSSCOMPILING_EMULATOR_PARAMETERS} ${gctest_static_library_test})
    add_test(NAME ${gctest_shared_library_test} COMMAND ${CMAKE_CROSSCOMPILING_EMULATOR} ${GCTEST_CROSSCOMPILING_EMULATOR_PARAMETERS} ${gctest_shared_library_test})
else()
    add_test(NAME ${gctest_interface_library_test} COMMAND ${gctest_interface_library_test})
    add_test(NAME ${gctest_static_library_test} COMMAND ${gctest_static_library_test})
    add_test(NAME ${gctest_shared_library_test} COMMAND ${gctest_shared_library_test})
endif()