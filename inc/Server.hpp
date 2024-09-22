/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:15:45 by tappourc          #+#    #+#             */
/*   Updated: 2024/09/20 11:56:26 by tappourc         ###   ########.fr       */
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

		static bool				_sig;

		std::string				_password;
		std::string				_hostname;

		struct sockaddr_in		_addr;

		std::vector<Client>		_clients;
		// std::vector<Channel>		_channels;

		struct pollfd 				_new_cli;
		std::vector<struct pollfd>	_pollfds;

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

		//METHODS
		static void		sigHandler(int signum);
		void			close_serv():
		
		class ServerException : public Except {
			public:
				ServerException(std::string message) : Except("Server error", message) {}
		};
};

#endif