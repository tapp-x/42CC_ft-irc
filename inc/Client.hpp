/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:54:23 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/28 14:22:25 by tappourc         ###   ########.fr       */
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
		
	public:
	//BASICS
		Client();
		~Client();
		Client(Client const &src);
		Client &operator=(Client const &src);
	
	//GETTERS
		std::string		get_username();
		std::string		get_nickname();
		std::string		get_ip();
		int				get_fd();
		ClientStatus	get_status();
		std::string		get_cmdBuff();
		bool			is_operator();
	
	//SETTERS
		void			set_fd(int fd);
		void			set_username(std::string username);
		void			set_nickname(std::string nickname);
		void			set_ip(std::string ipadd);
		void			set_status(ClientStatus new_status);
		void			set_operator(bool op);
		void			set_cmdBuff(const std::string &cmd);
		
	// METHODS
		bool			sendMessage(const std::string &message);
};

#endif