// UDP Socket Programming
// M Zaeem Nasir
// 19F 0355
// 5B

// Server.cpp
// ---------------------
// Creating Socket
// Binding Socket
// Listening for Client
// Accepting Client
// Sending Data
// Closing Socket
// ---------------------

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int main()
{
    int Socket = socket(AF_INET, SOCK_DGRAM, 0);
    char Buffer[1024] = {0};
    if (Socket < 0)
    {
        cout << "Error in creating socket" << endl;
        return -1;
    }
    else
    {
        cout << "Socket Created" << endl;
    }

    struct sockaddr_in ServerAddress, ClientAddress;
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(3000);
    ServerAddress.sin_addr.s_addr = INADDR_ANY;

    int Bind = bind(Socket, (sockaddr *)&ServerAddress, sizeof(ServerAddress));
    if (Bind < 0)
    {
        cout << "Error in binding socket" << endl;
        return -1;
    }
    else
    {
        cout << "Socket Bound" << endl;
    }
    memset(&ClientAddress, 0, sizeof(ClientAddress));
    socklen_t sizeofClientAddress = sizeof(ClientAddress);
    recvfrom(Socket, Buffer, sizeof(Buffer), 0, (sockaddr *)&ClientAddress, &sizeofClientAddress);
    cout << "Client: Connected" << Buffer << endl;
    sendto(Socket, "Hello Client", sizeof("Hello Client"), 0, (sockaddr *)&ClientAddress, sizeof(ClientAddress));

    return 0;
}