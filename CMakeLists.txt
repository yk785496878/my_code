cmake_minimum_required(VERSION 3.21.0)

project(my_code)

set(ZMQ_BUILD_TESTS OFF CACHE BOOL "disable libzmq tests" FORCE)
set(CPPZMQ_BUILD_TESTS OFF CACHE BOOL "disable cppzmq build tests" FORCE)
add_subdirectory("3rdparty/libzmq-master")
add_subdirectory("3rdparty/cppzmq-master")

set(3RD_LIB_DIR ${PROJECT_SOURCE_DIR}/3rdparty)

# get all cpp file
file(GLOB SRC_FILES
    "base/*.cpp" "*.cpp" 
)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
)

message(STATUS "${PROJECT_SOURCE_DIR}")

target_include_directories(${PROJECT_NAME} PRIVATE
    ${3RD_LIB_DIR}/rapidjson-master/include
)

target_link_libraries(${PROJECT_NAME}
    libzmq
    cppzmq  
)

install(DIRECTORY config_file/
DESTINATION ${PROJECT_SOURCE_DIR}/build/config_file)
