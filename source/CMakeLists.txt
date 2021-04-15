
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

include(CMakePackageConfigHelpers)
# https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html

set(TUTO_LIB_NAME TutoCMakeLib)
set(TUTO_INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(TUTO_CONFIG_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib/cmake/${TUTO_LIB_NAME})
# https://cmake.org/cmake/help/latest/command/find_package.html#search-procedure

set(TUTO_LIB_TARGET_NAME ${TUTO_LIB_NAME}Targets)

option(BUILD_SHARED_LIBS "Build using shared libraries" OFF)

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

# https://cmake.org/cmake/help/latest/command/target_include_directories.html
target_include_directories(${TUTO_LIB_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	$<INSTALL_INTERFACE:${TUTO_INCLUDE_INSTALL_DIR}>
)
# https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#output-related-expressions

###############################################################################
################################### CONFIG ####################################
###############################################################################

# message("CMAKE_BINARY_DIR         : ${CMAKE_BINARY_DIR}")
# message("CMAKE_SOURCE_DIR         : ${CMAKE_SOURCE_DIR}")
# message("CMAKE_CURRENT_BINARY_DIR : ${CMAKE_CURRENT_BINARY_DIR}")
# message("CMAKE_CURRENT_SOURCE_DIR : ${CMAKE_CURRENT_SOURCE_DIR}")

configure_package_config_file(
	${CMAKE_CURRENT_SOURCE_DIR}/cmake/TutoCMake2Config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/cmake/${TUTO_LIB_NAME}Config.cmake
	INSTALL_DESTINATION ${TUTO_CONFIG_INSTALL_DIR}
	PATH_VARS TUTO_INCLUDE_INSTALL_DIR
)


write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/cmake/${TUTO_LIB_NAME}ConfigVersion.cmake
	COMPATIBILITY ExactVersion
)

###############################################################################
############################## INSTALL/PACKAGING ##############################
###############################################################################

# https://cmake.org/cmake/help/latest/command/install.html
install(
	FILES ${HEADERS}
	DESTINATION ${TUTO_INCLUDE_INSTALL_DIR}/${TUTO_LIB_NAME}
)

install(
	TARGETS ${TUTO_LIB_NAME}
	EXPORT ${TUTO_LIB_TARGET_NAME}
)

###############################################################################
############################### INSTALL/CONFIG ################################
###############################################################################

install(
	FILES
		${CMAKE_CURRENT_BINARY_DIR}/cmake/${TUTO_LIB_NAME}Config.cmake
		${CMAKE_CURRENT_BINARY_DIR}/cmake/${TUTO_LIB_NAME}ConfigVersion.cmake
	DESTINATION
		${TUTO_CONFIG_INSTALL_DIR}
)

# https://cmake.org/cmake/help/latest/command/install.html#export
install(
	EXPORT ${TUTO_LIB_TARGET_NAME}
	DESTINATION ${TUTO_CONFIG_INSTALL_DIR}
	NAMESPACE "TUTOCMAKE2::"
)
