cmake_minimum_required(VERSION 3.1)

set(TARGET chrono_practice)
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
    chrono_practice.cpp
    )

add_executable(${TARGET} ${HEADER_FILES} ${SOURCE_FILES})

