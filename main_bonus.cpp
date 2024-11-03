/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wneel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:49:18 by tappourc          #+#    #+#             */
/*   Updated: 2024/11/03 17:22:36 by wneel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/irc.hpp"
#include "inc/Server_bonus.hpp"

bool globalSig = false;

int main(int argc, char **argv)
{
	if (argc != 3) {
		std::cout << "Usage: " << argv[0] << " <port number> <password>" << std::endl;
		return (1);
	}
	Server serv;
	try {
		signal(SIGINT, Server::sigHandler);
		signal(SIGQUIT, Server::sigHandler);
		signal(SIGPIPE, SIG_IGN);
		serv.init(std::atoi(argv[1]), 100, argv[2], "localhost");
	}
	catch(const std::exception& e){
		// if (serv.get_sockserv() != -1)
		// 	close(serv.get_port());
		std::cout << e.what() << std::endl;
	}
}
