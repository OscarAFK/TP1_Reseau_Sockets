#pragma once

#include <stdlib.h>
#include <stdio.h>

#include "SocketManager.h"

namespace uqac {

	// via elle que nous envoyons et recevons nos messages
	class Connection : public SocketManager {

	public:
		virtual void sendMessage(const std::string message) = 0;
		virtual int receiveMessage(char* recvbuf) = 0;
		virtual int receiveMessage(char* recvbuf, struct sockaddr_in* addrBuff) = 0;

		Connection(std::string protocol, std::string addr, std::string port);
		Connection(int socket);
		Connection() = default;
		~Connection();



	};

}