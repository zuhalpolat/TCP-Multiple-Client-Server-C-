#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

using namespace std;

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cerr << "Usage: IPAddress Port" << endl;
        exit(0);
    }

    char *serverIp = argv[1];
    int port = atoi(argv[2]);

    struct hostent* host = gethostbyname(serverIp);

    int clientSd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in sendSocketAddr;
    memset(&sendSocketAddr, 0, sizeof(sendSocketAddr));
    sendSocketAddr.sin_family = AF_INET;
    sendSocketAddr.sin_port = htons(port);
    sendSocketAddr.sin_addr.s_addr = inet_addr(inet_ntoa(*(struct in_addr*)*host->h_addr_list));

    int status = connect(clientSd, (sockaddr*)&sendSocketAddr, sizeof(sendSocketAddr));

    if(status < 0)
    {
        cerr << "Can't connect to socket!" << endl;
        exit(0);
    }

    char buffer[250];
    string data;

    while(true)
    {
        cout << ">> ";
        getline(cin, data);

        memset(&buffer, 0, 250);
        strcpy(buffer, data.c_str());

        send(clientSd, (char*)&buffer, 250, 0);
    
        if(data == "exit")
            break;

        memset(&buffer, 0, 250);
        recv(clientSd, (char*)&buffer, 250, 0);

        cout << "Server: " << buffer << endl;
    }

    close(clientSd);
    cout << "\nConnection has been closed!" << endl;
    return 0;
}