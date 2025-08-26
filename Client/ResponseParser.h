#ifndef RESPONSEPARSER_H
#define RESPONSEPARSER_H

#include <string>

class ResponseParser {
public:
    // Read from the given socket and return parsed response a string, return "" in failure.
    static std::string parseResponse(int sockfd);
private:
    // this is Redis Serialization Protocol 2 (+ - : $ *)        //we can go with redi serialization protocol 3 also can use their properties like (# , ( ! = % ~ >))
    static std::string parseSimpleString(int sockfd);    //ping 
    static std::string parseSimpleError(int sockfd);      // invalidcmd or error msg
    static std::string parseInteger(int sockfd);          //
    static std::string parseBulkString(int sockfd);
    static std::string parseArray(int sockfd);
};

#endif // RESPONSEPARSER_H