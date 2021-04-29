
###############################################################################
################################### PROJECT ###################################
###############################################################################

cmake_minimum_required(VERSION 3.16)

project(
    UserProject
    VERSION 1.0
    LANGUAGES CXX
)

###############################################################################
#################################### SETUP ####################################
###############################################################################

set(USER_EXE_NAME insane)
set(CMAKE_PREFIX_PATH "../install" CACHE PATH "Prefix search path to look for the needed libraries")
# https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#config-file-packages
# https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html

# https://cmake.org/cmake/help/latest/command/find_package.html#search-procedure
find_package(TutoCMakeLib REQUIRED)

###############################################################################
############################ IMPLEMENTATION/BUILD #############################
###############################################################################

add_executable(${USER_EXE_NAME} main.cpp)

target_link_libraries(${USER_EXE_NAME} PUBLIC TUTOCMAKE2::TutoCMakeLib)

###############################################################################
################################### INSTALL ###################################
###############################################################################

install(
    TARGETS ${USER_EXE_NAME}
	# https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#output-artifacts
    RUNTIME DESTINATION bin
	COMPONENT applications
)

# Where to find the lib. USER_DEP_DIR is used in file(GET_RUNTIME_DEPENDENCIES) to search for dependencies and find the .dll or .so (...) files
set(USER_DEP_DIR "${CMAKE_INSTALL_PREFIX}/../install/bin")

# USER_POST_EXCLUDE_REGEXES used to exclude the system dependencies
if(WIN32)
	set(USER_POST_EXCLUDE_REGEXES "system32")
else()
	set(USER_POST_EXCLUDE_REGEXES "")
endif()


# https://cmake.org/cmake/help/latest/command/configure_file.html
configure_file(
	cmake/UserProjectInstallConfigure.cmake.in
	cmake/UserProjectInstallConfigure.cmake
	@ONLY
)

# https://cmake.org/cmake/help/latest/command/install.html#script
install(
	CODE [[ 
		set(USER_TARGET_FILE "$<TARGET_FILE:insane>")
	]] 
	SCRIPT
		${CMAKE_CURRENT_BINARY_DIR}/cmake/UserProjectInstallConfigure.cmake
)


###############################################################################
################################## PACKAGING ##################################
###############################################################################

# https://cmake.org/cmake/help/latest/cpack_gen/nsis.html
# https://cmake.org/cmake/help/latest/module/CPackComponent.html
# https://gitlab.kitware.com/cmake/community/-/wikis/doc/cpack/PackageGenerators


# # https://cmake.org/cmake/help/latest/module/InstallRequiredSystemLibraries.html#module:InstallRequiredSystemLibraries
# # search and install compiler-provided system runtime libraries 
# include(InstallRequiredSystemLibraries)

option(USE_NSIS "Use NSIS generator to produce installer" ON)

# Custom target for packaging.
if(USE_NSIS)
	set(CPACK_GENERATOR "NSIS")
else(USE_NSIS)
	set(CPACK_GENERATOR "ZIP")
endif(USE_NSIS)


# set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_DIRECTORY "CPack")

set(CPACK_PACKAGE_NAME "${PROJECT_NAME}_${USER_EXE_NAME}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_NAME}_${USER_EXE_NAME} - Insane Math")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
# everybody does this following lines but it seems CPACK_PACKAGE_VERSION has priority over the three others
# set (CPACK_PACKAGE_VERSION_MAJOR "1")
# set (CPACK_PACKAGE_VERSION_MINOR "0")
# set (CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Insane Math")
# SET(CPACK_NSIS_MODIFY_PATH ON)
# set(CPACK_NSIS_MUI_ICON "VIRUS.ico")


# https://dominoc925.blogspot.com/2016/09/create-windows-installer-using-cmake.html

# Define components and their display names
set(CPACK_COMPONENTS_ALL applications libraries headers)
# CPACK_COMPONENT_<compName>_DISPLAY_NAME
set(CPACK_COMPONENT_APPLICATIONS_DISPLAY_NAME "Insane Applications")
set(CPACK_COMPONENT_LIBRARIES_DISPLAY_NAME "Libraries")
set(CPACK_COMPONENT_HEADERS_DISPLAY_NAME "C++ Headers")

# Define dependencies between components
set(CPACK_COMPONENT_HEADERS_DEPENDS libraries)

# Define groups
set(CPACK_COMPONENT_APPLICATIONS_GROUP "Runtime")
set(CPACK_COMPONENT_LIBRARIES_GROUP "Development")
set(CPACK_COMPONENT_HEADERS_GROUP "Development")

set(CPACK_COMPONENT_GROUP_DEVELOPMENT_DESCRIPTION
   "All of the tools you'll ever need to develop software"
)

# Define NSIS installation types, what are these lines for ? idk
set(CPACK_ALL_INSTALL_TYPES Full Developer)
set(CPACK_COMPONENT_LIBRARIES_INSTALL_TYPES Developer Full)
set(CPACK_COMPONENT_HEADERS_INSTALL_TYPES Developer Full)
set(CPACK_COMPONENT_APPLICATIONS_INSTALL_TYPES Full)


INCLUDE(CPack)

# # https://martinrotter.github.io/it-programming/2014/05/09/integrating-nsis-cmake/
# # NSIS.template.in NSIS.InstallOptions.ini.in are searched with CMAKE_MODULE_PATH
# message("CMAKE_MODULE_PATH : ${CMAKE_MODULE_PATH}")
# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/resources/nsis ${CMAKE_MODULE_PATH})
# message("CMAKE_MODULE_PATH : ${CMAKE_MODULE_PATH}")