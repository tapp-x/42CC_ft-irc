# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 10:45:35 by tappourc          #+#    #+#              #
#    Updated: 2024/10/03 12:37:57 by tappourc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98


SRCS = \
		main.cpp \
		./srcs/Socket.cpp \
		./srcs/Tcp.cpp \
		./srcs/Server.cpp \
		./srcs/Client.cpp \
		./srcs/Channel.cpp \

OBJS = $(SRCS:.cpp=.o)

EXEC = ircserv

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(EXEC)

re: fclean all

.PHONY: all clean fclean re