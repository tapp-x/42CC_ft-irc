/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:54:46 by tappourc          #+#    #+#             */
/*   Updated: 2024/09/19 14:21:52 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Client.hpp"

// BASICS
Client::~Client() {}

Client::Client() {
	this->_fd = -1;
	this->_username = "";
	this->_nickname = "";
}

Client::Client(int fd, std::string username, std::string nickname){
	this->_fd = fd;
	this->_username = username;
	this->_nickname = nickname;
}

// GETTERS
std::string	Client::get_username() {
	return (this->_username);
}
std::string	Client::get_nickname() {
	return (this->_nickname);
}
int			Client::get_fd() {
	return (this->_fd);
}

// SETTERS
void	Client::set_username(std::string username) {
	this->_username = username;
}
void	Client::set_nickname(std::string nickname) {
	this->_nickname = nickname;
}
void	Client::set_fd(int fd) {
	this->_fd = fd;
}