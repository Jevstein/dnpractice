#**********************************************************
#
# by jevstein
# 2018/12/14
#
# DEBUG	: DEBUG can be set to YES to include debug info, or NO otherwise(RELEASE)
#		  you can also use like this: make DEBUG:=NO
#**********************************************************

# 1.config
dirs = static_library share_library demo

# 2.TOOL CHAIN OR PARAMETERS
THREADS_FLAG = #-j2

# 3.OUTPUT
all:
	@for dir in $(dirs); \
	do \
		cd $$dir; $(MAKE) $(THREADS_FLAG); cd -;\
	done

clean:
	@for dir in $(dirs); \
	do \
		cd $$dir; $(MAKE) clean; cd -;\
	done

cleanall:
	@for dir in $(dirs); \
	do \
		cd $$dir; $(MAKE) cleanall; cd -;\
	done

# 4.PHONY
.PHONY: all clean cleanall