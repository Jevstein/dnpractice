/*
 *  MyMath.cpp 
 *  MyMath
 *
 *  Created by Jevstein on 2018/10/16 17:11.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 */
#include <iostream>
#include "MyMath.h"

MyMath::MyMath(void)
{
}

MyMath::~MyMath(void)
{
}

double MyMath::add(double a, double b)
{
	return a + b;
}

double MyMath::sub(double a, double b)
{
	return a - b;
}

double MyMath::mul(double a, double b)
{
	return a * b;
}

double MyMath::div(double a, double b)
{
	if (b == 0.0f)
		return 0;

	return a / b;
}

//1.静态库编译：
// $ g++ -c MyMath.cpp
// $ ar -crv libmymath.a MyMath.o
//
//2.动态库编译：
// $ g++ -fPIC -shared -o libmymath.so MyMath.cpp