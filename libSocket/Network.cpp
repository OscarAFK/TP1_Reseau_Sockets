#include "Network.h"

namespace uqac {

	Network::Network(std::string protocole) : m_quit(false), m_protocole(protocole)
	{}

	Network::~Network()
	{
	}

	void Network::Listen(std::function<void(Connection*)> onConnect, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect)
	{
	}

	void Network::broadcast(const std::string message)
	{
		for (std::vector<Connection*>::iterator it = m_connections.begin(); it != m_connections.end(); it++) {
			(*it)->sendMessage(message);
		}
	}

	void Network::broadcast(const std::string message, const Connection* origin)
	{
		for (std::vector<Connection*>::iterator it = m_connections.begin(); it != m_connections.end(); it++) {
			if ((*it) != origin) (*it)->sendMessage(message);
		}
	}

	int Network::Update(std::function<void(Connection*)> onConnect, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect)
	{
		while (!m_quit) {
			Listen(onConnect, onRecv, onDisconnect);
		}
		return 0;
	}

	void Network::Quit()
	{
		m_quit = true;
	}

}