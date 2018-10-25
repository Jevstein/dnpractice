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

extern "C"
{
	#include <lua.h>
	#include <lauxlib.h>
	#include <lualib.h>
}


/************************************************************************/
/* global value                                                         */
/************************************************************************/
//pop interge
#define POP_VALUE_INT(L, key)\
({ \
	int ret = 0; \
	lua_getglobal(L, key); \
	if (lua_isnumber(L, -1)) { ret = (int)lua_tointeger(L, -1); lua_pop(L, 1); }\
	(ret);\
})
//pop string
#define POP_VALUE_STR(L, key)\
({ \
	std::string ret = ""; \
	lua_getglobal(L, key); \
	if (lua_isstring(L, -1)) { ret = (std::string)lua_tostring(L, -1); lua_pop(L, 1); }\
	(ret);\
})

/************************************************************************/
/* field value                                                          */
/************************************************************************/
//pop filed interge
#define POP_FIELD_INT(L, key)\
({ \
	int ret = 0; \
	lua_getfield(L, -1, key); \
	if (lua_isnumber(L, -1)) { ret = (int)lua_tointeger(L, -1); lua_pop(L, 1); }\
	(ret); \
})
//pop filed string
#define POP_FIELD_STR(L, key)\
({ \
	std::string ret = ""; \
	lua_getfield(L, -1, key); \
	if (lua_isstring(L, -1)) { ret = (std::string)lua_tostring(L, -1); lua_pop(L, 1); }\
	(ret); \
})

//数据库配置信息
struct st_db_conf
{
	std::string db_ip;
	unsigned int db_port;
	std::string db_user;
	std::string db_pwd;
	std::string db_name;
};

class LuaCfg
{
public:
	LuaCfg(){ init(); }
	~LuaCfg(){ uninit(); }

public:
	bool load_file(const char *script)
	{
		int ret = luaL_dofile(L_, script);
		if (LUA_OK != ret)
		{
			printf("Failed to load file: '%s', ret=%d! \n", script, ret);
			return false;
		}

		// -- database
		lua_getglobal(L_, "db_conf");
		db_conf_.db_ip = POP_FIELD_STR(L_, "db_ip");
		db_conf_.db_port = POP_FIELD_INT(L_, "db_port");
		db_conf_.db_user = POP_FIELD_STR(L_, "db_user");
		db_conf_.db_pwd = POP_FIELD_STR(L_, "db_pwd");
		db_conf_.db_name = POP_FIELD_STR(L_, "db_name");
		printf("db: '%s', %d, '%s', '%s', '%s'\n"
			, db_conf_.db_ip.c_str(), db_conf_.db_port, db_conf_.db_user.c_str(), db_conf_.db_pwd.c_str(), db_conf_.db_name.c_str());
		lua_pop(L_, 1);

		// -- server
		srv_port_ = POP_VALUE_INT(L_, "srv_port");
		//srv_port_ = POP_VALUE_(L_, int, "srv_port", 0);
		printf("server port: %d\n", srv_port_);

		return true;
	}

protected:
	bool init()
	{
		L_ = luaL_newstate();
		if (NULL == L_)
		{
			std::cout << "Failed to create Lua State!" << std::endl;
			return false;
		}

		luaL_openlibs(L_);

		return true;
	}

	void uninit()
	{
		lua_close(L_);
	}

public:
	st_db_conf db_conf_;
	unsigned int srv_port_;

private:
	lua_State *L_;
};

int main()
{
	LuaCfg cfg;
	if (cfg.load_file("./conf/cfg.lua"))
	{
		printf("db: '%s', %d, '%s', '%s', '%s' \n"
			, cfg.db_conf_.db_ip.c_str(), cfg.db_conf_.db_port, cfg.db_conf_.db_user.c_str(), cfg.db_conf_.db_pwd.c_str(), cfg.db_conf_.db_name.c_str());
		printf("server port: %d\n", cfg.srv_port_);
	}

	//string str1 = LOAD_VALUE("aaa");
	//printf("str1: %s\n", str1.c_str());

	//int a = SECOND_OF_YEAR(2003);
	//std::cout << a << std::endl;

	// -- db
	//std::string db_ip = parser.load_string("db_ip");
	//int db_port = parser.load_integer("db_port");
	//std::string  db_user = parser.load_string("db_user");
	//int db_pwd = parser.load_integer("db_pwd");
	//std::string db_name = parser.load_string("db_name");
	//printf("db: '%s', %d, '%s', %d, '%s' \n", db_ip.c_str(), db_port, db_user.c_str(), db_pwd, db_name.c_str());

	//// -- network
	//int net_port = parser.load_integer("srv_port");
	//printf("network: %d\n", net_port);

	return 0;
}

//编译:
//g++ -o job *.cpp -llua -ldl
//g++ -Wall -O2 *.cpp -llua -ldl -o job