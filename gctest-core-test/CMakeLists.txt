set(GCTEST_CMAKE_VERSION 3.22.1)
set(GCTEST_PROJECT_NAMESPACE gctest)
set(GCTEST_PROJECT_NAME core-test)
set(GCTEST_PROJECT_VERSION 1.0.0)
set(GCTEST_PROJECT_DESCRIPTION "test of the gctest::core")
set(GCTEST_PROJECT_CONTACT "Gökay Cömert gokay.comert@icloud.com")

get_filename_component(current_path ${CMAKE_SOURCE_DIR} PATH)
list(APPEND CMAKE_FIND_ROOT_PATH "${current_path}/gctest-core/build/install")

cmake_minimum_required (VERSION ${GCTEST_CMAKE_VERSION})

project (${GCTEST_PROJECT_NAME} VERSION ${GCTEST_PROJECT_VERSION} DESCRIPTION ${GCTEST_PROJECT_DESCRIPTION})

find_package(gctest-core CONFIG 1.0.0 REQUIRED)

enable_language(CXX)

enable_testing()

add_subdirectory(test_fail)
add_subdirectory(test_pass)



