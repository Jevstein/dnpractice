#include "StaticMath.h"

const char *LIB_INFO = "libStaticLibrary version: 0.0.1 (" __DATE__ "," __TIME__ ")";

CStaticMath::CStaticMath(void)
{
}

CStaticMath::~CStaticMath(void)
{
}

double CStaticMath::add(double a, double b)
{
	return a + b;
}

double CStaticMath::sub(double a, double b)
{
	return a - b;
}

double CStaticMath::mul(double a, double b)
{
	return a * b;
}

double CStaticMath::div(double a, double b)
{
	return (b == 0) ? 0 : (a / b);
}
