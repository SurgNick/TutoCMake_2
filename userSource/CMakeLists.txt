
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
set(CMAKE_PREFIX_PATH ../install)
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



install(CODE
	[[
	file(GET_RUNTIME_DEPENDENCIES
		RESOLVED_DEPENDENCIES_VAR deps_resolved
		UNRESOLVED_DEPENDENCIES_VAR deps_unresolved
		CONFLICTING_DEPENDENCIES_PREFIX deps_conflicting
		EXECUTABLES $<TARGET_FILE:insane>
		DIRECTORIES ${CMAKE_INSTALL_PREFIX}/../install/bin
		POST_EXCLUDE_REGEXES "system32"
		)
		message(STATUS "deps_resolved    : ${deps_resolved}")
		# message(STATUS "deps_unresolved  : ${deps_unresolved}")
		message(STATUS "deps_conflicting : ${deps_conflicting}")
		message("CMAKE_INSTALL_PREFIX : ${CMAKE_INSTALL_PREFIX}")
        foreach(dep ${deps_resolved})
			# install(
			# 	FILES
			# 		${dep}
			# 	RUNTIME DESTINATION
			# 		${CMAKE_INSTALL_PREFIX}/bin
			# )

	        file(INSTALL ${dep} DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

	        # file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "${deps_resolved}")

		endforeach()
		]]
)


set(CPACK_GENERATOR "ZIP")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Nicolas Ariba")

include(CPack)