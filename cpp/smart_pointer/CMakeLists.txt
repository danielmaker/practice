cmake_minimum_required(VERSION 3.1)

set(TARGET smart_pointer)
project( ${TARGET} )


set(CMAKE_BUILD_TYPE Debug)

message( CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME} )
message( CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} )
message( CMAKE_C_COMPILER=${CMAKE_C_COMPILER} )

set(CMAKE_CXX_STANDARD 14)

#############################

# include_directories( ./ )

set(HEADER_FILES
    )


set(SOURCE_FILES
    smart_pointer.cpp
    )

add_executable(${TARGET} ${HEADER_FILES} ${SOURCE_FILES})

