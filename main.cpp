/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:49:18 by tappourc          #+#    #+#             */
/*   Updated: 2024/09/18 17:09:28 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./inc/irc.hpp"

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
		if (serv.get_sockserv() != -1)
			close(serv.get_port());
		std::cout << e.what() << std::endl;
	}
}

// port can be set between 1024 & 65535