
###############################################################################
################################### PROJECT ###################################
###############################################################################

cmake_minimum_required(VERSION 3.12)

project(
    UserProject
    VERSION 1.0
    LANGUAGES CXX
)

###############################################################################
#################################### SETUP ####################################
###############################################################################

set(USER_EXE_NAME insane.exe)
set(CMAKE_PREFIX_PATH ../install)
# https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#config-file-packages
# https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html

# https://cmake.org/cmake/help/latest/command/find_package.html#search-procedure
find_package(TutoCMakeLib REQUIRED)

###############################################################################
############################ IMPLEMENTATION/BUILD #############################
###############################################################################

add_executable(${USER_EXE_NAME} main.cpp)

target_link_libraries(${USER_EXE_NAME} TUTOCMAKE2::TutoCMakeLib)

###############################################################################
############################## INSTALL/PACKAGING ##############################
###############################################################################

install(
    TARGETS ${USER_EXE_NAME}
    DESTINATION bin
)
