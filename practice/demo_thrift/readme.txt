参考:http://blog.jobbole.com/107828/

编译步骤:
1.将.thrift生成开发语言接口，如:
  $ thrift --gen cpp YiService.thrift

2.服务器实现，见gen-cpp
	1).修改x.skeleton.cpp的实现，如：
		int32_t GetServerName() {
			// Your implementation goes here
			printf("GetServerName\n");
		}
		
		int32_t GetServerTime() {
			// Your implementation goes here
			time_t now_time = time(NULL);
			printf("now is %d\n", (int)now_time);
			return now_time;
		}
	2).编译生成server,如:
		$ g++ -o server *.cpp -lthrift -ldl -std=c++11
		$ g++ -o server *.cpp *.h -lthrift -lthriftnb -ldl -std=c++11
	   注意：一定要包含c++11
  
3.客户端手工实现，见YiClient.cpp，编译如:
    $ g++ -g -Ithrift -L -lm -pthread -lz -lrt -lssl gen-cpp/YiService.cpp gen-cpp/YiService_constants.cpp gen-cpp/YiService_types.cpp *.cpp -o client -lthrift
    $ g++ -o client gen-cpp/YiService.cpp gen-cpp/YiService_constants.cpp gen-cpp/YiService_types.cpp *.cpp -lthrift