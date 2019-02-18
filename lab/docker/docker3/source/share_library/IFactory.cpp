#include <stdio.h>
#include "IFactory.h"
#include "DynamicMath.h"

const char *LIB_INFO = "libDynamicLibrary version: 0.0.1 (" __DATE__ "," __TIME__ ")";

//IFactory::~IFactory()
//{
//
//}

IMath* IFactory::create_math()
{
	return (new CDynamicMath());
}

void IFactory::destroy_math(IMath *math)
{
	if (math)
		delete math;
}

IFactory* create_factory()
{
	return (new IFactory());
}

void destroy_factory(IFactory* factory)
{
	if (factory)
		delete factory;
}
