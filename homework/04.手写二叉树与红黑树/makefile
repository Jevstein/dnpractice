#**********************************************************
#
# by jevstein
# 2019/01/27
#
# DEBUG	: DEBUG can be set to YES to include debug info, or NO otherwise(RELEASE)
#		  you can also use like this: make DEBUG:=NO
#**********************************************************

# 1.CONFIG
DEBUG 		= YES
SOURCE 		= $(wildcard *.c)
TARGETS 	= $(patsubst %.c, %, $(SOURCE))

# 2.TOOL CHAIN
CC 			= gcc
CFLAGS 		= -Wall -g
MKDIR_P     = mkdir -p
CP          = cp
RM			= rm
INSTALL		= $(CP)
EXPORET		= $(CP)

ifeq ($(DEBUG), YES)
    OBJ_DIR	= Debug
else
    OBJ_DIR	= Release
endif

# 3.OUTPUT
all: $(TARGETS)

clean:
	-rm -rf $(OBJ_DIR)

# 4.RULE
$(TARGETS):%:%.c
	@$(MKDIR_P) $(OBJ_DIR) ..
	$(CC) $< $(CFLAGS) -o $(OBJ_DIR)/$@

# .PHONY
.PHONY:clean all
