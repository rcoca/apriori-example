project(apriori-test)
cmake_minimum_required(VERSION 2.8)
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-backtrace-limit=0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall  -pedantic")
endif()

set(MSRC_LIST utils.cpp combination.cpp transaction_table.cpp main.cpp)

add_executable(${PROJECT_NAME} ${MSRC_LIST})

