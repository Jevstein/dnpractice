/*
 *  MyLuaMath.cpp 
 *  MyLuaMath
 *
 *  Created by Jevstein on 2018/10/17 17:45.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 */

#include <iostream>
extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}
#include "MyLuaMath.h"

#define MY_EXPORTS

/************************************************************************/
/* 1.函数实现                                                           */
/************************************************************************/
int add_func(lua_State* L)
{
	//if (!lua_isnumber(state, 1))
	//	printf("type invalid!");

	int a = lua_tonumber(L, 1);
	int b = lua_tonumber(L, 2);
	int ret = a + b;

	lua_pushnumber(L, ret);
	return 1;//1个返回值
}

int sub_func(lua_State* L)
{
	int a = lua_tonumber(L, 1);
	int b = lua_tonumber(L, 2);
	int ret = a - b;

	lua_pushnumber(L, ret);
	return 1;
}

int mul_func(lua_State* L)
{
	int a = lua_tonumber(L, 1);
	int b = lua_tonumber(L, 2);
	int ret = a * b;

	lua_pushnumber(L, ret);
	return 1;
}

int div_func(lua_State* L)
{
	int a = lua_tonumber(L, 1);
	int b = lua_tonumber(L, 2);
	int ret = (b == 0) ? 0 : a / b;

	lua_pushnumber(L, ret);
	return 1;
}

/************************************************************************/
/* 2.函数数组                                                           */
/************************************************************************/
static const struct luaL_Reg funcs__[] =
{
	{ "add", add_func },
	{ "sub", sub_func },
	{ "mul", mul_func },
	{ "div", div_func },
	{ NULL, NULL }
};

/************************************************************************/
/* 3.导出接口                                                           */
/*   [注]函数名luaopen_libmyluamath中的'libmyluamath'必须为库函数名，如:*/
/*       libmyluamath.so                                                */
/************************************************************************/
MY_REPORT_API int CALLMODE luaopen_libmyluamath(lua_State* L)
{
	//lua5.1之前版本使用如下:
	//luaL_openlib(L, "MyMath", funcs__, 0); //或luaL_register(L, "mymath", funcs__);

	//lua5.2以上版本使用如下:
	lua_getglobal(L, "MyMath");
	if (lua_isnil(L, -1))
	{
		lua_pop(L, 1);
		lua_newtable(L);
	}
	luaL_setfuncs(L, funcs__, 0);
	lua_setglobal(L, "MyMath");

	return 0;
}

//编译:
// $ g++ -fPIC -shared -o libmyluamath.so *.cpp -llua -ldl -I /usr/include/lua5.2/
// $ g++ -fPIC -shared -o libmyluamath.so *.cpp -llua -ldl