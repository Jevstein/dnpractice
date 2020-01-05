#include<iostream>
#include<boost/lexical_cast.hpp>
int main()
{
	int a = boost::lexical_cast<int>("123456");
	std::cout << "boost installed successfully! boost::lexical_cast: " << a << std::endl;
	return 0;
}

/***
运行命令:
   #  g++ demo-boost.cpp -o demo-boost
   #  ./demo-boost
*/
