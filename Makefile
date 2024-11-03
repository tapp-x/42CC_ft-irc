# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/29 10:45:35 by tappourc          #+#    #+#              #
#    Updated: 2024/10/31 22:15:14 by tappourc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98

BASE_SRC = \
		./srcs/Socket.cpp \
		./srcs/Tcp.cpp \
		./srcs/Client.cpp \
		./srcs/Channel.cpp \
		./srcs/CMD/join.cpp \
		./srcs/CMD/privmsg.cpp \
		./srcs/CMD/nick.cpp \
		./srcs/CMD/user.cpp \
		./srcs/CMD/quit.cpp \
		./srcs/CMD/invite.cpp \
		./srcs/CMD/part.cpp \
		./srcs/CMD/kick.cpp \
		./srcs/CMD/pass.cpp \
		./srcs/CMD/topic.cpp \
		./srcs/CMD/mode.cpp \
		./srcs/CMD/who.cpp


SRCS = \
		$(BASE_SRC) \
		main.cpp \
		./srcs/Server.cpp


BONUS_SRCS = \
		$(BASE_SRC) \
		main_bonus.cpp \
		./srcs/Server_bonus.cpp \
		./srcs/CMD/bot_bonus.cpp

OBJS = $(SRCS:.cpp=.o)
BONUS_OBJS = $(BONUS_SRCS:.cpp=.o)

EXEC = ircserv
BONUS_EXEC = ircserv_bonus

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

bonus: $(BONUS_EXEC)

$(BONUS_EXEC): $(BONUS_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f $(OBJS)
	rm -f $(BONUS_OBJS)

fclean: clean
	rm -f $(EXEC)
	rm -f $(BONUS_EXEC)

re: fclean all

.PHONY: all clean fclean re bonus
