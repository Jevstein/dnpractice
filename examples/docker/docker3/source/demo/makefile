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
OUTPUT	:= $(HOME)/bin/demo
DEFS	:= 
INCS	:= -I$(HOME)/include\
		   #-I../../libs/libghttp-1.0.9
LIBS	:= -ldl -lpthread\
           -L$(HOME)/lib/ -lStaticLibrary

#**********************************************************
#CXX		:= colorgcc /usr/bin/g++
CXX		:= g++
LD		:= g++
AR		:= ar rcs
RANLIB	:= ranlib

DEBUG_CXXFLAGS		:= -Wall -g -DDEBUG
RELEASE_CXXFLAGS	:= -Wall -O3 -DNDEBUG

DEBUG_LDFLAGS		:= -g
RELEASE_LDFLAGS		:=

ifeq (YES, $(DEBUG))
	CXXFLAGS		:= $(DEBUG_CXXFLAGS) $(INCS)
	LDFLLAGS		:= $(DEBUG_LDFLAGS) $(INCS)
else
	CXXFLAGS		:= $(RELEASE_CXXFLAGS) $(INCS)
	LDFLLAGS		:= $(RELEASE_CSSFLAGS) $(INCS)
endif

all:$(OUTPUT)

SRCS	:= $(wildcard *.cpp)

OBJS	:= $(addsuffix .o, $(basename $(SRCS)))

DEPS	:= $(addsuffix .d, $(basename $(SRCS)))
#**********************************************************
#	OUTPUT
#**********************************************************

$(OUTPUT):$(OBJS)
	$(LD) -o $@ $(CXXFLAGS) $(OBJS) $(LIBS)
	#$(AR) $@ $(OBJS)
	
#**********************************************************
#	common rule
#**********************************************************
include $(subst .cpp,.d,$(SRCS))

%.d : %.cpp
	$(CXX) -M $(CPPFLAGS) $(INCS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$;

%.o : %.cpp
	$(CXX) -c -o $@ $(CXXFLAGS) $(INCS) $<

clean:
	rm -f $(OBJS) $(OUTPUT) $(DEPS) *.d
