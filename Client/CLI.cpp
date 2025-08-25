#include "CLI.h"
#include <vector>

// Simple helper to trim whitespace
static std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(" \t\n\r\f\v");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\n\r\f\v");
    return s.substr(start, end - start + 1);
}


CLI::CLI(const std::string &host, int port) 
    : redisClient(host, port) {}             //ye host, port and socket=-1 set kar dega

void CLI::run() {                              // check if with taht host, port and socket is helps in connec to server or not
    if (!redisClient.connectToServer()) {
        return;
    }

    std::cout << "Connected to Redis at " << redisClient.getSocketFD() << "\n";
    std::string host = "127.0.0.1"; 
    int port = 6379;


     while (true) {
        std::cout << host  << ":" << port << "> ";
        std::cout.flush();
        std::string line;
        if (!std::getline(std::cin, line)) break;
        line = trim(line);
        if(line.empty()) continue;
        if (line == "quit") {
            std::cout << "Goodbye.\n";
            break;
        }
        if (line == "help") {
            std::cout << "Displaing help\n";
            continue;
        }

        // Split command into tokens using splitArgs  //commandhandler and commandparser is required here 
        std::vector<std::string> args = CommandHandler::splitArgs(line);
        if(args.empty()) continue;

        // for (const auto &arg : args) {
        //     std::cout << arg << "\n";
        // }

        std::string command = CommandHandler::buildRESPcommand(args);
         if (!redisClient.sendCommand(command)) {
            std::cerr << "(Error) Failed to send command.\n";
            break;
        }
        // response Parse and print response will be the next step
        std::string response = ResponseParser::parseResponse(redisClient.getSocketFD());
        std::cout << response << "\n";
    }

    redisClient.disconnect();


}