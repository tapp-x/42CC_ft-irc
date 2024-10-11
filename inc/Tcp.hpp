/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tcp.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 12:24:42 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/03 15:54:05 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_HPP
#define TCP_HPP

#include "Socket.hpp"
#include "Client.hpp"
#include "irc.hpp"

class Socket;

class Tcp {
	private :
		Socket						_sockServ;		
		std::vector<Socket>			_sockClient;
		
		struct pollfd				_newPoll;
		std::vector<struct pollfd>	_pollfds;
		
	public:
	// BASICS
		Tcp();
		~Tcp();
		Tcp(const Tcp &other);
		Tcp &operator=(const Tcp &other);
	
	//GETTERS
		int							getSockServ();

	//SETTERS
	
	// METHODS
		void						initServ(int port, int backlog);
		Socket						acceptNewClient();
		void						run();
	
	//EXCEPTION
	class TCPException : public Except {
			public:
				TCPException(std::string message) : Except("TCP error", message) {}
		};
};

#endif