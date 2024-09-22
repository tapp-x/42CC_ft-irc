/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:54:23 by tappourc          #+#    #+#             */
/*   Updated: 2024/09/19 14:23:11 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "irc.hpp"

class Client {
	private:
		int			_fd;

		std::string _username;
		std::string _nickname;
	public:
	//BASICS
		Client();
		Client(int fd, std::string username, std::string nickname);
		~Client();
		Client(Client const &src);
		Client &operator=(Client const &src);
	
	//GETTERS
		std::string	get_username();
		std::string	get_nickname();
		int			get_fd();
	//SETTERS
		void		set_username(std::string username);
		void		set_nickname(std::string nickname);
		void		set_fd(int fd);
	// METHODS
};

#endif