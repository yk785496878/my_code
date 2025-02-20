cmake_minimum_required(VERSION 3.21.0)

project(sim_send)

set(ZMQ_BUILD_TESTS OFF CACHE BOOL "disable libzmq tests" FORCE)
set(CPPZMQ_BUILD_TESTS OFF CACHE BOOL "disable cppzmq build tests" FORCE)

add_subdirectory("3rdparty/json-3.11.2")
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
    ${3RD_LIB_DIR}/json-3.11.2/include
)

target_link_libraries(${PROJECT_NAME}
    nlohmann_json
    libzmq
    cppzmq
)

install(DIRECTORY data/
DESTINATION ${PROJECT_SOURCE_DIR}/build/config_file)
