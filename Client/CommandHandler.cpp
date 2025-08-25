#include "CommandHandler.h"
#include <regex>
#include <sstream>

std::vector<std::string> CommandHandler::splitArgs(const std::string &input) {
    std::vector<std::string> tokens;

    //for input std::string input = "SET mykey hello world";
     // without regex  // parts = ["SET", "mykey", "hello", "world"]
                        // Problem: Is this a command to set key "mykey" to value "hello world"
                        // or set key "mykey" to value "hello" and then the word "world" is garbage?
    // with regex  // parts = ["SET", "mykey", "hello world"] <- Correct!
    // Regular Expressions (regex) are a universal, general-purpose tool for pattern matching and text processing.
    // They are a fundamental concept in computer science that exists independently and is used across virtually all programming languages and thousands of applications.

    // Regex to match words or quoted strings
    std::regex rgx(R"((\"[^\"]+\"|\S+))"); 
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), rgx);
    auto words_end = std::sregex_iterator();

    for (auto it = words_begin; it != words_end; ++it) {
        std::string token = it->str();
        // Remove quotes
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
    oss << "*" << args.size() << "\r\n"; // num of args

    for (const auto &arg: args) {
        oss << "$" << arg.size() << "\r\n" << arg << "\r\n"; // len and value of arg
    }
    return oss.str();
}