#include "gen-cpp/YiService.h"
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <boost/shared_ptr.hpp>
#include <iostream>

using namespace std;

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace yisrv;

int main(int argc, char *argv[]) {
	boost::shared_ptr<TSocket> socket(new TSocket("localhost", 9090));
	boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
	boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

	time_t mytime = 0;
	try
	{
		YiServiceClient client(protocol);
		transport->open();
		mytime = client.GetServerTime();

		cout << "Now is " << ctime(&mytime) << endl;
		transport->close();
	}
	catch (TException &tx)
	{
		printf("ERROR: %s\n", tx.what());
	}

	return 0;
}

//编译
// $ g++ -o ../../bin/thrift_client *.cpp gen-cpp/YiService_constants.cpp gen-cpp/YiService.cpp gen-cpp/YiService_types.cpp -lthrift -ldl