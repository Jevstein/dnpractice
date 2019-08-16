cmake_minimum_required(VERSION 3.10)
project(loong)

set(CMAKE_CXX_STANDARD 17)
set(model server.cpp event.cpp network.cpp log.cpp)
add_executable(loong main.cpp ${model})
