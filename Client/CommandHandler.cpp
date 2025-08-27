#include "CommandHandler.h"
#include <regex>
#include <sstream>

std::vector<std::string> CommandHandler::splitArgs(const std::string &input) {          //untimately this function will return tokens
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
    //Breakdown:

    // \"[^\"]+\"
    // \" → a double quote " character.
    // [^\"]+ → one or more characters that are not a quote (^ means "not").
    // \" → another double quote.
    // → This whole part matches something like "hello world" (including the quotes).

    // | (OR)
    // \S+
    // \S means "non-whitespace character" (the opposite of \s, which means space, tab, newline).
    // + means "one or more".
    // → So this matches words like SET, mykey, 123.
    
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), rgx);
    auto words_end = std::sregex_iterator();

    for (auto it = words_begin; it != words_end; ++it) {
        std::string token = it->str();
        //it->str() returns the entire matched text for that token.
        //For quoted tokens, that includes the surrounding quotes (e.g., "hello world").
        //For unquoted tokens, it’s just the word (e.g., SET).

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

std::string CommandHandler::buildRESPcommand(const std::vector<std::string> &args) {  //sending that splited commands with protocol
    std::ostringstream oss;  //string builder
    // oss comes with string stream <sstream> library
    // to store the string
    oss << "*" << args.size() << "\r\n"; // the thing which is going to be output will be stored in oss

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
