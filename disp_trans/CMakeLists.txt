cmake_minimum_required(VERSION 3.21.0)

project(disp_services)

set(3RD_LIB_DIR ${PROJECT_SOURCE_DIR}/3rdparty)

# get all cpp file
file(GLOB SRC_FILES
    "common/*.cpp" "*.cpp" "data/*.cpp"
)

add_executable(${PROJECT_NAME}
    ${SRC_FILES}
)

message(STATUS "${PROJECT_SOURCE_DIR}")

# install(DIRECTORY config_file/
# DESTINATION ${PROJECT_SOURCE_DIR}/build/config_file)