#include <stdio.h>
#include "StaticMath.h"
#include "IFactory.h"

/* dlopen + dlsym + dlclose */
#include <dlfcn.h>

#define LOG_DBG(fmt,...) printf(fmt"\n", ##__VA_ARGS__)
#define LOG_ERR(fmt,...) printf(fmt" ["__FILE__":%s().%d]\n", ##__VA_ARGS__, __FUNCTION__, __LINE__)

class LibTestCase
{
public:
	LibTestCase(){}

public:
	double do_static(double a, double b)
	{
		CStaticMath math;
		LOG_DBG("%lf + %lf = %lf", a, b, math.add(a, b));
		LOG_DBG("%lf - %lf = %lf", a, b, math.sub(a, b));
		LOG_DBG("%lf * %lf = %lf", a, b, math.mul(a, b));
		LOG_DBG("%lf / %lf = %lf", a, b, math.div(a, b));

		return math.add(a, b);
	}

	double do_dynamic(double a, double b)
	{
#if 0//windows
#define DYNLIB_HANDLE HINSTANCE
#define DYNLIB_LOAD( a ) LoadLibrary( a )
#define DYNLIB_GETSYM( a, b ) GetProcAddress( a, b )
#define DYNLIB_UNLOAD( a ) (bool)!FreeLibrary( a )
#else
#define DYNLIB_HANDLE void*
#define DYNLIB_LOAD( a ) dlopen( a, RTLD_NOW )
#define DYNLIB_GETSYM( a, b ) dlsym( a, b )
#define DYNLIB_UNLOAD( a ) dlclose( a )
//#define P_EXPORT_DLL
#endif

		double ret = 0.0f;

		// 1.dlopen .so
		LOG_DBG("1.dlopen '.so' ...");
		
		DYNLIB_HANDLE pHandler = DYNLIB_LOAD("../lib/libDynamicLibrary.so");//相对于exe的路径
		if (pHandler == 0)
		{
			LOG_ERR("Error::The pointer pHandler is null!\n errorcode: %s", dlerror());
			return ret;
		}

		// 2.find the exported function, and do something
		LOG_DBG("2.find the exported function, and do something ...");
		{
			// 2.1.find the function named create_factory
			LOG_DBG("  2.1.find the function named create_factory ...");
			typedef	IFactory* (*PFNCreateFactory)();
			PFNCreateFactory create_factory = (PFNCreateFactory)DYNLIB_GETSYM(pHandler, "create_factory");
			if (!create_factory)
			{
				LOG_ERR("Error::The pointer pfn is null!\n errorcode: %s", dlerror());
				LOG_DBG("Prompt::see shell command of linux about export functions in .so file. e.g：nm -D *.so; nm *.so; objdump -tT 7z.so");
				return ret;
			}
			IFactory* pFactory = create_factory();
			if (!pFactory)
			{
				LOG_ERR("Error::Failed to create_factory");
				return ret;
			}
			
			// 2.2.do math
			LOG_DBG("  2.2.control math object ...");
			IMath *pMath = (IMath*)pFactory->create_math();
			if (pMath)
			{
				// 2.2.1.do math
				LOG_DBG("    2.2.1.do math ...");

				LOG_DBG("		%lf + %lf = %lf", a, b, pMath->add(a, b));
				LOG_DBG("		%lf - %lf = %lf", a, b, pMath->sub(a, b));
				LOG_DBG("		%lf * %lf = %lf", a, b, pMath->mul(a, b));
				LOG_DBG("		%lf / %lf = %lf", a, b, pMath->div(a, b));

				ret = pMath->add(a, b);

				// 2.2.2. destroy math
				LOG_DBG("    2.2.2.destroy math!");
				pFactory->destroy_math(pMath);
			}
			else
			{
				LOG_ERR("Error::Failed to create_math!");
			}

			// 2.3.destroy_factory
			LOG_DBG("  2.3.call destroy_factory!");
			typedef	void* (*PFNDestroyFactory)(IFactory* factory);
			PFNDestroyFactory destroy_factory = (PFNDestroyFactory)DYNLIB_GETSYM(pHandler, "destroy_factory");
			destroy_factory(pFactory);
		}

		// 3.dlclose
		LOG_DBG("3.dlclose...");
		DYNLIB_UNLOAD(pHandler);

		// 4.dlclose
		LOG_DBG("4.the end!");

		return ret;
	}
};

int main()
{
	double a = 100.0;
	double b = 200.0;
	LibTestCase ts;

	// 1.静态库测试
	LOG_DBG("--- static library ---");
	ts.do_static(a, b);

	LOG_DBG("");

	// 2.动态库测试
	LOG_DBG("--- dynamic library---");
	ts.do_dynamic(a, b);

    // FILE* file = fopen("t.txt","w+");
    // if (file == NULL)
    // {
    //     return 0;
    // }

    // char buf[20]="hello world!!!\n";
    // int len = strlen(buf);

    // while(1)
    // {
    //     fputs(buf,file);
    //     fflush(file);
    // //  printf("%s",buf);
    //     sleep(1);
    // }

    // fclose(file);

    return 0;
}
