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
OUTPUT	:= $(HOME)/lib/libDynamicLibrary.so
DEFS	:= 
INCS	:= -I$(HOME)/include
LIBS	:= -ldl -lpthread

#**********************************************************

CXX		:= g++
LD		:= g++
AR		:= ar rc
RANLIB	:= ranlib

DEBUG_CXXFLAGS		:= -Wall -g -DDEBUG -Wno-deprecated
RELEASE_CXXFLAGS	:= -Wall -O3 -DNDEBUG

DEBUG_LDFLAGS		:= -g -fno-rtti -fno-exceptions
RELEASE_LDFLAGS		:=

ifeq (YES, $(DEBUG))
	CXXFLAGS		:= $(DEBUG_CXXFLAGS) $(DEFS)
	LDFLLAGS		:= $(DEBUG_LDFLAGS) $(DEFS)
else
	CXXFLAGS		:= $(RELEASE_CXXFLAGS) $(DEFS)
	LDFLLAGS		:= $(RELEASE_CSSFLAGS) $(DEFS)
endif

all:$(OUTPUT)

SRCS	:= $(wildcard *.cpp)

OBJS	:= $(addsuffix .o, $(basename $(SRCS)))

#**********************************************************
#	OUTPUT
#**********************************************************
include $(subst .cpp,.d,$(SRCS))

%.d : %.cpp
	$(CXX) -M $(CPPFLAGS) $(INCS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$;
	
$(OUTPUT):$(OBJS)
	$(LD) -o $@ -shared $(CXXFLAGS) $(OBJS) $(LIBS)
	
#**********************************************************
#	common rule
#**********************************************************

%.o : %.cpp
	$(CXX) -c -fPIC $(CXXFLAGS) $(INCS) $<

clean:
	rm -f $(OBJS) $(OUTPUT) *.d
