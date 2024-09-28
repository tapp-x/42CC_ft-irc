/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:54:23 by tappourc          #+#    #+#             */
/*   Updated: 2024/09/26 16:18:26 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "irc.hpp"

enum ClientStatus
{
	WAITING,
	LOGIN,
	REGISTERED,
	DISCONNECTED
};

class Client {
	private:
		int				_fd;

		std::string 	_username;
		std::string 	_nickname;
		std::string 	_ip;
		
		std::string 	_cmdBuff;

		ClientStatus	_status;
		bool			_operator;
		
		// Client(Client const &src);
		// Client &operator=(Client const &src);
	public:
	//BASICS
		Client();
		// Client(int fd, std::string username, std::string nickname);
		~Client();
	
	//GETTERS
		std::string		get_username();
		std::string		get_nickname();
		int				get_fd();
		ClientStatus	get_status();
		bool			is_operator();
	//SETTERS
		void			set_username(std::string username);
		void			set_nickname(std::string nickname);
		void			set_ip(std::string ipadd);
		void			set_fd(int fd);
		void			set_status(ClientStatus new_status);
	// METHODS
};

#endif