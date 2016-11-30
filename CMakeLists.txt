project(Test_pybind11)

#**************************************************************************************************
# General cMake settings 
#**************************************************************************************************
cmake_minimum_required(VERSION 3.5)

#**************************************************************************************************
# Find Package **************************************************************************************************
find_package(OpenCV 3 REQUIRED) 
MESSAGE( " *** OpenCV_INCLUDE_DIRS : " ${OpenCV_INCLUDE_DIRS} ) 
MESSAGE( " *** OpenCV_LIB_DIRS : " ${OpenCV_LIB_DIRS} ) 
MESSAGE( " *** OpenCV_LIBS : " ${OpenCV_LIBS} )

find_package(PythonLibs 2.7 EXACT REQUIRED)
MESSAGE( " *** PYTHON_INCLUDE_DIRS : " ${PYTHON_INCLUDE_DIRS} ) 
MESSAGE( " *** PYTHON_LIBRARIES : " ${PYTHON_LIBRARIES} ) 

#**************************************************************************************************
# Include **************************************************************************************************
include_directories(${PYTHON_INCLUDE_DIRS})
include_directories(${OpenCV_INCLUDE_DIRS}) 
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

#**************************************************************************************************
# Set variable **************************************************************************************************
SET(SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/example.cpp
)

#**************************************************************************************************
# Python Link **************************************************************************************************
# ligne obtenu par python2-config --cflags --ldflags
# ou python3-config --cflags --ldflags
# SET(PYTHON_INCLUDE "-I/usr/include/python3.5m -I/usr/include/python3.5m  -Wno-unused-result -Wsign-compare -g -fstack-protector-strong -Wformat -Werror=format-security  -DNDEBUG -g -fwrapv -O3 -Wall -Wstrict-prototypes -L/usr/lib/python3.5/config-3.5m-x86_64-linux-gnu -L/usr/lib -lpython3.5m -lpthread -ldl  -lutil -lm  -Xlinker -export-dynamic -Wl,-O1 -Wl,-Bsymbolic-functions")

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
add_library(eb SHARED ${SOURCES})
target_link_libraries(eb ${PYTHON_LIBRARIES} ${OpenCV_LIBS})
SET_TARGET_PROPERTIES(eb PROPERTIES PREFIX "")

