project (server)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB HEADER_FILE ./*h)
FILE(GLOB SOURCE_FILE ./*cpp)

find_package(Threads REQUIRED)

add_executable(sender ${HEADER_FILE} sender.cpp)
add_executable(receiver ${HEADER_FILE} receiver.cpp)


target_link_libraries(sender -lpthread)
target_link_libraries(sender -lrt)

target_link_libraries(receiver -lpthread)
target_link_libraries(receiver -lrt)

