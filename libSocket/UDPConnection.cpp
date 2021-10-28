#include "UDPConnection.h"

namespace uqac {

    UDPConnection::UDPConnection(std::string addr, std::string port) : Connection("UDP", addr, port)
    {

        //Create a SOCKET for connecting to the server
        m_ConnectSocket = socket(m_hints.ai_family, m_hints.ai_socktype,
            m_hints.ai_protocol);
        if (m_ConnectSocket == INVALID_SOCKET) {
            if (verbose) std::cout << "ConnectionToServer: socket failed with error: " << m_iResult << std::endl;
            WSACleanup();
            return;
        }

        u_long nonBlocking = 1;
        ioctlsocket(m_ConnectSocket, FIONBIO, &nonBlocking);

    }

    UDPConnection::UDPConnection(int socket) : Connection(socket)
    {
    }

    void UDPConnection::sendMessage(const std::string message)
    {
        if (sendto(m_ConnectSocket, message.c_str(), strlen(message.c_str()), 0, (struct sockaddr*)&m_result, sizeof(m_result)) == SOCKET_ERROR)
        {
            if (verbose) std::cout << "sendto failed with error: " << WSAGetLastError() << std::endl;
        }
    }

    int UDPConnection::receiveMessage(char* recvbuf)
    {
        return 0;
    }

    int UDPConnection::receiveMessage(char* recvbuf, struct sockaddr_in* addrBuff)
    {
        int len = sizeof(addrBuff);
        m_iResult = recvfrom(m_ConnectSocket, recvbuf, (int)strlen(recvbuf) + 1, 0, (sockaddr*)addrBuff, &len);
        if (m_iResult == SOCKET_ERROR)
        {
            if (verbose) std::cout << "recvfrom failed with error: " << WSAGetLastError() << std::endl;
        }
        return m_iResult;
    }

}