/*
 *  call_lua_demo.cpp 
 *  call_lua_demo
 *
 *  Created by Jevstein on 2018/10/16 11:30.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 */

#include <iostream>
#include <string>
using namespace std;

//0.包含lua头文件
extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}

void call_lua_test()
{
	//1.创建lua环境
	lua_State *L = luaL_newstate(); //lua_open()
	if (L == NULL)
	{
		std::cout << "[C++]: Failed to create Lua State!" << std::endl;
		return;
	}

	//2.加载库
	luaL_openlibs(L);//加载终端输出打印信息库，届时可看到lua的print信息

	//3.加载lua脚本
	const std::string script = "./scripts/test.lua";
	int ret = luaL_dofile(L, script.c_str());
	if (ret != 0)
	{
		std::cout << "[C++]: Lua doFile Error !" << std::endl;
		return;
	}

	//4.调用脚本内容: 变量、函数等
	//     为简化代码，以下可以对其封装，如：
	//  bool load_file(string str);		//加载文件
	//  string load_string(string str);	//读取string变量
	//  int load_integer(string str);	//读取int变量
	//  double load_double(string str);	//读取double变量
	//  bool load_boolean(string str);	//读取bool变量
	//  bool load_map(const char* name, const int number, string str[], double array_list[], int type = 0);	//读取map
	//  bool load_array(const char* name, int*& array);	//读取array
	{//4.1.无参函数
		std::cout << "[C++]: 1.Get variable !" << std::endl;

		lua_getglobal(L, "id");//变量名称
		if (lua_isnumber(L, -1))
		{
			int id = 0;
			std::cout << "[C++]: The result is id=" << (int)lua_tointeger(L, -1) << endl;
		}
	}
	{//4.2.无参函数
		std::cout << "[C++]: 2.Call ruler_func() !" << std::endl;
		lua_getglobal(L, "ruler_func");		//脚本函数名: ruler_func
		lua_pcall(L, 0, 0, 0);				//用保护模式调用lua函数：入参个数为0、出参个数为0、无自定义错误处理
	}
	{//4.3.有参函数
		int number1 = 100;
		int number2 = 200;
		printf("[C++]: 3.Call add_func(%d, %d)!\n", number1, number2);
		lua_getglobal(L, "add_func");		//脚本函数名: add_func
		lua_pushnumber(L, number1);			//参数1入参： 100
		lua_pushnumber(L, number2);			//参数2入参： 200
		lua_pcall(L, 2, 1, 0);				//函数有两个入参，一个出参，所以函数形式为add(a,b)

		//获得返回值: 单回值情况下调用完成后lua会把结果放到栈顶，多返回值时，按照规则存放
		if (lua_isnumber(L, -1) != 0)
		{
			std::cout << "[C++]: The result is :" << lua_tonumber(L, -1) << endl;
		}
	}

	//5.销毁lua环境
	lua_close(L);
}

int main()
{
	std::cout << "--------- sample: C++ call Lua --------- " << std::endl;
	call_lua_test();
	std::cout << "--------- the end --------- " << std::endl;

	return 0;
}

//编译:
//gcc -o demo *.cpp -llua -ldl -lm
//g++ -o demo *.cpp -llua -ldl
//g++ -Wall -O2 *.cpp -llua -ldl -o demo