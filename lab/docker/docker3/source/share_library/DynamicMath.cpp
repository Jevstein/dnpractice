#include "DynamicMath.h"


CDynamicMath::CDynamicMath(void)
{
}

CDynamicMath::~CDynamicMath(void)
{
}

double CDynamicMath::add(double a, double b)
{
	return a + b;
}

double CDynamicMath::sub(double a, double b)
{
	return a - b;
}

double CDynamicMath::mul(double a, double b)
{
	return a * b;
}

double CDynamicMath::div(double a, double b)
{
	return (b == 0) ? 0 : (a / b);
}