# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer

# Include any dependencies generated for this target.
include CMakeFiles/TCPServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/TCPServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/TCPServer.dir/flags.make

CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o: CMakeFiles/TCPServer.dir/flags.make
CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o: src/BytestreamEventHandler.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o -c /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/BytestreamEventHandler.cpp

CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/BytestreamEventHandler.cpp > CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.i

CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/BytestreamEventHandler.cpp -o CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.s

CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o.requires:

.PHONY : CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o.requires

CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o.provides: CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o.requires
	$(MAKE) -f CMakeFiles/TCPServer.dir/build.make CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o.provides.build
.PHONY : CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o.provides

CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o.provides.build: CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o


CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o: CMakeFiles/TCPServer.dir/flags.make
CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o: src/ConnectionInfo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o -c /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/ConnectionInfo.cpp

CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/ConnectionInfo.cpp > CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.i

CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/ConnectionInfo.cpp -o CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.s

CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o.requires:

.PHONY : CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o.requires

CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o.provides: CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o.requires
	$(MAKE) -f CMakeFiles/TCPServer.dir/build.make CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o.provides.build
.PHONY : CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o.provides

CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o.provides.build: CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o


CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o: CMakeFiles/TCPServer.dir/flags.make
CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o: src/ConnectionListener.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o -c /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/ConnectionListener.cpp

CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/ConnectionListener.cpp > CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.i

CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/ConnectionListener.cpp -o CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.s

CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o.requires:

.PHONY : CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o.requires

CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o.provides: CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o.requires
	$(MAKE) -f CMakeFiles/TCPServer.dir/build.make CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o.provides.build
.PHONY : CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o.provides

CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o.provides.build: CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o


CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o: CMakeFiles/TCPServer.dir/flags.make
CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o: src/EPollObject.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o -c /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/EPollObject.cpp

CMakeFiles/TCPServer.dir/src/EPollObject.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TCPServer.dir/src/EPollObject.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/EPollObject.cpp > CMakeFiles/TCPServer.dir/src/EPollObject.cpp.i

CMakeFiles/TCPServer.dir/src/EPollObject.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TCPServer.dir/src/EPollObject.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/EPollObject.cpp -o CMakeFiles/TCPServer.dir/src/EPollObject.cpp.s

CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o.requires:

.PHONY : CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o.requires

CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o.provides: CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o.requires
	$(MAKE) -f CMakeFiles/TCPServer.dir/build.make CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o.provides.build
.PHONY : CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o.provides

CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o.provides.build: CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o


CMakeFiles/TCPServer.dir/src/Event.cpp.o: CMakeFiles/TCPServer.dir/flags.make
CMakeFiles/TCPServer.dir/src/Event.cpp.o: src/Event.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/TCPServer.dir/src/Event.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TCPServer.dir/src/Event.cpp.o -c /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/Event.cpp

CMakeFiles/TCPServer.dir/src/Event.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TCPServer.dir/src/Event.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/Event.cpp > CMakeFiles/TCPServer.dir/src/Event.cpp.i

CMakeFiles/TCPServer.dir/src/Event.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TCPServer.dir/src/Event.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/Event.cpp -o CMakeFiles/TCPServer.dir/src/Event.cpp.s

CMakeFiles/TCPServer.dir/src/Event.cpp.o.requires:

.PHONY : CMakeFiles/TCPServer.dir/src/Event.cpp.o.requires

CMakeFiles/TCPServer.dir/src/Event.cpp.o.provides: CMakeFiles/TCPServer.dir/src/Event.cpp.o.requires
	$(MAKE) -f CMakeFiles/TCPServer.dir/build.make CMakeFiles/TCPServer.dir/src/Event.cpp.o.provides.build
.PHONY : CMakeFiles/TCPServer.dir/src/Event.cpp.o.provides

CMakeFiles/TCPServer.dir/src/Event.cpp.o.provides.build: CMakeFiles/TCPServer.dir/src/Event.cpp.o


CMakeFiles/TCPServer.dir/src/Reactor.cpp.o: CMakeFiles/TCPServer.dir/flags.make
CMakeFiles/TCPServer.dir/src/Reactor.cpp.o: src/Reactor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/TCPServer.dir/src/Reactor.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TCPServer.dir/src/Reactor.cpp.o -c /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/Reactor.cpp

CMakeFiles/TCPServer.dir/src/Reactor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TCPServer.dir/src/Reactor.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/Reactor.cpp > CMakeFiles/TCPServer.dir/src/Reactor.cpp.i

CMakeFiles/TCPServer.dir/src/Reactor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TCPServer.dir/src/Reactor.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/Reactor.cpp -o CMakeFiles/TCPServer.dir/src/Reactor.cpp.s

CMakeFiles/TCPServer.dir/src/Reactor.cpp.o.requires:

.PHONY : CMakeFiles/TCPServer.dir/src/Reactor.cpp.o.requires

CMakeFiles/TCPServer.dir/src/Reactor.cpp.o.provides: CMakeFiles/TCPServer.dir/src/Reactor.cpp.o.requires
	$(MAKE) -f CMakeFiles/TCPServer.dir/build.make CMakeFiles/TCPServer.dir/src/Reactor.cpp.o.provides.build
.PHONY : CMakeFiles/TCPServer.dir/src/Reactor.cpp.o.provides

CMakeFiles/TCPServer.dir/src/Reactor.cpp.o.provides.build: CMakeFiles/TCPServer.dir/src/Reactor.cpp.o


CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o: CMakeFiles/TCPServer.dir/flags.make
CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o: src/ReactorCenter.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o -c /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/ReactorCenter.cpp

CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/ReactorCenter.cpp > CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.i

CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/ReactorCenter.cpp -o CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.s

CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o.requires:

.PHONY : CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o.requires

CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o.provides: CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o.requires
	$(MAKE) -f CMakeFiles/TCPServer.dir/build.make CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o.provides.build
.PHONY : CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o.provides

CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o.provides.build: CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o


CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o: CMakeFiles/TCPServer.dir/flags.make
CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o: src/TcpServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o -c /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/TcpServer.cpp

CMakeFiles/TCPServer.dir/src/TcpServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TCPServer.dir/src/TcpServer.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/TcpServer.cpp > CMakeFiles/TCPServer.dir/src/TcpServer.cpp.i

CMakeFiles/TCPServer.dir/src/TcpServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TCPServer.dir/src/TcpServer.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/TcpServer.cpp -o CMakeFiles/TCPServer.dir/src/TcpServer.cpp.s

CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o.requires:

.PHONY : CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o.requires

CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o.provides: CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o.requires
	$(MAKE) -f CMakeFiles/TCPServer.dir/build.make CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o.provides.build
.PHONY : CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o.provides

CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o.provides.build: CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o


CMakeFiles/TCPServer.dir/src/welcome.cc.o: CMakeFiles/TCPServer.dir/flags.make
CMakeFiles/TCPServer.dir/src/welcome.cc.o: src/welcome.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/TCPServer.dir/src/welcome.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/TCPServer.dir/src/welcome.cc.o -c /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/welcome.cc

CMakeFiles/TCPServer.dir/src/welcome.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/TCPServer.dir/src/welcome.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/welcome.cc > CMakeFiles/TCPServer.dir/src/welcome.cc.i

CMakeFiles/TCPServer.dir/src/welcome.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/TCPServer.dir/src/welcome.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/src/welcome.cc -o CMakeFiles/TCPServer.dir/src/welcome.cc.s

CMakeFiles/TCPServer.dir/src/welcome.cc.o.requires:

.PHONY : CMakeFiles/TCPServer.dir/src/welcome.cc.o.requires

CMakeFiles/TCPServer.dir/src/welcome.cc.o.provides: CMakeFiles/TCPServer.dir/src/welcome.cc.o.requires
	$(MAKE) -f CMakeFiles/TCPServer.dir/build.make CMakeFiles/TCPServer.dir/src/welcome.cc.o.provides.build
.PHONY : CMakeFiles/TCPServer.dir/src/welcome.cc.o.provides

CMakeFiles/TCPServer.dir/src/welcome.cc.o.provides.build: CMakeFiles/TCPServer.dir/src/welcome.cc.o


# Object files for target TCPServer
TCPServer_OBJECTS = \
"CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o" \
"CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o" \
"CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o" \
"CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o" \
"CMakeFiles/TCPServer.dir/src/Event.cpp.o" \
"CMakeFiles/TCPServer.dir/src/Reactor.cpp.o" \
"CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o" \
"CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o" \
"CMakeFiles/TCPServer.dir/src/welcome.cc.o"

# External object files for target TCPServer
TCPServer_EXTERNAL_OBJECTS =

bin/TCPServer: CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o
bin/TCPServer: CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o
bin/TCPServer: CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o
bin/TCPServer: CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o
bin/TCPServer: CMakeFiles/TCPServer.dir/src/Event.cpp.o
bin/TCPServer: CMakeFiles/TCPServer.dir/src/Reactor.cpp.o
bin/TCPServer: CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o
bin/TCPServer: CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o
bin/TCPServer: CMakeFiles/TCPServer.dir/src/welcome.cc.o
bin/TCPServer: CMakeFiles/TCPServer.dir/build.make
bin/TCPServer: CMakeFiles/TCPServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable bin/TCPServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/TCPServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/TCPServer.dir/build: bin/TCPServer

.PHONY : CMakeFiles/TCPServer.dir/build

CMakeFiles/TCPServer.dir/requires: CMakeFiles/TCPServer.dir/src/BytestreamEventHandler.cpp.o.requires
CMakeFiles/TCPServer.dir/requires: CMakeFiles/TCPServer.dir/src/ConnectionInfo.cpp.o.requires
CMakeFiles/TCPServer.dir/requires: CMakeFiles/TCPServer.dir/src/ConnectionListener.cpp.o.requires
CMakeFiles/TCPServer.dir/requires: CMakeFiles/TCPServer.dir/src/EPollObject.cpp.o.requires
CMakeFiles/TCPServer.dir/requires: CMakeFiles/TCPServer.dir/src/Event.cpp.o.requires
CMakeFiles/TCPServer.dir/requires: CMakeFiles/TCPServer.dir/src/Reactor.cpp.o.requires
CMakeFiles/TCPServer.dir/requires: CMakeFiles/TCPServer.dir/src/ReactorCenter.cpp.o.requires
CMakeFiles/TCPServer.dir/requires: CMakeFiles/TCPServer.dir/src/TcpServer.cpp.o.requires
CMakeFiles/TCPServer.dir/requires: CMakeFiles/TCPServer.dir/src/welcome.cc.o.requires

.PHONY : CMakeFiles/TCPServer.dir/requires

CMakeFiles/TCPServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/TCPServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/TCPServer.dir/clean

CMakeFiles/TCPServer.dir/depend:
	cd /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer /mnt/hgfs/test/17.socket/EpollServer/BaseServer/TCPServer/CMakeFiles/TCPServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/TCPServer.dir/depend

