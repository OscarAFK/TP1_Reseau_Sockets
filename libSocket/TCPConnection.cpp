#include "TCPConnection.h"

namespace uqac {

    TCPConnection::TCPConnection(std::string addr, std::string port) : Connection("TCP", addr, port)
    {
        // Attempt to connect to an address until one succeeds
        for (m_ptr = m_result; m_ptr != NULL; m_ptr = m_ptr->ai_next) {

            //Create a SOCKET for connecting to the server
            m_ConnectSocket = socket(m_ptr->ai_family, m_ptr->ai_socktype,
                m_ptr->ai_protocol);
            if (m_ConnectSocket == INVALID_SOCKET) {
                if (verbose) std::cout << "ConnectionToServer: socket failed with error: " << m_iResult << std::endl;
                WSACleanup();
                return;
            }

            // Connect to server.
            m_iResult = connect(m_ConnectSocket, m_ptr->ai_addr, (int)m_ptr->ai_addrlen);
            if (m_iResult == SOCKET_ERROR) {
                closesocket(m_ConnectSocket);
                m_ConnectSocket = INVALID_SOCKET;
                continue;
            }
            break;
        }
        u_long nonBlocking = 1;
        ioctlsocket(m_ConnectSocket, FIONBIO, &nonBlocking);
    }

    TCPConnection::TCPConnection(int socket) : Connection(socket)
    {
    }

    void TCPConnection::sendMessage(const std::string message)
    {
        m_iResult = send(m_ConnectSocket, message.c_str(), (int)strlen(message.c_str()) + 1, 0);
        if (m_iResult == SOCKET_ERROR) {
            if (verbose) std::cout << "send failed with error: " << WSAGetLastError() << std::endl;
            WSACleanup();
        }
        if (verbose) std::cout << "Bytes sent: " << m_iResult << std::endl;
    }

    int TCPConnection::receiveMessage(char* recvbuf)
    {
        m_iResult = recv(m_ConnectSocket, recvbuf, (int)strlen(recvbuf) + 1, 0);
        if (m_iResult > 0) {
            if (verbose) std::cout << "Bytes received: " << m_iResult << std::endl;
        }
        else if (m_iResult == 0) {
            if (verbose) std::cout << "Connection closed\n";
        }
        else
            if (verbose) std::cout << "recv failed with error: " << WSAGetLastError() << std::endl;
        return m_iResult;
    }

    int TCPConnection::receiveMessage(char* recvbuf, sockaddr_in* addrBuff)
    {
        return 0;
    }

}