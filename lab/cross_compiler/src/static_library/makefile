#**********************************************************
#
# by jevstein
# 2018/12/11
#
# DEBUG	: DEBUG can be set to YES to include debug info, or NO otherwise(RELEASE)
#		  you can also use like this: make DEBUG:=NO
#**********************************************************

# 1.CONFIG
DEBUG 		:= YES
APP			:= libStaticLibrary
APP_OUT		:= libStaticLibrary.a
ROOT_DIR	:= ../..
PROJECT_DIR := .
OUT_DIR		:= $(ROOT_DIR)/lib
DEFS_DIR	:= 
INCS_DIR	:= -I$(ROOT_DIR)/include
LIBS_DIR	:= 
LIBS		:= 
SRCS		:= $(wildcard *.cpp)

# 2.TOOL CHAIN
CXX				:= g++
COMMON_FLAGS	:= -g
CXX_FLAGS		:= $(COMMON_FLAGS)
MKDIR_P     	:= mkdir -p
CP          	:= cp
RM				:= rm
AR				:= ar rcs
INSTALL			:= $(CP)

ifeq ($(DEBUG), YES)
    OBJ_DIR		:= Debug
else
    OBJ_DIR		:= Release
endif

# 3.FILES
OBJS	:= $(addsuffix .o, $(basename $(SRCS)))
OBJS	:= $(patsubst %.o, $(OBJ_DIR)/%.o, $(OBJS))

# 4.OUTPUT
all: prog install
	$(info $(APP_OUT)\makefile -> all success!)

prog: $(OBJ_DIR)/$(APP_OUT)
	$(info $(APP_OUT)\makefile -> $(OBJ_DIR)/$(APP_OUT))

install: $(OUT_DIR)/$(APP_OUT)
	$(info $(APP)\makefile -> $(OUT_DIR)/$(APP_OUT))

clean:
	$(RM) -rf $(OBJ_DIR)

cleaninstall:
	$(RM) $(OUT_DIR)/$(APP_OUT)

cleanall: clean cleaninstall
	$(info $(APP)\makefile -> clean all success!)

# 5.common rule
$(OBJ_DIR)/%.o : %.cpp
	$(info creating $@ ...)
	@$(MKDIR_P) $(OBJ_DIR) ..
	$(CXX) -c $(CXXFLAGS) $(INCS_DIR) $< -o $@

$(OBJ_DIR)/$(APP_OUT): $(OBJS)
	$(info linking ...)
	$(AR) $@ $(OBJS) $(LIBS)

$(OUT_DIR)/$(APP_OUT): $(OBJ_DIR)/$(APP_OUT)
	$(info installing ...)
	@$(MKDIR_P) $(OUT_DIR) ..
	@$(CP) $< $@

#include $(subst .cpp,.d,$(SRCS))

# 6.PHONY
.PHONY: all prog install clean cleaninstall cleanall