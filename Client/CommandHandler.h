#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <vector>
#include <string>

class CommandHandler {
public:
    //splitArgs Split comman into tokens
    static std::vector<std::string> splitArgs(const std::string &input);
    
};


#endif // COMMAND_HANDLER_H