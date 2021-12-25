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
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std;

int Calculate(int &num1, int &num2, char &expression)
{
    cout << "Calculating..." << endl;
    cout << "expression: " << expression << endl;
    switch (expression)
    {
    case '1':
        return num1 + num2;
    case '2':
        return num1 - num2;
    case '3':
        return num1 * num2;
    case '4':
        return num1 / num2;
    default:
        return 0;
    }
}

int main()
{
    int num1, num2, result;
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
    cout << "Client: Connected" << endl;
    sendto(Socket, "Hello Client", sizeof("Hello Client"), 0, (sockaddr *)&ClientAddress, sizeof(ClientAddress));
    sendto(Socket, "Enter Number 1", sizeof("Enter Number 1"), 0, (sockaddr *)&ClientAddress, sizeof(ClientAddress));

    memset(Buffer, 0, sizeof(Buffer));
    recvfrom(Socket, Buffer, sizeof(Buffer), 0, (sockaddr *)&ClientAddress, &sizeofClientAddress);
    num1 = atoi(Buffer);
    cout << "Number 1: " << num1 << endl;
    memset(Buffer, 0, sizeof(Buffer));
    sendto(Socket, "Enter Number 2", sizeof("Enter Number 2"), 0, (sockaddr *)&ClientAddress, sizeof(ClientAddress));

    recvfrom(Socket, Buffer, sizeof(Buffer), 0, (sockaddr *)&ClientAddress, &sizeofClientAddress);
    num2 = atoi(Buffer);
    cout << "Number 2: " << num2 << endl;

    memset(Buffer, 0, sizeof(Buffer));
    // receive expression
    recvfrom(Socket, Buffer, sizeof(Buffer), 0, (sockaddr *)&ClientAddress, &sizeofClientAddress);
    result = Calculate(num1, num2, Buffer[0]);
    cout << "Result: " << result << endl;
    sendto(Socket, to_string(result).c_str(), sizeof(result), 0, (sockaddr *)&ClientAddress, sizeof(ClientAddress));
    return 0;
}