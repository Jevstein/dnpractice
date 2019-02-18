#ifndef _YI_DYNAMICMATH_H_
#define _YI_DYNAMICMATH_H_
#include "IFactory.h"

class CDynamicMath : public IMath
{
public:
	CDynamicMath(void);
	~CDynamicMath(void);

	virtual double add(double a, double b);//加法
	virtual double sub(double a, double b);//减法
	virtual double mul(double a, double b);//乘法
	virtual double div(double a, double b);//除法
};

#endif//_YI_DYNAMICMATH_H_