cmake_minimum_required(VERSION 3.17)

if(POLICY CMP0011)
  cmake_policy(SET CMP0011 NEW)
endif()


#**************************************************************************************************
# General CMake settings
#**************************************************************************************************
project(Test_pybind11)

#**************************************************************************************************
# Find Package **************************************************************************************************
find_package(OpenCV REQUIRED)
MESSAGE( " *** OpenCV_INCLUDE_DIRS : " ${OpenCV_INCLUDE_DIRS} )
MESSAGE( " *** OpenCV_LIB_DIRS : " ${OpenCV_LIB_DIRS} )
MESSAGE( " *** OpenCV_LIBS : " ${OpenCV_LIBS} )

find_package(pybind11 CONFIG REQUIRED)
MESSAGE( " *** PYTHON_INCLUDE_DIRS : " ${PYTHON_INCLUDE_DIRS} )
MESSAGE( " *** PYTHON_LIBRARIES : " ${PYTHON_LIBRARIES} )


set(NUMPY_INCLUDE_DIR "" CACHE FILEPATH "Path to numpy header if cmake can't find them.")
if (NOT ${NUMPY_INCLUDE_DIR} STREQUAL "")
  message( " *** NUMPY_INCLUDE_DIR : ${NUMPY_INCLUDE_DIR}" )
  if(NOT EXISTS ${NUMPY_INCLUDE_DIR}/numpy/ndarrayobject.h)
    message(SEND_ERROR "Can't find numpy/ndarrayobject.h in ${NUMPY_INCLUDE_DIR}")
    endif()
  include_directories(${NUMPY_INCLUDE_DIR})
endif()


#**************************************************************************************************
# Include **************************************************************************************************
include_directories(${pybind11_INCLUDE_DIR})
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS}/opencv4)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

#**************************************************************************************************
# Set variable **************************************************************************************************
SET(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/ndarray_converter.cpp
)

#**************************************************************************************************
# Set compiler **************************************************************************************************
SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -O3 -fPIC")

#**************************************************************************************************
# Linker **************************************************************************************************
LINK_DIRECTORIES(
  ${OpenCV_LIB_DIR}
)

#**************************************************************************************************
# Make configuration
#**************************************************************************************************
add_library(test_modules SHARED ${SOURCES} ${CMAKE_CURRENT_SOURCE_DIR}/tests/cpp/test.cpp)
target_link_libraries(test_modules ${PYTHON_LIBRARIES} ${OpenCV_LIBS})
SET_TARGET_PROPERTIES(test_modules PROPERTIES PREFIX "")

install(TARGETS test_modules DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_modules)
