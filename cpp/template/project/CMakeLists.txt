cmake_minimum_required(VERSION 2.8)

set(TARGET cpp-template.example)
project( ${TARGET} )

set(CMAKE_BUILD_TYPE Debug)

message( CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME} )
message( CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} )
message( CMAKE_C_COMPILER=${CMAKE_C_COMPILER} )

#############################

include( source_file.txt )

add_executable( ${TARGET} ${SOURCES})

# ##### C++ standard #####
set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 14)  # C++14
set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD_REQUIRED ON)


#############################
# gtest

string(TOLOWER ${CMAKE_SYSTEM_NAME} PLATFORM)
string(TOLOWER ${CMAKE_CXX_COMPILER_ID} COMPILER)

set(GTEST_PATH ../../Imports/gtest)
set(GTEST_LIB_PATH "${CMAKE_CURRENT_LIST_DIR}/${GTEST_PATH}/lib/${PLATFORM}-${COMPILER}")
include_directories( ${GTEST_PATH}/include )

if(MSVC)
    if(CMAKE_BUILD_TYPE MATCHES  Debug)
        target_link_libraries(${TARGET} ${CMAKE_SOURCE_DIR}/${GTEST_PATH}/lib/msvc2010/gtest-mdd.lib)
    else()
        target_link_libraries(${TARGET} ${CMAKE_SOURCE_DIR}/${GTEST_PATH}/lib/msvc2010/gtest-md.lib)
    endif (CMAKE_BUILD_TYPE MATCHES  Debug)
endif(MSVC)

if(APPLE)
    target_link_libraries(${TARGET} ${CMAKE_SOURCE_DIR}/${GTEST_PATH}/lib/macx-llvm/libgtest.a)
endif(APPLE)

if("Linux" STREQUAL ${CMAKE_SYSTEM_NAME})
    target_link_libraries(${TARGET} ${GTEST_LIB_PATH}/libgtest.a)
    #pthread
    find_package(Threads REQUIRED)
    if(THREADS_HAVE_PTHREAD_ARG)
      target_compile_options(PUBLIC ${TARGET} "-pthread")
    endif()
    if(CMAKE_THREAD_LIBS_INIT)
      target_link_libraries(${TARGET} "${CMAKE_THREAD_LIBS_INIT}")
    endif()
endif()
