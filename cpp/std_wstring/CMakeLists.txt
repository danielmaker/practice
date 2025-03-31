cmake_minimum_required(VERSION 3.26)

set(TARGET wstring_example)
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

)

set(SOURCE_FILES
  wstring_example.cpp
)

if(WIN32)
  target_include_directories(${TARGET}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/windows
  )

  LIST(APPEND HEADER_FILES
      windows/WinUnicodeUtil.h
  )

  LIST(APPEND SOURCE_FILES
      windows/WinUnicodeUtil.cpp
  )
endif()

target_sources(${TARGET} PRIVATE ${HEADER_FILES} ${SOURCE_FILES})
