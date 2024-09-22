/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theoappourchaux <theoappourchaux@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:49:15 by tappourc          #+#    #+#             */
/*   Updated: 2024/09/05 19:49:06 by theoappourc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"

class Server {

	private:
		int						_port;
		int						_client_max;
		int						_sock_serv;

		std::string				_password;
		std::string				_hostname;

		struct sockaddr_in		_addr;

		// need to create other class
		// std::vector<Client>		clients;
		// std::vector<Channel>	channels;

	public:
		// BASICS
		Server();
		~Server();		
		Server(const Server &server);
		Server	&operator=(const Server &server);

		// SETTERS
		void			init(int port, int maxclient, std::string password, std::string hostname);
		void			set_port(int port);
		void			set_clientmax(int port);
		void			set_sockserv();
		
		// GETTERS
		int				get_port();
		int				get_sockserv();
		std::string		get_password();
		std::string		get_hostname();
		class ServerException : public Except {
			public:
				ServerException(std::string message) : Except("Server error", message) {}
		};
};

#endif