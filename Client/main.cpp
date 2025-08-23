/*

## what we are going to do

1. command-line argument parsing(we will parsh the argument from clint side we will use tokenaziation and make them redy to send over server)
   -h <host> -p <port>  default: 127.0.0.1,  -p <port> default: 6379
   if no args, launch interactive REPH mode

2. object oriented programming
   RedisClient(we will use socket), commandhandler(for parshing the input), repsonseparser(parsh responce from server), cli(handel user input and output)

3. Establish TCP connection to redis (redisclient)
   barkeley sockets to open TCP connection
   IPv4 and IPv6 'getaddrinfo'

4. Parsing and command formatting (commandhandler)
   split user input(tokannize and handel)
   convert commands into RESP format:

   *3\r\n
   $3\r\nSET\r\n
   $3\r\nkey\r\n
   $5\r\nvalue\r\n

5. Handling Redis responses(in responseparsher)
   read server response and Parses RESP types
   +ok, -Error, :100, $5\r\nhello -> bulk string

6. Implement interactive REPL (cli)
   run loop: user input, valis redi commands, send commandsd to the server, display parsed response
   support:help, quit

7. main.cpp:parse command-line arguments, instantiate cli and launc in PEPL mode

socket programing
protocol handling
oops principle
cli development


*/


#include<iostream>
// #include "CLI.h"


int main(int argc, char* argv[])
{
    // this is default part if user will not give any host and port
    std::string host = "127.0.0.1";
    int port = 6379;
    int i = 1;

    
    // parse command-line arguments for -h and -p
    while(i < argc)
    {
        std::string arg = argv[i];

        if(arg == "-h" && i+1 < argc)
        {
            host = argv[++i];
        }
        else if(arg == "-p" && i+1 < argc)
        {
            port = std::stoi(argv[++i]);
        }
        else
        break;

        i++;
    }


    // handle REPL and one-shot command modes
    CLI::cli(host, port);    // clint class making cli object
    cli.run();

    return 0;
}