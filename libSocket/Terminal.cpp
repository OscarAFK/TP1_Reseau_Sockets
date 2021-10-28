#include "Terminal.h"

namespace uqac {

    Terminal::Terminal(std::string protocole, std::string port) : SocketManager(protocole, "", port)
    {
        // Create a SOCKET for connecting to server
        m_ConnectSocket = socket(m_result->ai_family, m_result->ai_socktype, m_result->ai_protocol);
        if (m_ConnectSocket == INVALID_SOCKET) {
            if (verbose) std::cout << "InitServer: socket failed with error: " << WSAGetLastError() << std::endl;
            freeaddrinfo(m_result);
            WSACleanup();
            return;
        }

        // Setup the TCP listening socket
        m_iResult = bind(m_ConnectSocket, m_result->ai_addr, (int)m_result->ai_addrlen);
        if (m_iResult == SOCKET_ERROR) {
            if (verbose) std::cout << "bind failed with error: " << WSAGetLastError() << std::endl;
            freeaddrinfo(m_result);
            closesocket(m_ConnectSocket);
            WSACleanup();
            return;
        }
        freeaddrinfo(m_result);
        if (protocole == "TCP") {
            m_iResult = listen(m_ConnectSocket, SOMAXCONN);
            if (m_iResult == SOCKET_ERROR) {
                if (verbose) std::cout << "listen failed with error: " << WSAGetLastError() << std::endl;
                closesocket(m_ConnectSocket);
                WSACleanup();
                return;
            }
        }

        u_long nonBlocking = 1;
        ioctlsocket(m_ConnectSocket, FIONBIO, &nonBlocking);
    }

    int Terminal::Connect()
    {
        // Accept a client socket
        int ConnectSocket = accept(m_ConnectSocket, NULL, NULL);
        if (ConnectSocket == INVALID_SOCKET) {
            if (verbose) std::cout << "accept failed with error: " << WSAGetLastError() << std::endl;
            closesocket(m_ConnectSocket);
            WSACleanup();
        }
        if (verbose) std::cout << "Nouvelle connection!\n";
        return ConnectSocket;
    }

}