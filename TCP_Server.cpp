#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "Usage: Port " << endl;
        exit(0);
    }

    int port = atoi(argv[1]);

    int serverSd = socket(AF_INET, SOCK_STREAM, 0);

    if (serverSd < 0)
    {
        cerr << "Can't initialize socket!" << endl;
        exit(0);
    }
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int bindStatus = bind(serverSd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

    if (bindStatus < 0)
    {
        cerr << "Can't binding socket to local address!" << endl;
        exit(0);
    }

    listen(serverSd, 5);

    sockaddr_in newSocketAddr;
    socklen_t newSocketSize = sizeof(newSocketAddr);

    char buffer[500];
    string data;
    pid_t childpid;
    int newSd;

    while (true)
    {
        newSd = accept(serverSd, (sockaddr *)&newSocketAddr, &newSocketSize);

        if (newSd < 0)
        {
            cerr << "Can't accepting the request from client!" << endl;
            exit(0);
        }

        cout << "Connection accepted from " << inet_ntoa(newSocketAddr.sin_addr) << " " << ntohs(newSocketAddr.sin_port) << endl;

        if((childpid = fork()) == 0)
        {
            close(serverSd);

            while(true)
            {
                recv(newSd, (char*)buffer, sizeof(buffer), 0);

                if(!strcmp(buffer, "exit"))
                {
                    cout << "\nClient has quit the session" << endl;
                    break;
                }

                cout << "Client: " << buffer << endl;

                data = "Your message has been received!";
                memset(&buffer, 0, sizeof(buffer));
                strcpy(buffer, data.c_str());

                // Send message to client
                send(newSd, (char*)buffer, strlen(buffer), 0);   
                memset(&buffer, 0, sizeof(buffer));
            }
        } 
    }

    close(newSd);
    cout << "Connection has been closed!" << endl;
    return 0;
}