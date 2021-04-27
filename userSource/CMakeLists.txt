
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
############################## INSTALL/PACKAGING ##############################
###############################################################################

install(
    TARGETS ${USER_EXE_NAME}
    DESTINATION bin
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


set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_DIRECTORY "CPack")

include(CPack)