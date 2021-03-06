# -----------------------------------------------------------------------------
#         cppad_swig: A C++ Object Library and SWIG Interface to CppAD
#          Copyright (C) 2017-17 Bradley M. Bell (bradbell@seanet.com)
#              This program is distributed under the terms of the
#          GNU Affero General Public License version 3.0 or later see
#                     http://www.gnu.org/licenses/agpl.txt
# -----------------------------------------------------------------------------
FIND_PACKAGE(SWIG)
FIND_PROGRAM(octave_config NAMES octave-config)
IF( SWIG_FOUND AND octave_config )
	#
	# include the swig specific macros
	INCLUDE( ${CMAKE_ROOT}/Modules/UseSWIG.cmake )
	#
	# use include files in parent directory
	INCLUDE_DIRECTORIES( ${CMAKE_CURRENT_SOURCE_DIR}/.. )
	#
	# treat like a C++ files
	SET_SOURCE_FILES_PROPERTIES(../swig_example.i PROPERTIES CPLUSPLUS ON)
	#
	# swig flags when processing this file
	SET_SOURCE_FILES_PROPERTIES(./swig_example.i PROPERTIES SWIG_FLAGS "-Wall")
	#
	# getg octave include directories
	EXECUTE_PROCESS(
		COMMAND ${octave_config} -p OCTINCLUDEDIR
		OUTPUT_VARIABLE  octave_include_dirs
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	# unix style paths
	STRING(REGEX REPLACE
		"/octave$" "" octave_include_dirs ${octave_include_dirs}
	)
	# windows styple paths
	STRING(REGEX REPLACE
		"\\octave$" "" octave_include_dirs ${octave_include_dirs}
	)
	#
	# octave library directories
	EXECUTE_PROCESS(
		COMMAND ${octave_config} -p OCTLIBDIR
		OUTPUT_VARIABLE  octave_library_dirs
		OUTPUT_STRIP_TRAILING_WHITESPACE
	)
	#
	# liboctinterp
	FIND_LIBRARY(octave_liboctinterp
		NAMES octinterp liboctinterp
		PATHS "${octave_library_dirs}"
	)
	#
	# liboctave
	FIND_LIBRARY(octave_liboctave
		NAMES octave liboctave
		PATHS "${octave_library_dirs}"
	)
	#
	# include directory determined by find octive-config
	# (treat like system include files to suppress warnings)
	INCLUDE_DIRECTORIES( SYSTEM ${octave_include_dirs})
	#
	# SWIG_ADD_MODULE(name language [ files ])
	SWIG_ADD_MODULE(m_example octave ../swig_example.i ../swig_example.cpp)
	#
	# SWIG_LINK_LIBRARIES(name [ libraries ])
	SWIG_LINK_LIBRARIES(m_example
		${octave_liboctinterp} ${octave_liboctave}
	)
	#
	# additional flags for compiling swig wrapper
	SET_TARGET_PROPERTIES( ${SWIG_MODULE_m_example_REAL_NAME}
		 PROPERTIES COMPILE_FLAGS "${swig_cxx_flags}"
	)
	#
	# copy check_example.m from source to binary directory
	ADD_CUSTOM_TARGET(check_example_m
		"${CMAKE_COMMAND}" -E copy
		"${CMAKE_CURRENT_SOURCE_DIR}/check_example.m"
		"${CMAKE_CURRENT_BINARY_DIR}/check_example.m"
		DEPENDS
		"${CMAKE_CURRENT_SOURCE_DIR}/check_example.m"
	)
	# check_example_octave
	ADD_CUSTOM_TARGET(check_example_octave
		octave check_example.m
		DEPENDS ${SWIG_MODULE_m_example_REAL_NAME} check_example_m
	)
	MESSAGE(STATUS "make check_example_octave: available")
	#
	# add this check to list of checks for parent directory
	SET(check_example_depends
		${check_example_depends} check_example_octave PARENT_SCOPE
	)
	#
ENDIF( SWIG_FOUND AND octave_config )
