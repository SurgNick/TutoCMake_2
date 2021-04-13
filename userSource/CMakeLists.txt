
cmake_minimum_required(VERSION 3.12)

project(
    userTutoLib
    LANGUAGES C CXX
)

set(CMAKE_PREFIX_PATH /home/nicolas/document/TutoCMake/TutoCMake_2/install)
# message("CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}")
find_package(TutoCMake2)

add_executable(userExe main.cpp)

target_link_libraries(userExe ${TutoCMake2_LIBRARIES})
target_include_directories(userExe PRIVATE ${TutoCMake2_INCLUDE_DIRS})