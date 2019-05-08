#1.project name
PROJECT(simpledemo)

#2.the version of CMake
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

#3.assign source file names in the current directory to DIR_SRCS
AUX_SOURCE_DIRECTORY(. DIR_SRCS)

#4.compile the source files in DIR_SRCS into an executable file named 'simpledemo'
ADD_EXECUTABLE(simpledemo ${DIR_SRCS})

#TODO: then you can execute a command like this: cmake [options] <path-to-source>
# e.g: 
#    1：cmake .
#    2：make