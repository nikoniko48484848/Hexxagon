cmake_minimum_required(VERSION 3.24)
project(Hexxagon)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)
include(FetchContent)
FETCHCONTENT_DECLARE(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git)
FETCHCONTENT_MAKEAVAILABLE(SFML)
add_executable(Hexxagon main.cpp Game.cpp Game.h Player.cpp Player.h)
target_link_libraries(Hexxagon sfml-system sfml-window sfml-graphics sfml-audio)