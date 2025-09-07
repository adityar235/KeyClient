#ifndef REDIS_CLIENT_H      
#define REDIS_CLIENT_H

#include <string>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>     // for socket, connect, and socket releted contants
#include <unistd.h>         // for close
#include <cstring>          // for memset

class RedisClient{
public:
    RedisClient(const std::string &host, int port); 
    ~RedisClient();                                   
    
    bool connectToServer();          
    void disconnect();               
    int getSocketFD() const;
    bool sendCommand(const std::string &command);
    
private:
    std::string host;      
    int port;              
    int sockfd;            

};


#endif   //REDIS_CLIENT_H