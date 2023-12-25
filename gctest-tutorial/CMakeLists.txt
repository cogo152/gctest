set(GCTEST_CMAKE_VERSION 3.20.0)
set(GCTEST_PROJECT_NAMESPACE gctest)
set(GCTEST_PROJECT_NAME tutorial)
set(GCTEST_PROJECT_VERSION 1.0.4)
set(GCTEST_PROJECT_DESCRIPTION "tutorial of the gctest framework")
set(GCTEST_PROJECT_CONTACT "Gökay Cömert gokay.comert@icloud.com")

get_filename_component(current_path ${CMAKE_SOURCE_DIR} PATH)
list(APPEND CMAKE_FIND_ROOT_PATH "${current_path}/gctest-core/build/install")

cmake_minimum_required (VERSION ${GCTEST_CMAKE_VERSION})

project (${GCTEST_PROJECT_NAME} VERSION ${GCTEST_PROJECT_VERSION} DESCRIPTION ${GCTEST_PROJECT_DESCRIPTION})

find_package(gctest-core CONFIG 1.0.4 REQUIRED)

enable_language(CXX)

enable_testing()

file(GLOB_RECURSE sources 
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
)

add_executable(${GCTEST_PROJECT_NAME})

target_sources(${GCTEST_PROJECT_NAME}
    PRIVATE 
        ${sources}
)

target_link_libraries(${GCTEST_PROJECT_NAME}
    PRIVATE 
        gctest::core
)

add_test(NAME "${GCTEST_PROJECT_NAME}" COMMAND ${GCTEST_PROJECT_NAME})



