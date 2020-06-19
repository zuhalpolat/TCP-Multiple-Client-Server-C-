
USAGE

TCP_Server.cpp:

```cpp
{
    ./server 5058
    Connection accepted from 127.0.0.1 53986
    Connection accepted from 127.0.0.1 53988
    Connection accepted from 127.0.0.1 53990
    Client: Merhaba
    Client: I am second client
    Client: I am third client

    Client has quit the session
    Cannot accepting the request from client!

    Client has quit the session
    Cannott accepting the request from client!

    Client has quit the session
    Cannott accepting the request from client!

}
```

TCP_Client.cpp:

Client1:
```cpp
{
    ./client 127.0.0.1 5058
    >> Merhaba
    Server: Your message has been received!
    >> exit

    Connection has been closed!
}
```

Client2:
```cpp
{
    ./client 127.0.0.1 5058
    >> I am second client
    Server: Your message has been received!
    >> exit

    Connection has been closed!
}
```

Client3:
```cpp
{
    ./client 127.0.0.1 5058
    >> I am third client
    Server: Your message has been received!
    >> exit

    Connection has been closed!
}
```