#pragma once
#define WIN32_LEAN_AND_MEAN

#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <atomic>

#include "Connection.h"
#include "Terminal.h"
#include "Network.h"
#include <thread>
#include <functional>

namespace uqac {

    class Network
    {
    protected:

        Terminal* m_terminal;
        std::vector<Connection*>    m_connections;
        //std::thread m_threadNetwork;
        std::atomic<bool> m_quit;
        std::string m_protocole;

    public:

        Network(std::string protocole);       // Constructeur
        ~Network();      // Destructeur

        virtual void Listen(std::function<void(Connection*)> onConnect, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect) = 0;
        void broadcast(const std::string message);
        void broadcast(const std::string message, const Connection* origin);
        int Update(std::function<void(Connection*)> onConnect, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect);
        void Quit();

    };

}