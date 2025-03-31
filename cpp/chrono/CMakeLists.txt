cmake_minimum_required(VERSION 3.26)

set(TARGET chrono_practice)
project( ${TARGET} )

add_executable(${TARGET} "")
set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 20)
set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD_REQUIRED ON)

if(MSVC)
  add_definitions(-D_UNICODE)
  add_definitions(-DUNICODE)
  add_definitions(-DNOMINMAX)
  target_compile_options(${TARGET} PRIVATE "/utf-8")
endif()

#############################

set(HEADER_FILES
  date.h
)

set(SOURCE_FILES
  chrono_practice.cpp
)

target_sources(${TARGET} PRIVATE ${HEADER_FILES} ${SOURCE_FILES})
