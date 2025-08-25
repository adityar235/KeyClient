#ifndef REDIS_CLIENT_H      //head file to prevent file from being included and compiled multiple times
#define REDIS_CLIENT_H

#include <string>
#include <iostream>
#include <netdb.h>
#include <sys/socket.h>     // for socket, connect, and socket releted contants
#include <unistd.h>         // for close
#include <cstring>          // for memset

class RedisClient{
public:
    RedisClient(const std::string &host, int port);   // constructor is called when objected is created
    ~RedisClient();                                   // distructor is called when object is getting out of scope
    
    bool connectToServer();          //return true for successful and false for fails connection
    void disconnect();               //method to disconnect from the server

private:
    std::string host;      //host or IP to connect with
    int port;              //port no. to connect with
    int sockfd;            //

};


#endif   //REDIS_CLIENT_H