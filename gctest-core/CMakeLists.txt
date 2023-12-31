set(GCTEST_CMAKE_VERSION 3.20.0)
set(GCTEST_PROJECT_NAMESPACE gctest)
set(GCTEST_PROJECT_NAME core)
set(GCTEST_PROJECT_VERSION 1.1.1)
set(GCTEST_PROJECT_DESCRIPTION "cpp test framework for the asm, c and cpp languages")
set(GCTEST_PROJECT_CONTACT "Gökay Cömert gokay.comert@icloud.com")

cmake_minimum_required (VERSION ${GCTEST_CMAKE_VERSION})

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "install directory" FORCE)
set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "cmake build type" FORCE)

if(ARM32)
    message(STATUS "ARM32")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/gctest.toolchain.arm32.cmake")
    set(GCTEST_CROSSCOMPILING_EMULATOR_PARAMETERS -L;/usr/arm-linux-gnueabihf)
elseif(ARM64)
    message(STATUS "ARM64")
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/gctest.toolchain.arm64.cmake")
    set(GCTEST_CROSSCOMPILING_EMULATOR_PARAMETERS -L;/usr/aarch64-linux-gnu)
else()
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/gctest.toolchain.local.cmake")
endif()

project (${GCTEST_PROJECT_NAME} VERSION ${GCTEST_PROJECT_VERSION} DESCRIPTION ${GCTEST_PROJECT_DESCRIPTION})

set(CMAKE_EXPORT_COMPILE_COMMANDS FALSE)
set(CMAKE_VERBOSE_MAKEFILE FALSE)
enable_language(CXX)

find_package(Threads REQUIRED)

if(OWN_TEST)
    message(STATUS "OWN TEST")
    set(gctest_compile_definitions
        __SOURCE_LOCATION_IMPL__ #Rhel8 does not support <source_location>
        __OWN_TEST__
    )
else()
    message(STATUS "RELEASE")
    set(gctest_compile_definitions
        __SOURCE_LOCATION_IMPL__ # Rhel8 does not support <source_location>
    )
endif()

set(gctest_compile_features
    cxx_std_20
)

set(gctest_compile_options # Not only for this project but also for other projects
    -Wall
    -Wextra
    -O0
    -g
    -fPIC
)

set(gctest_link_libraries
    ${CMAKE_THREAD_LIBS_INIT}
)

set(gctest_interface_library ${GCTEST_PROJECT_NAME}_interface)
set(gctest_static_library ${GCTEST_PROJECT_NAME}_static)
set(gctest_shared_library ${GCTEST_PROJECT_NAME}_shared)

set(include_directory ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(source_directory ${CMAKE_CURRENT_SOURCE_DIR}/source)

file(GLOB_RECURSE public_headers 
    "${include_directory}/*.hpp"
)

file(GLOB_RECURSE sources 
    "${source_directory}/*.cpp"
)

add_library(${gctest_interface_library} INTERFACE)

target_include_directories(${gctest_interface_library}
    INTERFACE
        $<BUILD_INTERFACE:${include_directory}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

foreach(source_path IN LISTS sources)
    string(LENGTH "${source_path}" source_path_length)
    string(FIND "${source_path}" "/source" source_folder_location)
    math(EXPR source_begin "${source_folder_location} + 8" OUTPUT_FORMAT DECIMAL)
    math(EXPR source_length "${source_path_length} - ${source_begin}" OUTPUT_FORMAT DECIMAL)
    string(SUBSTRING ${source_path} ${source_begin} ${source_length} source)
        
    target_sources(${gctest_interface_library}
        INTERFACE
        $<BUILD_INTERFACE:${source_directory}/${source}>
        $<INSTALL_INTERFACE:source/${GCTEST_PROJECT_NAMESPACE}/${GCTEST_PROJECT_NAME}/${source}>
    )
endforeach()

target_compile_definitions(${gctest_interface_library}
    INTERFACE
        ${gctest_compile_definitions}
)

target_compile_features(${gctest_interface_library}
    INTERFACE
        ${gctest_compile_features}
)

target_compile_options(${gctest_interface_library}
    INTERFACE
        ${gctest_compile_options}
)

set_target_properties(${gctest_interface_library}
    PROPERTIES 
        PUBLIC_HEADER
            "${public_headers}"
)

set_target_properties(${gctest_interface_library}
    PROPERTIES 
        OUTPUT_NAME "${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}"
)

target_link_libraries(${gctest_interface_library}
    INTERFACE
        ${gctest_link_libraries}
)

add_library(${gctest_static_library} STATIC)

target_include_directories(${gctest_static_library}
    PRIVATE
        ${source_directory}
    PUBLIC
        $<BUILD_INTERFACE:${include_directory}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_sources(${gctest_static_library}
    PRIVATE
        ${sources}
)

target_compile_definitions(${gctest_static_library}
    PUBLIC
        ${gctest_compile_definitions}
)

target_compile_features(${gctest_static_library}
    PUBLIC
        ${gctest_compile_features}
)

target_compile_options(${gctest_static_library}
    PUBLIC
        ${gctest_compile_options}
)

set_target_properties(${gctest_static_library}
    PROPERTIES 
        PUBLIC_HEADER
            "${public_headers}"
)

set_target_properties(${gctest_static_library}
    PROPERTIES 
        OUTPUT_NAME "${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}"
)

target_link_libraries(${gctest_static_library}
    PUBLIC
        ${gctest_link_libraries}
)

add_library(${gctest_shared_library} SHARED)

target_include_directories(${gctest_shared_library}
    PRIVATE
        ${source_directory}
    PUBLIC
        $<BUILD_INTERFACE:${include_directory}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_sources(${gctest_shared_library}
    PRIVATE
        ${sources}
)

target_compile_definitions(${gctest_shared_library}
    PUBLIC
        ${gctest_compile_definitions}
)

target_compile_features(${gctest_shared_library}
    PUBLIC
        ${gctest_compile_features}
)

target_compile_options(${gctest_shared_library}
    PUBLIC
        ${gctest_compile_options}
)

set_target_properties(${gctest_shared_library}
    PROPERTIES 
        PUBLIC_HEADER
            "${public_headers}"
)

set_target_properties(${gctest_shared_library}
    PROPERTIES 
        OUTPUT_NAME "${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}"
)

target_link_libraries(${gctest_shared_library}
    PUBLIC
        ${gctest_link_libraries}
)

if(OWN_TEST)
    message(STATUS "TESTING")
    enable_testing()
    add_subdirectory(test)
endif()

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
    TARGETS 
        ${gctest_interface_library} ${gctest_static_library} ${gctest_shared_library}
    EXPORT 
        "${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}Targets"
    INCLUDES DESTINATION 
        ${CMAKE_INSTALL_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION 
        ${CMAKE_INSTALL_INCLUDEDIR}/${GCTEST_PROJECT_NAMESPACE}/${GCTEST_PROJECT_NAME}
)

install(
    EXPORT 
        "${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}Targets"
    FILE 
        "${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}Targets.cmake"
    NAMESPACE 
        ${GCTEST_PROJECT_NAMESPACE}::
    DESTINATION 
        cmake/${GCTEST_PROJECT_NAMESPACE}/${GCTEST_PROJECT_NAME}
)

install(
    FILES 
        ${sources}
    DESTINATION 
        source/${GCTEST_PROJECT_NAMESPACE}/${GCTEST_PROJECT_NAME}
)

write_basic_package_version_file(
    "${CMAKE_BINARY_DIR}/${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}ConfigVersion.cmake"
    VERSION 
        "${GCTEST_PROJECT_VERSION}"
    COMPATIBILITY 
        AnyNewerVersion
)

configure_package_config_file(
    "${CMAKE_SOURCE_DIR}/Config.cmake.in"
    "${CMAKE_BINARY_DIR}/${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION 
        cmake
)

install(
    FILES
        "${CMAKE_BINARY_DIR}/${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}Config.cmake"
        "${CMAKE_BINARY_DIR}/${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION 
        cmake
)

export(
    EXPORT 
        "${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}Targets"
    FILE 
        "${CMAKE_BINARY_DIR}/cmake/${GCTEST_PROJECT_NAMESPACE}/${GCTEST_PROJECT_NAME}/${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}Targets.cmake"
    NAMESPACE 
        ${GCTEST_PROJECT_NAMESPACE}::
)

set(CPACK_PACKAGE_NAME "${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}" CACHE STRING "package name")
set(CPACK_PACKAGE_CONTACT ${GCTEST_PROJECT_CONTACT})
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_SOURCE_DIR}/package")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)
set(CPACK_VERBATIM_VARIABLES TRUE)
set(CPACK_STRIP_FILES TRUE)

set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
if(ARM32)
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE arm)
    set(CPACK_GENERATOR "DEB")
elseif(ARM64)
    set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE arm64)
    set(CPACK_GENERATOR "DEB")
else()
    set(CPACK_RPM_COMPONENT_INSTALL ON)
    set(CPACK_RPM_PACKAGE_AUTOREQ YES)
    set(CPACK_RPM_FILE_NAME RPM-DEFAULT)
    set(CPACK_GENERATOR "DEB;RPM")
endif()

include(CPack)
