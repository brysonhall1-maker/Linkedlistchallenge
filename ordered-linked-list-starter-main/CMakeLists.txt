# Set minimum CMAKE
cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
project( LinkedListChallenge )

# require C++20
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_EXTENSIONS OFF )
set( CMAKE_CXX_STANDARD_REQUIRED ON )

set( APP_EXECUTABLE LinkedListTest )

set( LIB_NAME classLibrary )

# Add the class .cpp and .h files
add_library( ${LIB_NAME} STATIC
    src/MemberDO.cpp inc/MemberDO.h inc/LinkedList.hpp )
target_include_directories( ${LIB_NAME} PUBLIC inc )

ADD_EXECUTABLE( ${APP_EXECUTABLE} src/LinkedListTest.cpp )
TARGET_LINK_LIBRARIES( ${APP_EXECUTABLE} ${LIB_NAME} )

set_property( DIRECTORY PROPERTY VS_STARTUP_PROJECT ${APP_EXECUTABLE} )

include (CTest)
add_test(${APP_EXECUTABLE}_constructors ${APP_EXECUTABLE} 1)
add_test(${APP_EXECUTABLE}_insert ${APP_EXECUTABLE} 2)
add_test(${APP_EXECUTABLE}_output ${APP_EXECUTABLE} 3)
add_test(${APP_EXECUTABLE}_gets ${APP_EXECUTABLE} 4)
add_test(${APP_EXECUTABLE}_find ${APP_EXECUTABLE} 5)
add_test(${APP_EXECUTABLE}_remove ${APP_EXECUTABLE} 6)
add_test(${APP_EXECUTABLE}_clear ${APP_EXECUTABLE} 7)
add_test(${APP_EXECUTABLE}_deep_copies ${APP_EXECUTABLE} 8)
add_test(${APP_EXECUTABLE}_template ${APP_EXECUTABLE} 9)
add_test(${APP_EXECUTABLE}_other ${APP_EXECUTABLE} 10)

find_program(VALGRIND "valgrind")
if(VALGRIND)
    add_custom_target(valgrind
        COMMAND "${VALGRIND}" --tool=memcheck --leak-check=yes --show-reachable=yes --error-exitcode=1 $<TARGET_FILE:${APP_EXECUTABLE}>)
endif()
