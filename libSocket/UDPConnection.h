#pragma once
#include "Connection.h"

namespace uqac {

	class UDPConnection : public Connection {
	public:
		UDPConnection(std::string addr, std::string port);
		UDPConnection(int socket);
		~UDPConnection() = default;

		void sendMessage(const std::string message);
		virtual int receiveMessage(char* recvbuf);
		int receiveMessage(char* recvbuf, struct sockaddr_in* addrBuff);
	};

}