cmake_minimum_required(VERSION 3.0)

set(TARGET eight_queens)
project( ${TARGET} )

set(CMAKE_BUILD_TYPE Debug)

message( CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} )
message( CMAKE_C_COMPILER=${CMAKE_C_COMPILER} )


#############################

include( source_file.txt )

add_executable( ${TARGET} ${SOURCES})


#############################
# gtest

include_directories( ../../../Imports/gtest/include )

if(MSVC)
    if(CMAKE_BUILD_TYPE MATCHES  Debug)
        target_link_libraries( ${TARGET} ${CMAKE_SOURCE_DIR}/../../../Imports/gtest/lib/msvc2010/gtest-mdd.lib )
    else()
        target_link_libraries( ${TARGET} ${CMAKE_SOURCE_DIR}/../../../Imports/gtest/lib/msvc2010/gtest-md.lib )
    endif (CMAKE_BUILD_TYPE MATCHES  Debug)
endif(MSVC)

if(APPLE)
    target_link_libraries( ${TARGET} ${CMAKE_SOURCE_DIR}/../../../Imports/gtest/lib/macx-llvm/libgtest.a )
endif(APPLE)
