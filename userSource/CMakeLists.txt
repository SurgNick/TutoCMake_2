
###############################################################################
################################### PROJECT ###################################
###############################################################################

cmake_minimum_required(VERSION 3.16)

project(
    UserProject
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

###############################################################################
#################################### SETUP ####################################
###############################################################################

set(USER_EXE_NAME insane)
set(CMAKE_PREFIX_PATH "../install" CACHE PATH "Prefix search path to look for the needed libraries")
# https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#config-file-packages
# https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html

# https://cmake.org/cmake/help/latest/command/find_package.html#search-procedure
find_package(TutoCMakeLib REQUIRED)

find_package(Qt5 5.12 COMPONENTS Charts Concurrent Multimedia Qml Quick Xml)


###############################################################################
############################ IMPLEMENTATION/BUILD #############################
###############################################################################

add_executable(${USER_EXE_NAME}
    main.cpp
    qml.qrc
)

target_link_libraries(${USER_EXE_NAME} PUBLIC
    TUTOCMAKE2::TutoCMakeLib
    Qt5::Charts Qt5::Concurrent Qt5::Multimedia Qt5::Qml Qt5::Quick Qt5::Xml
)

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
