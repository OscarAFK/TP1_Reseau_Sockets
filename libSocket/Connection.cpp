#include "Connection.h"

namespace uqac {

	Connection::Connection(std::string protocol, std::string addr, std::string port) : SocketManager(protocol, addr, port) {}

	Connection::Connection(int socket) : SocketManager(socket)
	{
	}

	Connection::~Connection()
	{
	}


}