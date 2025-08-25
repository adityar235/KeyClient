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

#include "CLI.h"
#include<iostream>

#include <string>

//to stop redis server service  type this in terminal ->  sudo systemctl stop redis
// to start redis server service type this in terminal ->   sudo systemctl start redis-server


// argc = number of command-line tokens (at least 1).
//./myapp -h 127.0.0.1 -p 6380
// argc = 5,argv[0] = "./myapp" (the program name / path),argv[1] = "-h",argv[2] = "127.0.0.1",argv[3] = "-p",argv[4] = "6380"

// argv = array of C-strings; argv[0] is the program name, argv[1...] are the args.

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
        break;      //if token is neither "-h" nor "-p" (or missing value)

        ++i;
    }


    // handle REPL and one-shot command modes
    // Create the CLI object with the chosen host/port and start the REPL loop.
    CLI cli(host, port);    // clint class making cli object
    cli.run();

    //Here REPL stands for:
   //Read → Take input from the user (for example, a Redis command).
   //Evaluate → Process/execute the command (send it to Redis through your RedisClient).
   //Print → Show the result back to the user.
   //Loop → Repeat the cycle until the user quits.

    return 0;
}