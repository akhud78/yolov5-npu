cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(yolov5_npu)

macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 17)
  endif ()
endmacro(use_cxx11)

find_package(OpenCV REQUIRED)                              

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -fexceptions")

set(SOURCES main.cpp postprocess.cpp)

set(LIB_PATH $ENV{RUNTIME_LIB_PATH})
if(LIB_PATH)
    include_directories(${LIB_PATH}/include) 
    set(LIBRKNNRT ${LIB_PATH}/librknnrt.so)
endif()

set(EXTRA_LIBS ${OpenCV_LIBS} ${LIBRKNNRT})

include_directories(include ${OpenCV_INCLUDE_DIRS})

add_link_options(-fopenmp -s -ldl -lpthread -pthread -lgomp -rdynamic -march=armv8.2-a)

add_executable(yolov5_npu ${SOURCES})

target_link_libraries(yolov5_npu ${EXTRA_LIBS})
