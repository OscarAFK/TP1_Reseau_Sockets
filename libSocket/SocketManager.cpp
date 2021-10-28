#include "SocketManager.h"

namespace uqac {

    SocketManager::SocketManager(std::string protocole, std::string addr, std::string port) : verbose(true), m_addr(addr), m_port(port)
    {
        // Initialize Winsock
        WSADATA wsaData;
        m_iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
        if (m_iResult != 0) {
            if (verbose) std::cout << "WSAStartup failed with error: " << m_iResult << std::endl;
            return;
        }

        if (port.empty())
            port = DEFAULT_PORT;

        if (addr.empty())
            addr = "localhost";

        if (protocole.empty())
            protocole = "TCP";


        ZeroMemory(&m_hints, sizeof(m_hints));
        m_hints.ai_family = AF_INET;
        if (protocole == "TCP") {
            m_hints.ai_socktype = SOCK_STREAM;
            m_hints.ai_protocol = IPPROTO_TCP;
        }
        else if (protocole == "UDP") {
            m_hints.ai_socktype = SOCK_DGRAM;
            m_hints.ai_protocol = IPPROTO_UDP;
        }
        else {
            if (verbose) std::cout << "Protocole not recognized! Protocole provided: " << protocole << std::endl;
            return;
        }

        m_hints.ai_flags = AI_PASSIVE;

        m_iResult = getaddrinfo(addr.c_str(), port.c_str(), &m_hints, &m_result);
        if (m_iResult != 0) {
            if (verbose) std::cout << "getaddrinfo failed with error: " << m_iResult << std::endl;
            WSACleanup();
            return;
        }
    }

    SocketManager::SocketManager(int socket) : verbose(true)
    {
        m_ConnectSocket = socket;
        u_long nonBlocking = 1;
        ioctlsocket(m_ConnectSocket, FIONBIO, &nonBlocking);
    }

    SocketManager::~SocketManager()
    {
        if (m_ConnectSocket != INVALID_SOCKET) {
            m_iResult = shutdown(m_ConnectSocket, SD_SEND);
            if (verbose && m_iResult == SOCKET_ERROR) {
                std::cout << "Connection: shutdown failed with error: " << WSAGetLastError() << std::endl;
            }
        }
        closesocket(m_ConnectSocket);
        WSACleanup();
    }


    int SocketManager::getSocket()
    {
        return m_ConnectSocket;
    }

    void SocketManager::getName(char* buffAddr, char* buffPort)
    {
        struct sockaddr_in _buffAddr;
        int* namelen;
        getsockname(m_ConnectSocket, (struct sockaddr*)&_buffAddr, namelen);
        buffAddr = inet_ntoa(_buffAddr.sin_addr);
        buffPort = (char*)std::to_string(_buffAddr.sin_port).c_str();
    }


    void SocketManager::Update()
    {
    }

}