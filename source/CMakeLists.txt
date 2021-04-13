# https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html
# https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html
# https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html#command:write_basic_package_version_file



cmake_minimum_required(VERSION 3.12)

project(
	TutoCMake2
	VERSION 1.0
	DESCRIPTION
	"Petite description, on va voir ou elle se met :) ba nul part :'("
	LANGUAGES CXX
)

include(CMakePackageConfigHelpers)


message("CMAKE_INSTALL_PREFIX : ${CMAKE_INSTALL_PREFIX}")

set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(CONFIG_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib/cmake/${PROJECT_NAME}")


################################### Implementation ##############################


set(TUTO_SOURCES
	src/mylib.cpp
)

set(TUTO_HEADERS
	src/mylib.hpp
)

add_library(${PROJECT_NAME} ${TUTO_SOURCES} ${TUTO_HEADERS})


target_include_directories(
	${PROJECT_NAME} PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	$<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>
)

################################### Config ##############################


# set(LIEN2 /home/nicolas/document/TutoCMake/TutoCMake_2/install/lib/libTutoCMake2.a)
# set(LIEN2 /mnt/d/CodeInfo/Cpparti/TutoCMake/TutoCMake_2/install/lib/libTutoCMake2.a)
set(TUTOCMAKE2_CMAKE_TARGETS_EXPORT_NAME "${PROJECT_NAME}Targets")

# https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html?highlight=configure_package_config_file#command:configure_package_config_file

configure_package_config_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/TutoCMake2Config.cmake.in"
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
	INSTALL_DESTINATION ${CONFIG_INSTALL_DIR}
	PATH_VARS INCLUDE_INSTALL_DIR
)

write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake"
	COMPATIBILITY ExactVersion
)

install(
	FILES
		"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
		"${CMAKE_CURRENT_BINARY_DIR}/cmake/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION
		${CONFIG_INSTALL_DIR}
)

install(
    EXPORT ${TUTOCMAKE2_CMAKE_TARGETS_EXPORT_NAME}
    NAMESPACE "TUTOCMAKE2::"
    DESTINATION ${CONFIG_INSTALL_DIR}
)

################################### Install/Packaging ##############################



# install(
# 	TARGETS ${PROJECT_NAME}
# )

# install(
# 	DIRECTORY src
# 	DESTINATION ${INCLUDE_INSTALL_DIR}
# 	FILES_MATCHING PATTERN "*.hpp"
# )

install(
	FILES ${TUTO_HEADERS} 
	DESTINATION ${INCLUDE_INSTALL_DIR}/${PROJECT_NAME}
	)

install(
	TARGETS ${PROJECT_NAME}
	EXPORT ${TUTOCMAKE2_CMAKE_TARGETS_EXPORT_NAME}
	RUNTIME DESTINATION "bin"
	LIBRARY DESTINATION "lib"
	ARCHIVE DESTINATION "lib"
	)

