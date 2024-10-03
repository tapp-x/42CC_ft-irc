/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:48:25 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/03 15:22:03 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "irc.hpp"

class Socket {
	private:
		int							_fd;
		struct sockaddr_in			_addr;
	
	public:
	// BASIC
		Socket();
		~Socket();
		Socket(const Socket &other);
		Socket &operator=(const Socket &other);
	
	// GETTERS
		int							getFd();
		const struct sockaddr_in&	getAddr();
	
	// SETTERS
		void						setFd(int fd);
		void						setAddr(const struct sockaddr_in& addr);
	
	// METHODS
		void						init();
		void						bindSocket(int port);
		void						listenSocket(int backlog);
		Socket						acceptConnection();

	//EXCEPTION
		class SocketException : public Except {
			public:
				SocketException(std::string message) : Except("Socket error", message) {}
		};
};

#endif