
/*
Establishing a TCP Connection to Redis (RedisClient)
    Uses Berkeley sockets to open a TCP connection to the Redis server.
    Supports IPv4 and IPv6 resolution using getaddrinfo.
    Implements:
    connectToServer() → Establishes the connection.
    sendCommand() → Sends a command over the socket.
    disconnect() → Closes the socket when finished.
*/





#include "RedisClient.h"

RedisClient::RedisClient(const std::string &host, int port) 
    : host(host), port(port), sockfd(-1) {}



RedisClient::~RedisClient(){
    disconnect();
}

bool RedisClient::connectToServer(){
    struct addrinfo hints, *res = nullptr;
    std::memset(&hints,0, sizeof(hints));   //clear the hints structure using memset
    hints.ai_family = AF_UNSPEC;        //allow IPv4 OR IPv6
    hints.ai_socktype = SOCK_STREAM;   // for TCP defining

    std::string portStr = std::to_string(port);   // converting port no. integer to string

    int err = getaddrinfo(host.c_str(), portStr.c_str(), &hints, &res);  //resolve address
    if(err != 0)
    {
        std::cerr <<"getaddrinfo: "<< gai_strerror(err)<<"\n";    //print the error message
        return false;    // return false on failure
    }
    
    //iterate through the resolved addresses
    for(auto p = res; p!= nullptr; p = p->ai_next)
    {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);   //create the socket

        if(sockfd == -1)   // -1 for error    // and skip if socket creation failed
        continue;

        if(connect(sockfd, p->ai_addr, p->ai_addrlen) == 0)    //attempt to connect
        {
            break;                //break if there is successful connection
        } 

        close(sockfd);          // close socket if connection failed
        sockfd = -1;            //reset socket file descriptor

    }
    freeaddrinfo(res);          //free the address information

    if(sockfd == -1)
    {
        std::cerr << "could not connect to " << host << ":" << port << "\n";      //print failure message
        return false;
    }
    return true;           //return true on successful connection

}


void RedisClient::disconnect()
{
    if(sockfd != -1)
    close(sockfd);            //close socket if connection failed
    sockfd = -1;              //reset socket file descriptor
}

