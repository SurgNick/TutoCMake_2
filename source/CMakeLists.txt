
###############################################################################
################################### PROJECT ###################################
###############################################################################

cmake_minimum_required(VERSION 3.12)

project(
	TutoCMake2
	VERSION 1.1
	LANGUAGES CXX
)

###############################################################################
#################################### SETUP ####################################
###############################################################################

set(TUTO_LIB_NAME "TutoCMakeLib")
set(TUTO_INCLUDE_INSTALL_DIR_RELATIVE "include")
set(TUTO_INCLUDE_INSTALL_DIR_ABSOLUTE "${CMAKE_INSTALL_PREFIX}/${TUTO_INCLUDE_INSTALL_DIR_RELATIVE}")
set(TUTO_CONFIG_INSTALL_DIR_RELATIVE "lib/cmake/${TUTO_LIB_NAME}")
set(TUTO_CONFIG_INSTALL_DIR_ABSOLUTE "${CMAKE_INSTALL_PREFIX}/${TUTO_CONFIG_INSTALL_DIR_RELATIVE}")

# https://cmake.org/cmake/help/latest/command/find_package.html#search-procedure

set(TUTO_LIB_TARGET_NAME "${TUTO_LIB_NAME}Targets")

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)


# https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html
include(CMakePackageConfigHelpers)


# https://cmake.org/cmake/help/v3.20/module/GenerateExportHeader.html
include(GenerateExportHeader)
set(GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated")
message(STATUS "Generated files goes in : ${GENERATED_DIR}")
file(MAKE_DIRECTORY ${GENERATED_DIR})

set(TUTO_EXPORT_FILE_NAME "${TUTO_LIB_NAME}_export.h")
set(TUTO_EXPORT_MACRO_NAME "TUTO_MYLIB_EXPORT")

###############################################################################
############################ IMPLEMENTATION/BUILD #############################
###############################################################################

set(SOURCES
	src/mylib/mylib.cpp
)

set(HEADERS
	src/mylib/mylib.hpp
)

add_library(${TUTO_LIB_NAME} ${SOURCES} ${HEADERS})


set(LIB_STATIC_DEFINE TUTOCMAKELIB_STATIC_DEFINE)
set(LIB_EXPORT_DEFINE TutoCMakeLib_EXPORTS)

# generate a file suitable for preprocessor inclusion which contains EXPORT macros to be used in library classes
generate_export_header(
	${TUTO_LIB_NAME}
	EXPORT_FILE_NAME ${GENERATED_DIR}/${TUTO_EXPORT_FILE_NAME}
	STATIC_DEFINE ${LIB_STATIC_DEFINE}
)


# https://cmake.org/cmake/help/latest/command/target_include_directories.html
target_include_directories(${TUTO_LIB_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	$<BUILD_INTERFACE:${GENERATED_DIR}>

	$<INSTALL_INTERFACE:${TUTO_INCLUDE_INSTALL_DIR_ABSOLUTE}>
)
# https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#output-related-expressions

# https://cmake.org/cmake/help/v3.20/guide/tutorial/index.html?highlight=export%20symbol#mixing-static-and-shared-step-9
# define the symbol stating we are using the declspec(dllexport) when building on windows
if(BUILD_SHARED_LIBS)
	target_compile_definitions(${TUTO_LIB_NAME} PRIVATE "${LIB_EXPORT_DEFINE}")
else()
	target_compile_definitions(${TUTO_LIB_NAME} PUBLIC "${LIB_STATIC_DEFINE}")
endif()

###############################################################################
################################### CONFIG ####################################
###############################################################################

# message("CMAKE_BINARY_DIR         : ${CMAKE_BINARY_DIR}")
# message("CMAKE_SOURCE_DIR         : ${CMAKE_SOURCE_DIR}")
# message("CMAKE_CURRENT_BINARY_DIR : ${CMAKE_CURRENT_BINARY_DIR}")
# message("CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")

# generate the config file that is includes the exports
configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/TutoCMake2Config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/cmake/${TUTO_LIB_NAME}Config.cmake
	INSTALL_DESTINATION ${TUTO_CONFIG_INSTALL_DIR_ABSOLUTE}
	PATH_VARS TUTO_INCLUDE_INSTALL_DIR_ABSOLUTE
)

# generate the version file for the config file
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/cmake/${TUTO_LIB_NAME}ConfigVersion.cmake
	COMPATIBILITY ExactVersion
)


###############################################################################
############################## INSTALL/PACKAGING ##############################
###############################################################################

# Note that the DESTINATION option of the install() command must be a relative path; otherwise installed files are ignored by CPack

# https://cmake.org/cmake/help/latest/command/install.html
# install the include files
install(
	FILES
		${HEADERS}
		${GENERATED_DIR}/${TUTO_EXPORT_FILE_NAME}
	DESTINATION
		${TUTO_INCLUDE_INSTALL_DIR_RELATIVE}/${TUTO_LIB_NAME}
)

# install the library
install(
	TARGETS ${TUTO_LIB_NAME}
	EXPORT ${TUTO_LIB_TARGET_NAME}
)

###############################################################################
############################### INSTALL/CONFIG ################################
###############################################################################

# install the configuration files
install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/cmake/${TUTO_LIB_NAME}Config.cmake
		${CMAKE_CURRENT_BINARY_DIR}/cmake/${TUTO_LIB_NAME}ConfigVersion.cmake
	DESTINATION
		${TUTO_CONFIG_INSTALL_DIR_RELATIVE}
)

# https://cmake.org/cmake/help/latest/command/install.html#export
# install the generated <export-name>.cmake file
install(
	EXPORT ${TUTO_LIB_TARGET_NAME}
	DESTINATION ${TUTO_CONFIG_INSTALL_DIR_RELATIVE}
	NAMESPACE "TUTOCMAKE2::"
)
