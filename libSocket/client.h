#pragma once

#include "TCPConnection.h"
#include "UDPConnection.h"
#include <thread>
#include <functional>
#include "Network.h"

namespace uqac {

	class Client : public Network {
	public:

		Client() = default;		// constructeur
		Client(std::string protocole, std::string addr, std::string port, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect);		// constructeur
		~Client();		// destructeur

		void Listen(std::function<void(Connection*)> onConnect, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect);
		bool isServerUp();
	};

}