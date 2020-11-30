project(app)
set(CMAKE_CXX_STANDARD 11)
add_executable(app main.cpp)
target_include_directories(app PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../libx)
target_link_directories(app PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../libx)
target_link_libraries(app dl)
target_link_libraries(app x_v1)
#target_link_options(app PRIVATE -fvisibility=hidden)