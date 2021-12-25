
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
    cout << "Connection Established " << endl;

    memset(Buffer, 0, sizeof(Buffer));
    // receive number 1
    recvfrom(Socket, Buffer, sizeof(Buffer), 0, (sockaddr *)&ServerAddress, &sizeofServerAddress);
    cout << Buffer << endl;
    // sending num 1
    char num;
    cin >> num;
    sendto(Socket, &num, sizeof(num), 0, (sockaddr *)&ServerAddress, sizeof(ServerAddress));
    memset(Buffer, 0, sizeof(Buffer));
    // receive number 2
    recvfrom(Socket, Buffer, sizeof(Buffer), 0, (sockaddr *)&ServerAddress, &sizeofServerAddress);
    cout << Buffer << endl;
    // sending num 2
    cin >> num;
    sendto(Socket, &num, sizeof(num), 0, (sockaddr *)&ServerAddress, sizeof(ServerAddress));

    memset(Buffer, 0, sizeof(Buffer));
    // receive expression
    string s = "Please Enter Operation: \n1. Addition \n2. Subtraction \n3. Multiplication \n4. Division \n5. Exit";
    cout << s << endl;
    cin >> num;
    if (num == '5')
    {
        exit;
    }
    // sending expression
    sendto(Socket, &num, sizeof(num), 0, (sockaddr *)&ServerAddress, sizeof(ServerAddress));
    // recv Result
    cout << "Result: ";
    memset(Buffer, 0, sizeof(Buffer));
    recvfrom(Socket, Buffer, sizeof(Buffer), 0, (sockaddr *)&ServerAddress, &sizeofServerAddress);
    cout << Buffer << endl;

    return 0;
}