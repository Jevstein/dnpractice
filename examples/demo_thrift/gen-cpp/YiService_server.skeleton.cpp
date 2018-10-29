// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "YiService.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using namespace ::yisrv;

class YiServiceHandler : virtual public YiServiceIf {
 public:
  YiServiceHandler() {
    // Your initialization goes here
  }

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

};

int main(int argc, char **argv) {
  int port = 9090;
  ::apache::thrift::stdcxx::shared_ptr<YiServiceHandler> handler(new YiServiceHandler());
  ::apache::thrift::stdcxx::shared_ptr<TProcessor> processor(new YiServiceProcessor(handler));
  ::apache::thrift::stdcxx::shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  ::apache::thrift::stdcxx::shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  ::apache::thrift::stdcxx::shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

//complie:
// $ g++ -o ../../bin/thrift_server *.cpp *.h -lthrift -lthriftnb -ldl -std=c++11