/*
 *  log4cppdemo.cpp 
 *  log4cppdemo
 *
 *  Created by Jevstein on 2018/10/25 17:34.
 *  Copyright @ 2018year Jevstein. All rights reserved.
 *
 *  ²Î¿¼: https://github.com/zhiyong0804/server_develop_guide_book/blob/master/chapter11/11.2_log4cpp.md
 */
#include <stdio.h>
#include <iostream>
#include "logger.h"

int main(int argc, char *argv[])
{
	if (!Logger::instance()->init(std::string(argv[1])))
	{
		printf("error: init log module failed.\n");
		return -1;
	}

	LOG_INFO("%d: i am happy.", 1);
	LOG_DEBUG("%d: oh, you happy, we happy.", 2);
	LOG_ERROR("%d: please do not contact me.", 3);
	LOG_WARN("%d: i am very busy now.", 4);
	LOG_NOTICE("%d: oh, what happed?", 5);

	return 0;
}

//compile:
// $ g++ -o ../../bin/log4cppdemo *.cpp -llog4cpp -lpthread
//
//run:
// $ ./log4cppdemo ./practice/demo_log4cpp/log.conf