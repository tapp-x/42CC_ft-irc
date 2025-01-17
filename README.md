# ft-irc

## Overview

`ft-irc` is a project developed as part of the 42 curriculum. It aims to create a simple Internet Relay Chat (IRC) server that complies with the RFC 2812 specification. The server allows multiple clients to connect, join channels, and communicate with each other.

## Features

- **Multi-client support**: Handle multiple clients simultaneously.
- **Channel management**: Create, join, and manage channels.
- **User authentication**: Password-protected server access.
- **Signal handling**: Graceful shutdown and signal management.
- **Bonus features**: Additional functionalities in the bonus version.

## Getting Started

### Prerequisites

- A Unix-like operating system (Linux, macOS, etc.)
- C++ compiler (GCC, Clang, etc.)

### Building the Project

To build the project, navigate to the project directory and run:

```sh
make
```

This will compile the source files and generate the executable.

### Running the Server
To start the server, use the following command:
```
./ft_irc <port number> <password>
```

You can now connect to the server with Hexchat ! 

## Project Structure
```
inc/
    Channel.hpp
    Client.hpp
    Exception.hpp
    format.hpp
    irc.hpp
    Server_bonus.hpp
    Server.hpp
    Socket.hpp
    Tcp.hpp

srcs/
    Channel.cpp
    Client.cpp
    CMD/
        bot_bonus.cpp
        invite.cpp
        join.cpp
        kick.cpp
        mode.cpp
        nick.cpp
        part.cpp
        pass.cpp
        privmsg.cpp
        quit.cpp
        topic.cpp
        user.cpp
        who.cpp
    Server_bonus.cpp
    Server.cpp
    Socket.cpp
    Tcp.cpp

main_bonus.cpp
main.cpp
Makefile
```

## Authors 
- tappourc
- wneel