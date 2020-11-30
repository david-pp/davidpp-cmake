cmake_minimum_required(VERSION 3.18)
project(plugins)
set(CMAKE_CXX_STANDARD 11)
add_library(plugin_1 SHARED plugin_1.cpp plugin_class.cpp)
target_include_directories(plugin_1 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../libx)
target_link_directories(plugin_1 PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../libx)
target_link_libraries(plugin_1 PRIVATE x_v2)
#target_link_options(plugin_1 PRIVATE -fvisibility=hidden)
#target_link_options(plugin_1 PRIVATE -Bsymbolic)