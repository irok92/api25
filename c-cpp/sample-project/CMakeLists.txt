cmake_minimum_required(VERSION 3.28)

project(my_project)

add_subdirectory(deps/raylib)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*.c)
add_executable(my_app ${MY_SOURCES})
target_include_directories(my_app PUBLIC include/)
target_link_libraries(my_app raylib_static)


file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS src/*.cpp)
add_executable(my_app_cpp ${MY_SOURCES})
target_include_directories(my_app_cpp PUBLIC include/)
target_link_libraries(my_app_cpp raylib_static)