cmake_minimum_required(VERSION 3.16)
project(CoolLogger)


SET(PROJECT_NAME "Cool Logger")
SET(APP_VERSION_STRING 1.0)

add_definitions(
    -std=c++17
)


add_subdirectory(src/liblogger)

add_executable(c_logger.out
               src/main.cpp
              )

target_link_libraries(c_logger.out PRIVATE logger_lib)
