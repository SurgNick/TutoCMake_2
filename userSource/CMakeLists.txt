
###############################################################################
################################### PROJECT ###################################
###############################################################################

cmake_minimum_required(VERSION 3.16)

project(
    UserProject
    VERSION 1.0
    LANGUAGES CXX
)

# https://doc.qt.io/qt-5/cmake-get-started.html
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
# not good as it uses absolute paths
# set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

SET(CMAKE_INSTALL_RPATH
    "$ORIGIN/../lib"
)

# https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD.html#variable:CMAKE_CXX_STANDARD
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

###############################################################################
#################################### SETUP ####################################
###############################################################################

set(USER_EXE_NAME insane)
set(CMAKE_PREFIX_PATH "../install" CACHE PATH "Prefix search path to look for the needed libraries")

set(USER_SHOW_DEPS "0" CACHE STRING "Display install dependencies info if set to 1")

# https://cmake.org/cmake/help/latest/manual/cmake-packages.7.html#config-file-packages
# https://cmake.org/cmake/help/latest/guide/using-dependencies/index.html

# https://cmake.org/cmake/help/latest/command/find_package.html#search-procedure
find_package(TutoCMakeLib REQUIRED)

find_package(Qt5 5.14 COMPONENTS Gui Qml Quick DBus QmlWorkerScript QuickControls2 QuickTemplates2 XcbQpa)

###############################################################################
############################ IMPLEMENTATION/BUILD #############################
###############################################################################

set(SOURCES
    main.cpp
    Counter.cpp
)

set(HEADERS
    Counter.hpp
)

message(STATUS "QML_IMPORT_PATH : ${QML_IMPORT_PATH}")
set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/qml CACHE STRING "" FORCE)

# qt5_wrap_cpp(SOURCES ${SOURCES})
qt5_add_resources(SOURCES myqml.qrc
    OPTIONS
    --verbose
)

qt5_wrap_cpp(SOURCES ${HEADERS}
    TARGET ${USER_EXE_NAME}
)

message(STATUS "Sources : ${SOURCES}")
add_executable(${USER_EXE_NAME}
    ${SOURCES} ${HEADERS}
)

target_link_libraries(${USER_EXE_NAME} PUBLIC
    TUTOCMAKE2::TutoCMakeLib
    stdc++fs
    Qt5::Gui Qt5::Qml Qt5::Quick Qt5::DBus Qt5::QmlWorkerScript Qt5::QuickControls2 Qt5::QuickTemplates2 Qt5::XcbQpa
)

# CMake with Qt5.14
qt5_import_plugins(${USER_EXE_NAME} 
    INCLUDE Qt5::QtGraphicalEffects
)

# ( https://cmake.org/cmake/help/latest/command/target_compile_options.html#command:target_compile_options )
# https://cmake.org/cmake/help/git-stage/command/target_link_options.html
# needed to set RPATH
target_link_options(${USER_EXE_NAME}
    PUBLIC "LINKER:--disable-new-dtags"
)

# message("INCLUDE DIRS :::: ${Qt5Widgets_INCLUDE_DIRS} : ${QtQml_INCLUDE_DIRS}")
# target_include_directories(${USER_EXE_NAME} PUBLIC
#     $<BUILD_INTERFACE:${Qt5Widgets_INCLUDE_DIRS} ${QtQml_INCLUDE_DIRS}>
# )

###############################################################################
################################# INSTALL QT ##################################
###############################################################################

# https://doc.qt.io/qt-5.12/cmake-manual.html
# message("Qt5Gui_COMPILE_DEFINITIONS      : ${Qt5Gui_COMPILE_DEFINITIONS}")
# message("Qt5Gui_DEFINITIONS              : ${Qt5Gui_DEFINITIONS}")
# message("Qt5Gui_EXECUTABLE_COMPILE_FLAGS : ${Qt5Gui_EXECUTABLE_COMPILE_FLAGS}")
# message("Qt5Gui_FOUND                    : ${Qt5Gui_FOUND}")
# message("Qt5Gui_INCLUDE_DIRS             : ${Qt5Gui_INCLUDE_DIRS}")
# message("Qt5Gui_LIBRARIES                : ${Qt5Gui_LIBRARIES}")
# message("Qt5Gui_PRIVATE_INCLUDE_DIRS     : ${Qt5Gui_PRIVATE_INCLUDE_DIRS}")
# message("Qt5Gui_VERSION_STRING           : ${Qt5Gui_VERSION_STRING}")

# message(STATUS "Qt5Gui_PLUGINS : ${Qt5Gui_PLUGINS}")


### Qt Libs ###

# https://stackoverflow.com/questions/35765106/symbolic-links-cmake/41037224
macro(install_symlink filepath sympath)
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${filepath} ${sympath})")
    install(CODE "message(\"-- Created symlink: ${sympath} -> ${filepath}\")")
endmacro(install_symlink)


set(QtDeps)

get_target_property(QtDep Qt5::QXcbIntegrationPlugin LOCATION)
list(APPEND QtDeps "${QtDep}")

# # Done at Configure time
# file(INSTALL ${QtDeps} DESTINATION "bin/platforms")

# Done at install time
install(FILES
    ${QtDeps}
    DESTINATION "bin/platforms"
)

set(QtDeps)

# libs to install
set(QtNeededLibs
    Qt5::DBus
    Qt5::QmlModels
    Qt5::QmlWorkerScript
    Qt5::Quick
    Qt5::QuickControls2
    Qt5::QuickTemplates2
    Qt5::XcbQpa
)

# for each lib to install, get its LOCATION and append it to QtDeps
foreach(QtNeededLib ${QtNeededLibs})
    get_target_property(QtDepFile ${QtNeededLib} LOCATION)
    list(APPEND QtDeps "${QtDepFile}")
endforeach()

# file(INSTALL ${QtDeps} DESTINATION "bin/lib" FOLLOW_SYMLINK_CHAIN)

# install QtDeps
message("QtDeps ${QtDeps}")
install(FILES
    ${QtDeps}
    DESTINATION "lib"
)

# for each lib to install, create symlink and install it
# https://cmake.org/cmake/help/latest/command/get_filename_component.html
foreach(QtNeededLib ${QtNeededLibs})
    get_target_property(QtFileSoname ${QtNeededLib} IMPORTED_SONAME_RELEASE)
    get_target_property(QtFileLocation ${QtNeededLib} LOCATION)
    get_filename_component(QtFileName ${QtFileLocation} NAME)
    install_symlink(${CMAKE_INSTALL_PREFIX}/lib/${QtFileName} ${CMAKE_INSTALL_PREFIX}/lib/${QtFileSoname})
endforeach()


### xcbglintegrations ###

set(QtNeededXcbLibs
    Qt5::QXcbEglIntegrationPlugin
    Qt5::QXcbGlxIntegrationPlugin
)

set(QtXcbDeps)

foreach(QtNeededXcbLib ${QtNeededXcbLibs})
    get_target_property(QtXcbDepFile ${QtNeededXcbLib} LOCATION)
    list(APPEND QtXcbDeps "${QtXcbDepFile}")
endforeach()

install(FILES
    ${QtXcbDeps}
    DESTINATION "bin/xcbglintegrations"
)


### qml modules ###

set(USER_QT_QML_DIR "${Qt5_DIR}/../../../qml/")

set(USER_QT_QML_DIR_DEPS
    QtGraphicalEffects
    QtQml
    QtQuick
    QtQuick.2
)

# https://cmake.org/cmake/help/latest/command/list.html#transform
list(TRANSFORM USER_QT_QML_DIR_DEPS PREPEND ${USER_QT_QML_DIR})

# https://cmake.org/cmake/help/latest/command/install.html#directory
# message("USER_QT_QML_DIR : ${USER_QT_QML_DIR}")
install(DIRECTORY ${USER_QT_QML_DIR_DEPS} DESTINATION qml
        PATTERN "*.debug" EXCLUDE
)


###############################################################################
############################ INSTALL/PACKAGING APP ############################
###############################################################################

install(
    TARGETS ${USER_EXE_NAME}
    DESTINATION bin
    # RUNTIME
)

# Where to find the lib. USER_DEP_DIR is used in file(GET_RUNTIME_DEPENDENCIES) to search for dependencies and find the .dll or .so (...) files
set(USER_DEP_DIR "${CMAKE_INSTALL_PREFIX}/../install/bin")

# USER_POST_EXCLUDE_REGEXES used to exclude the system dependencies
if(WIN32)
	set(USER_POST_EXCLUDE_REGEXES "system32")
else()
    set(USER_POST_EXCLUDE_REGEXES "linux-gnu")
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
        message(STATUS "USER_TARGET_FILE : <TARGET_FILE:insane> : $<TARGET_FILE:insane>")
	]] 
	SCRIPT
		${CMAKE_CURRENT_BINARY_DIR}/cmake/UserProjectInstallConfigure.cmake
)

set(CPACK_PACKAGE_CONTACT "un sudiste quelconque")

set(CPACK_GENERATOR "ZIP" "DEB")
set(CPACK_PACKAGE_DIRECTORY "CPack")

include(CPack)
