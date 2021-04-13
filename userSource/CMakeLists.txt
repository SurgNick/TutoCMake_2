
cmake_minimum_required(VERSION 3.12)

project(
    userTutoLib
    LANGUAGES C CXX
)

# set(CMAKE_PREFIX_PATH /home/nicolas/document/TutoCMake/TutoCMake_2/install)
set(CMAKE_PREFIX_PATH /mnt/d/CodeInfo/Cpparti/TutoCMake/TutoCMake_2/install)


# message("CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}")
find_package(TutoCMake2 REQUIRED)

add_executable(userExe main.cpp)

target_link_libraries(userExe TUTOCMAKE2::TutoCMake2)
# target_include_directories(userExe PRIVATE ${TutoCMake2_INCLUDE_DIRS})

install(
    TARGETS userExe
    DESTINATION bin
)


# LD_LIBRARY_PATH=/mnt/d/CodeInfo/Cpparti/TutoCMake/TutoCMake_2/install/lib ../userInstall/bin/userExe