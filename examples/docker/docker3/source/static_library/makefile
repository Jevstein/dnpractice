#**********************************************************
#
# by jevstein
# 2018/12/11
#
#**********************************************************

#**********************************************************
#
#	user design
#**********************************************************

# DEBUG can be set to YES to include debug info, or NO otherwise
DEBUG := YES
HOME	:= ../..
OUTPUT	:= $(HOME)/lib/libStaticLibrary.a
DEFS	:= 
INCS	:=  -I$(HOME)/include/StaticLibrary
LIBS	:= 

#**********************************************************

CXX		:= g++
LD		:= g++
AR		:= ar rcs
RANLIB	:= ranlib

DEBUG_CXXFLAGS		:= -Wall -g -DDEBUG -Wno-deprecated
RELEASE_CXXFLAGS	:= -Wall -O3 -DNDEBUG

DEBUG_LDFLAGS		:= -g
RELEASE_LDFLAGS		:=

ifeq (YES, $(DEBUG))
	CXXFLAGS		:= $(DEBUG_CXXFLAGS) $(DEFS)
	LDFLLAGS		:= $(DEBUG_LDFLAGS) $(DEFS)
else
	CXXFLAGS		:= $(RELEASE_CXXFLAGS) $(DEFS)
	LDFLLAGS		:= $(RELEASE_CSSFLAGS) $(DEFS)
endif                                                                                        

all:$(OUTPUT)

SRCS	:= $(wildcard *.cpp)\
			# $(wildcard zlib/*.c) $(wildcard sqlite/*.c)

OBJS	:= $(addsuffix .o, $(basename $(SRCS)))

#DEPS	:= $(addsuffix .d, $(basename $(SRCS)))
#**********************************************************
#	OUTPUT
#**********************************************************
include $(subst .cpp,.d,$(SRCS))

%.d : %.cpp
	$(CXX) -M $(CPPFLAGS) $(INCS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$;
	
$(OUTPUT):$(OBJS)
	$(AR) $@ $(OBJS)
	
#**********************************************************
#	common rule
#**********************************************************

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) $(INCS) $<
	
clean:
	rm -f $(OBJS) $(OUTPUT) *.d
