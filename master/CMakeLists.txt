project (master)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

FILE(GLOB SOURCE_FILES *.cpp)


include_directories(${CMAKE_SOURCE_DIR}/shared_memory_manager/include)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_BINARY_DIR}/shared_memory_manager/libshared_memory_manager.a)
