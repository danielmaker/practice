cmake_minimum_required(VERSION 3.0)

find_package(Java REQUIRED)
include(UseJava)

set(TARGET eight_queens)
project( ${TARGET} )


FILE(GLOB source
    "${CMAKE_CURRENT_SOURCE_DIR}/EightQueens/src/solution/*.java"
)

add_jar(${TARGET} ${source} ${CMAKE_CURRENT_SOURCE_DIR}/EightQueens/src/Main.java)

set(CMAKE_JAVA_INCLUDE_PATH ${CMAKE_JAVA_INCLUDE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/EightQueens/src/)
set(CMAKE_JAVA_COMPILE_FLAGS "-source" "1.6" "-target" "1.6")

get_target_property(_jarFile ${TARGET} JAR_FILE)
get_target_property(_classDir ${TARGET} CLASSDIR)

message(STATUS "Jar file ${_jarFile}")
message(STATUS "Class compiled to ${_classDir}")

