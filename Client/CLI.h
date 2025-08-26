#ifndef CLI_H  // guard to prevent the file from being included multiple time
#define CLI_H


#include<string>
//
#include "RedisClient.h"
#include "CommandHandler.h"
#include "ResponseParser.h"

class CLI{
    public:
        CLI(const std::string &host, int port);   //constructor take host and port to initialize the redisclient member

        void run(const std::vector<std::string>& commandArgs);                               //A method that will likely handle the user input loop for your CLI program
                                                  // will check if it ConnetToServer or not
        void executeCommand(const std::vector<std::string>& args);                                        
    private:
        RedisClient redisClient;   //This means that every CLI object contains a RedisClient object.
};

#endif    //CLI_H