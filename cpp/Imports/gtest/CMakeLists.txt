cmake_minimum_required(VERSION 2.8)

set(TARGET gtest)
project( ${TARGET} )

set(CMAKE_BUILD_TYPE Release)

#################################################

if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

macro(print_variable VAR)
  message("${Yellow}${VAR}${ColourReset} = " ${Cyan} ${${VAR}} ${ColourReset})
endmacro()

#################################################

print_variable(CMAKE_SYSTEM_NAME)
print_variable(CMAKE_BUILD_TYPE)
print_variable(CMAKE_CXX_COMPILER_ID)

string(TOLOWER ${CMAKE_SYSTEM_NAME} PLATFORM)
string(TOLOWER ${CMAKE_CXX_COMPILER_ID} COMPILER)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/lib/${PLATFORM}-${COMPILER}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/lib/${PLATFORM}-${COMPILER}")
print_variable(CMAKE_ARCHIVE_OUTPUT_DIRECTORY)

include_directories(./ include)
add_library(gtest src/gtest-all.cc)
