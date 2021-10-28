#pragma once
#include "Connection.h"

#include "SocketManager.h"

namespace uqac {

	// permet au serveur de cr�er une connexion lorsqu�il re�oit une
	// demande de connexion d�un client.
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