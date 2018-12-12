DEMO_DIR = demo
SHARE_LIBRARY_DIR = share_library
STATIC_LIBTARY_DIR = static_library

THREAD_FLAG = -j2

all:
	cd $(STATIC_LIBTARY_DIR); $(MAKE) $(THREAD_FLAG)
	cd $(SHARE_LIBRARY_DIR); $(MAKE) $(THREAD_FLAG)
	cd $(DEMO_DIR); $(MAKE) $(THREAD_FLAG)

clean:
	cd $(DEMO_DIR); $(MAKE) clean
	cd $(SHARE_LIBRARY_DIR); $(MAKE) clean
	cd $(STATIC_LIBTARY_DIR); $(MAKE) clean