#ifndef CLI_H
#define CLI_H


#include<string>
//
#include "RedisClient.h"


class CLI{
    public:
        CLI(const std::string &host, int port);   //constructor
        void run();                               //run function

    private:
        RedisClient redisClient;
};

#endif    //CLI_H