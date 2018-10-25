#include "MyMath.h"
#include <iostream>
using namespace std;

int main(int argc, char* argv[])
{
	double a = 10;
	double b = 2;

	std::cout << "a + b = " << MyMath::add(a, b) << std::endl;
	std::cout << "a - b = " << MyMath::sub(a, b) << std::endl;
	std::cout << "a * b = " << MyMath::mul(a, b) << std::endl;
	std::cout << "a / b = " << MyMath::div(a, b) << std::endl;

	return 0;
}

//1.动态库编译链接：
// $ g++ -o demo MyMathDemo.cpp -lmymath -ldl
// $ g++ -Wall -O2 MyMathDemo.cpp -lmymath -ldl -o demo
//
// $ g++ -o demo MyMathDemo.cpp -L. -lmymath -ldl -Wl, -rpath=.
// $ g++ -Wall -O2 MyMathDemo.cpp -o demo -L. -lmymath -ldl //-L.表示.so在当前目录
//[注意]:
//在项目开发过层中尽量让lib是垂直关系，避免循环依赖；越是底层的库，越是往后面写！
//如:
//g++ ...  obj($ ? ) - l(上层逻辑lib) - l(中间封装lib) - l(基础lib) - l(系统lib) - o $@