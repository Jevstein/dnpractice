/*
 *  iniconfig.cpp 
 *  iniconfig
 *
 *  Created by Jevstein on 2018/10/30 14:19.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  参考: https://github.com/ndevilla/iniparser
 */

#include <stdio.h>
#include <string.h>
#include "iniconfig.h"

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage: iniconfig [ conf.ini ]\n");
		return -1;
	}

	Iniconfig config;
	if (!config.loadfile(std::string(argv[1])))
	{
		printf("failed to load '%s'!\n", argv[1]);
		return -1;
	}

	st_env_config conf_args = config.getconfig();
	printf("db_ip=%s, port=%d, db_user=%s, db_pwd=%s, db_name=%s\n"
		, conf_args.db_ip.c_str(), conf_args.db_port, conf_args.db_user.c_str(), conf_args.db_pwd.c_str(), conf_args.db_name.c_str());
	printf("svr_port=%d\n", conf_args.svr_port);

	return 0;
}


//compile:
// $ g++ -g -o ../../bin/iniconfig ./iniparser/*.c *.cpp -I ./iniparser
//
//run:
// $ ./iniconfig ../examples/iniconfig/conf.ini