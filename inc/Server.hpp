/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:15:45 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/29 18:09:33 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"
#include "Tcp.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class Client;
class Channel;
class Tcp;

class Server {

	private:
	// GLOBAL INFOS
		int					_port;
		int					_client_max;
		std::string			_password;
		std::string			_hostname;

	// SOCKET PART
		Tcp					*_TcpHandler;

	// LIST OF USER
		std::vector<Client *>	_clients;

	// LIST OF CHANNELS
		std::vector<Channel *>	_channels;
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
		int					get_clientmax();
		int					get_sockserv();
		std::string			get_password();
		std::string			get_hostname();
		Client				*get_client(int fd);
		Client				*get_client_by_nick(const std::string &nickname);
		Channel				*get_channel(const std::string &channelName);

	// METHODS
		static void			sigHandler(int signum);
		void				shutdown_serv();
		void				checkAndAddClient();
		void				checkAndRemoveClient();
		void				createChannel(const std::string &channelName, Client *client);

	// DEBUG
		void				display_info();
		void				displayClientInfo(Client *client);
		
		
		class ServerException : public Except {
			public:
				ServerException(std::string message) : Except("Server error", message) {}
		};
};

#endif