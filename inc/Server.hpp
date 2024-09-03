/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:49:15 by tappourc          #+#    #+#             */
/*   Updated: 2024/08/29 11:18:06 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"

class Server {

	private:
		int			port;
		int			client_max;
		int			sock;

		std::string	password;
		std::string	hostname;

	public:
		Server();
		Server(const Server &server);
		Server	&operator=(const Server &server);
		~Server();
}

#endif