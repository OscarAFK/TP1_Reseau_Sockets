#pragma once
#include "Connection.h"

#include "SocketManager.h"

namespace uqac {

	// permet au serveur de créer une connexion lorsqu’il reçoit une
	// demande de connexion d’un client.
	class Terminal : public SocketManager {

	private:

		int m_iResult;

	public:

		Terminal(std::string protocole, std::string port);
		Terminal() = default;
		~Terminal() = default;

		int Connect();
	};

}