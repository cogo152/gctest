set(GCTEST_CMAKE_VERSION 3.22.1)
set(GCTEST_PROJECT_NAMESPACE gctest)
set(GCTEST_PROJECT_NAME core)
set(GCTEST_PROJECT_VERSION 1.0.2)
set(GCTEST_PROJECT_DESCRIPTION "cpp test framework for the asm, c and cpp languages")
set(GCTEST_PROJECT_CONTACT "Gökay Cömert gokay.comert@icloud.com")

cmake_minimum_required (VERSION ${GCTEST_CMAKE_VERSION})

set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "install directory" FORCE)

project (${GCTEST_PROJECT_NAME} VERSION ${GCTEST_PROJECT_VERSION} DESCRIPTION ${GCTEST_PROJECT_DESCRIPTION})

enable_language(CXX)

set(include_directory ${CMAKE_CURRENT_SOURCE_DIR}/include)
file(GLOB_RECURSE includes 
    "${include_directory}/*.hpp"
)

set(source_directory ${CMAKE_CURRENT_SOURCE_DIR}/source)
file(GLOB_RECURSE sources 
    "${source_directory}/*.cpp"
)

add_library(${GCTEST_PROJECT_NAME} INTERFACE)

target_include_directories(${GCTEST_PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${include_directory}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_sources(${GCTEST_PROJECT_NAME}
    INTERFACE
        $<BUILD_INTERFACE:${source_directory}/${GCTEST_PROJECT_NAMESPACE}/${GCTEST_PROJECT_NAME}/gctest_type.cpp>
        $<BUILD_INTERFACE:${source_directory}/${GCTEST_PROJECT_NAMESPACE}/${GCTEST_PROJECT_NAME}/gctest_exception.cpp>
        $<BUILD_INTERFACE:${source_directory}/${GCTEST_PROJECT_NAMESPACE}/${GCTEST_PROJECT_NAME}/gctest_executor.cpp>
        $<BUILD_INTERFACE:${source_directory}/${GCTEST_PROJECT_NAMESPACE}/${GCTEST_PROJECT_NAME}/gctest_main.cpp>

        $<INSTALL_INTERFACE:source/${GCTEST_PROJECT_NAMESPACE}/${GCTEST_PROJECT_NAME}/gctest_type.cpp>
        $<INSTALL_INTERFACE:source/${GCTEST_PROJECT_NAMESPACE}/${GCTEST_PROJECT_NAME}/gctest_exception.cpp>
        $<INSTALL_INTERFACE:source/${GCTEST_PROJECT_NAMESPACE}/${GCTEST_PROJECT_NAME}/gctest_executor.cpp>
        $<INSTALL_INTERFACE:source/${GCTEST_PROJECT_NAMESPACE}/${GCTEST_PROJECT_NAME}/gctest_main.cpp>
)

target_compile_features(${GCTEST_PROJECT_NAME}
    INTERFACE
        #c_std_23 
        cxx_std_23
)

target_compile_options(${GCTEST_PROJECT_NAME}
    INTERFACE
        #-v 
        -Wall
        -Wextra
        -O0
        -g
        -fPIC
        #"-x" "assembler-with-cpp"
)

set_target_properties(${GCTEST_PROJECT_NAME}
    PROPERTIES 
        PUBLIC_HEADER
            "${includes}"
)

set_target_properties(${GCTEST_PROJECT_NAME}
    PROPERTIES 
        OUTPUT_NAME "${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}"
)

enable_testing()

add_subdirectory(test)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

install(
    TARGETS 
        ${GCTEST_PROJECT_NAME}
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

write_basic_package_version_file("${CMAKE_BINARY_DIR}/${GCTEST_PROJECT_NAMESPACE}-${GCTEST_PROJECT_NAME}ConfigVersion.cmake"
    VERSION 
        "${GCTEST_PROJECT_VERSION}"
    COMPATIBILITY 
        AnyNewerVersion
)

configure_package_config_file("${CMAKE_SOURCE_DIR}/Config.cmake.in"
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
set(CPACK_OUTPUT_FILE_PREFIX "${CMAKE_BINARY_DIR}/package")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_COMPONENTS_GROUPING ALL_COMPONENTS_IN_ONE)
set(CPACK_VERBATIM_VARIABLES TRUE)
set(CPACK_STRIP_FILES TRUE)
set(CPACK_GENERATOR "DEB")

set(CPACK_DEB_COMPONENT_INSTALL ON)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
set(CPACK_DEBIAN_FILE_NAME DEB-DEFAULT)
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE all)

include(CPack)