#include "server.h"

namespace uqac {

    Server::Server(std::string protocole, std::string port) : Network(protocole)
    {
        m_terminal = new Terminal(protocole, port);
        if (protocole == "UDP") {
            m_connections.push_back(new TCPConnection(m_terminal->getSocket()));
        }
        //m_threadNetwork = std::thread(&Server::Update, this, onConnect, onRecv, onDisconnect);
    }

    Server::~Server()
    {
        //m_threadNetwork.join();
        std::cout << "Closing server\n";
    }

    void Server::Listen(std::function<void(Connection*)> onConnect, std::function<void(Connection*, char*)> onRecv, std::function<void(Connection*)> onDisconnect)
    {
        fd_set readingSet;
        FD_ZERO(&readingSet);

        FD_SET(m_terminal->getSocket(), &readingSet);
        for (std::vector<Connection*>::iterator it = m_connections.begin(); it != m_connections.end(); it++) {
            FD_SET((*it)->getSocket(), &readingSet);
        }

        char recvBuffer[DEFAULT_BUFLEN];
        TIMEVAL tv = { 0,0 };

        int ret = select(0, &readingSet, nullptr, nullptr, &tv);
        if (ret > 0)
        {
            if (m_protocole == "TCP") {
                if (FD_ISSET(m_terminal->getSocket(), &readingSet)) {
                    m_connections.push_back(new TCPConnection(m_terminal->Connect()));
                    onConnect(m_connections.back());
                }
                for (std::vector<Connection*>::iterator it = m_connections.begin(); it != m_connections.end();) {
                    if (FD_ISSET((*it)->getSocket(), &readingSet)) {
                        int i_Result = (*it)->receiveMessage(recvBuffer);
                        if (i_Result > 0) {
                            onRecv((*it), recvBuffer);
                        }
                        else {
                            if (WSAGetLastError() == 10054) {
                                onDisconnect((*it));
                                it = m_connections.erase(it);
                                continue;
                            }
                        }
                    }
                    ++it;
                }
            }
        }
    }

}