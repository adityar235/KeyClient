
/*
Establishing a TCP Connection to Redis (RedisClient)
    Uses Berkeley sockets to open a TCP connection to the Redis server.
    Supports IPv4 and IPv6 resolution using getaddrinfo.
    Implements:
    connectToServer() → Establishes the connection.
    sendCommand() → Sends a command over the socket.
    disconnect() → Closes the socket when finished.
*/

/*
struct addrinfo {
    int              ai_flags;      // options
    int              ai_family;     // AF_INET (IPv4), AF_INET6 (IPv6), AF_UNSPEC (any)
    int              ai_socktype;   // SOCK_STREAM (TCP), SOCK_DGRAM (UDP)
    int              ai_protocol;   // Protocol (0 = auto)
    socklen_t        ai_addrlen;    // Length of ai_addr
    struct sockaddr *ai_addr;       // Pointer to actual socket address
    char            *ai_canonname;  // Canonical name of host
    struct addrinfo *ai_next;       // Next result (linked list)
};

*/



#include "RedisClient.h"        //include the class definition from the header 

RedisClient::RedisClient(const std::string &host, int port) 
    : host(host), port(port), sockfd(-1) {}        //It initializes the data members of the class before the upper constructor body executes.

// RedisClient::RedisClient(const std::string &h, int p) {
//     host = h;
//     port = p;
//     sockfd = -1;
// }


RedisClient::~RedisClient(){   //automatically disconnet when objet is destroyed
    disconnect();
}

bool RedisClient::connectToServer(){
    //hints → a struct instance    //res → a pointer to a struct (this will hold the result returned by getaddrinfo)
    struct addrinfo hints, *res = nullptr;   //addrinfo is a struct defined in POSIX (netdb.h), not something you wrote.
    //It is used by getaddrinfo() to describe network address information (like IP family, socket type, protocol, etc.).
    std::memset(&hints,0, sizeof(hints));   //clear the hints structure using memset
    //memset is a standard C function (from <cstring> / <string.h>) that fills a block of memory with a specific byte value.
    // ptr → starting address of the memory block
    // value → the byte value to set (converted to unsigned char)
    // num → number of bytes to set
    hints.ai_family = AF_UNSPEC;        //allow both IPv4 OR IPv6
    hints.ai_socktype = SOCK_STREAM;   // specify TCP socket

    std::string portStr = std::to_string(port);   // converting port no. integer to string as getaddrinfo want port as string

    int err = getaddrinfo(host.c_str(), portStr.c_str(), &hints, &res);  //resolve address

    if(err != 0)
    {
        std::cerr <<"getaddrinfo: "<< gai_strerror(err)<<"\n";    //print the human-redable error message
        return false;    // return false on failure
    }
    
    //iterate through the resolved addresses
    for(auto p = res; p!= nullptr; p = p->ai_next)
    {
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);   //create the socket

        if(sockfd == -1)   // -1 for error // if socket creation failed
        continue;           // move to the next address of the list

        if(connect(sockfd, p->ai_addr, p->ai_addrlen) == 0)    //attempt to connect return 0 on success
        {
            break;                //break if there is successful connection
        } 
        
        //if we get here connect() failded for this address
        close(sockfd);          // close the socket we just created
        sockfd = -1;            //reset socket file descriptor to invalid

    }

    freeaddrinfo(res);          //Free the memory allocated by `getaddrinfo` for the linked list.

    if(sockfd == -1)
    {
        std::cerr << "could not connect to " << host << ":" << port << "\n";      //print failure message
        return false;
    }
    return true;           //return true on successful connection

}


void RedisClient::disconnect()
{
    if(sockfd != -1)          //check if socket is actually open
    close(sockfd);            //close socket
    sockfd = -1;              //reset socket file descriptor
}




int RedisClient::getSocketFD() const {
    return sockfd;
}

bool RedisClient::sendCommand(const std::string &command)   //sending command to client khud ka hai
{
    if (sockfd == -1) return false;  // if server is not listening khud ka hai 
    ssize_t sent = send(sockfd, command.c_str(), command.size(), 0);
    return (sent == (ssize_t)command.size());
}