#include "client.h"

namespace uqac {

    Client::Client(std::string protocole, std::string addr, std::string port, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect) : Network(protocole)
    {
        if (protocole == "TCP")
            m_connections.push_back(new TCPConnection(addr, port));
        else if (protocole == "UDP")
            m_connections.push_back(new UDPConnection(addr, port));
        m_threadNetwork = std::thread(&Client::Update, this, [](Connection*) { true; }, onRecv, onDisconnect);
    }

    Client::~Client()
    {
        m_threadNetwork.join();
        std::cout << "Closing client\n";
    }

    void Client::Listen(std::function<void(Connection*)> onConnect, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect)
    {
        fd_set readingSet;
        FD_ZERO(&readingSet);

        if (!m_connections.empty())
            FD_SET(m_connections[0]->getSocket(), &readingSet);

        char recvBuffer[DEFAULT_BUFLEN];
        TIMEVAL tv = { 0,0 };

        int ret = select(0, &readingSet, nullptr, nullptr, &tv);
        if (ret > 0)
        {
            if (FD_ISSET(m_connections[0]->getSocket(), &readingSet)) {
                int i_Result = m_connections[0]->receiveMessage(recvBuffer);
                if (i_Result > 0) {
                    onRecv(m_connections[0], recvBuffer);
                }
                else {
                    if (WSAGetLastError() == 10054) {
                        onDisconnect(m_connections[0]);
                        m_connections.clear();
                        Quit();
                        return;
                    }
                }
            }
        }
    }
    bool Client::isServerUp()
    {
        return !m_connections.empty();
    }

}