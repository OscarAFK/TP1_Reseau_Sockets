#pragma once

#include "Terminal.h"
#include <vector>

class MotherClass {

private :
	Terminal m_terminal;

	class Server server;

	vector<class Client> clients;

public :

	void listen();		// Server
	void connect();		// Client

};