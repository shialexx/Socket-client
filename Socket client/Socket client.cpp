// MADE BY SHIALEX

#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

using namespace std;

int main() {

    // Initialize Winsock
    WSADATA wsaData;
    _SOCKET_ADDRESS_LIST socket_address_list;

    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);

    if (result != 0) {
        cout << "WSAStartup failed with error: " << result << endl;
        return 1;
    }

    // Create a socket for incoming connections
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        cout << "socket creation failed with error: " << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    }

    // Bind the socket to a local address and port
    sockaddr_in addr = { 0 };
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80); // Example port number
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    result = bind(sock, (sockaddr*)&addr, sizeof(addr));
    if (result == SOCKET_ERROR) {
        cout << "bind failed with error: " << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Listen for incoming connections
    result = listen(sock, SOMAXCONN);
    if (result == SOCKET_ERROR) {
        cout << "listen failed with error: " << WSAGetLastError() << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Set the socket to non-blocking mode
    u_long iMode = 1;
    result = ioctlsocket(sock, FIONBIO, &iMode);
    if (result != NO_ERROR) {
        cout << "ioctlsocket failed with error: " << result << endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // If our result not equal error...

    if (result == NO_ERROR)
    {
        cout << "Current address: " << socket_address_list.Address << endl;

        wsaData.iMaxSockets = sock;

        cout << "iMaxSockets: " << wsaData.iMaxSockets << endl << "Socket port: " << addr.sin_port << endl << "Socket family: " << addr.sin_family << endl;
    }


    // Accept incoming connections and receive data in non-blocking way
    while (true) {
        SOCKET clientSock = accept(sock, NULL, NULL);
        if (clientSock != INVALID_SOCKET) {
            char buffer[1024];
            int bytesReceived = recv(clientSock, buffer, sizeof(buffer), 0);
            if (bytesReceived > 0) {
                // Process incoming data here
            }
            closesocket(clientSock);
        }
    }

    // Clean up
    closesocket(sock);
    WSACleanup();

    return 0;
}