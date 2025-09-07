#include "CommandHandler.h"
#include <regex>
#include <sstream>

std::vector<std::string> CommandHandler::splitArgs(const std::string &input) {          //untimately this function will return tokens
    std::vector<std::string> tokens;

  
    std::regex rgx(R"((\"[^\"]+\"|\S+))"); 
   
    
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), rgx);
    auto words_end = std::sregex_iterator();

    for (auto it = words_begin; it != words_end; ++it) {
        std::string token = it->str();
       
        if (token.size() >= 2 && token.front() == '\"' && token.back() == '\"') {
            token = token.substr(1, token.size() - 2);
        }
        tokens.push_back(token);
    }

    return tokens;

}

    /*
    * -> start of an array
    $ -> bulk of string
    +arg
    */

std::string CommandHandler::buildRESPcommand(const std::vector<std::string> &args) {  
    std::ostringstream oss;  
    oss << "*" << args.size() << "\r\n"; 

    for (const auto &arg: args) {
        oss << "$" << arg.size() << "\r\n" << arg << "\r\n"; // len and value of arg
    }
    return oss.str();
}

// input :  SET mykey myvalue
// output : *3\r\n             // tells total 3 arguments
//          $3\r\nSET\r\n      // first arguments
//          $5\r\nmykey\r\n    // second arguments
//          $7\r\nmyvalue\r\n  // third arguments
