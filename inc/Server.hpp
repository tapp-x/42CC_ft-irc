/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:15:45 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/03 15:24:14 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"
#include "Tcp.hpp"
#include "Client.hpp"

class Client;

class Server {

	private:
	//GLOBAL INFOS
		int					_port;
		int					_client_max;
		std::string			_password;
		std::string			_hostname;
	//SIGNAL TO STOP THE SERVER
		static bool			_sig;
	//SOCKET PART
		Tcp					_TcpHandler;
	// //LIST OF USER
		std::vector<Client>	_clients;
	// // LIST OF CHANNELS
	// 	// std::vector<Channel>	_channels;
	public:
		// BASICS
		Server();
		~Server();		
		Server(const Server &other);
		Server	&operator=(const Server &other);

		// SETTERS
		void				init(int port, int maxclient, std::string password, std::string hostname);
		void				set_port(int port);
		void				set_clientmax(int port);
		void				set_hostname(std::string hostname);
		void				set_password(std::string password);
		
		// GETTERS
		int					get_port();
		int					get_sockserv();
		std::string			get_password();
		std::string			get_hostname();

		//METHODS
		static void			sigHandler(int signum);
		void				display_info();
		
		class ServerException : public Except {
			public:
				ServerException(std::string message) : Except("Server error", message) {}
		};
};

#endif