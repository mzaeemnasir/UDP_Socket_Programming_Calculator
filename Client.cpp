
// Client.cpp
// ---------------------
// Creating Socket
// Sending Data
// Accept Data
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

    struct sockaddr_in ServerAddress;
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(3000);
    ServerAddress.sin_addr.s_addr = INADDR_ANY;

    sendto(Socket, "Hello Server", sizeof("Hello Server"), 0, (sockaddr *)&ServerAddress, sizeof(ServerAddress));
    socklen_t sizeofServerAddress;
    recvfrom(Socket, Buffer, sizeof(Buffer), 0, (sockaddr *)&ServerAddress, &sizeofServerAddress);
    cout << "Connection Established " << Buffer << endl;
    return 0;
}