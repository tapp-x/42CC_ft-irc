/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:48:25 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/26 19:16:59 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
#define SOCKET_HPP

#include "irc.hpp"

class Socket {
	private:
		int							_fd;
		struct sockaddr_in			_addr;
		std::string					_ip;
	
	public:
	// BASIC
		Socket();
		~Socket();
		Socket(const Socket &other);
		Socket &operator=(const Socket &other);
	
	// GETTERS
		int							getFd() const;
		const struct sockaddr_in&	getAddr() const;
		std::string					getIp() const;
	
	// SETTERS
		void						setFd(int fd);
		void						setAddr(const struct sockaddr_in& addr);
		void						setIp(const std::string &ip);
	
	// METHODS
		void						init(int port);
		void						bindSocket();
		void						setNonblock();
		void						listenSocket(int backlog);
		void						acceptConnection(Socket *clientSocket, int fd);

	//EXCEPTION
		class SocketException : public Except {
			public:
				SocketException(std::string message) : Except("Socket error", message) {}
		};
};

#endif