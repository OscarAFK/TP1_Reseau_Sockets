#pragma once

#include "UDPConnection.h"
#include "TCPConnection.h"
#include "Terminal.h"
#include "Network.h"
#include <thread>
#include <functional>

namespace uqac {

    class Server : public Network {

    public:


        Server() = default;       // Constructeur
        Server(std::string protocole, std::string port);       // Constructeur
        ~Server();      // Destructeur

        void Listen(std::function<void(Connection*)> onConnect, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect);


    };

}