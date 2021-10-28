#pragma once
#include "Connection.h"

namespace uqac {

	class TCPConnection : public Connection {
	public:
		TCPConnection(std::string addr, std::string port);
		TCPConnection(int socket);
		~TCPConnection() = default;

		void sendMessage(const std::string message);
		int receiveMessage(char* recvbuf);
		int receiveMessage(char* recvbuf, struct sockaddr_in* addrBuff);
	};

}