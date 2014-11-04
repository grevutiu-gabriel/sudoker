project(sudoker)
cmake_minimum_required(VERSION 2.8.8)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

SET(EIGEN_VERSION_MINIMUM 3.1.2)

FIND_PACKAGE(Eigen3 ${EIGEN_VERSION_MINIMUM} REQUIRED)
IF (EIGEN3_FOUND)
	SET(HAVE_EIGEN3 1)
	INCLUDE_DIRECTORIES(SYSTEM ${EIGEN_INCLUDE_DIR})
ENDIF()

include_directories("src/")
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in ${CMAKE_CURRENT_SOURCE_DIR}/src/config.h.in)

add_executable(sudoker src/sudoker.cc src/SudokuProblem.cc src/SudokuSolver.cc src/BacktrackSolver.cc)
