#include "CLI.h"

CLI::CLI(const std::string &host, int port) 
    : redisClient(host, port) {}             //ye host, port and socket=-1 set kar dega

void CLI::run() {                              // check if with taht host, port and socket is helps in connec to server or not
    if (!redisClient.connectToServer()) {
        return;
    }

    std::cout << "Connected to Redis at \n" ;
    // std::string host = "127.0.0.1"; 
    // int port = 6379;


}