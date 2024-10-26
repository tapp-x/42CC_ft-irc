/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:54:46 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/26 20:00:54 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Client.hpp"

// BASICS
Client::~Client() {}

Client::Client() {
	this->_fd = -1;
	this->_username = "";
	this->_nickname = "";
	this->_ip = "";
	this->_cmdBuff = "";
	this->_status = WAITING;
	this->_operator = false;
}

Client::Client(Client const &src) {
	*this = src;
}

Client &Client::operator=(Client const &src) {
	if (this != &src) {
		this->_fd = src._fd;
		this->_username = src._username;
		this->_nickname = src._nickname;
		this->_ip = src._ip;
		this->_cmdBuff = src._cmdBuff;
		this->_status = src._status;
		this->_operator = src._operator;
	}
	return (*this);
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

ClientStatus	Client::get_status() {
	return (this->_status);
}

bool	Client::is_operator() {
	return (this->_operator);
}

std::string	Client::get_ip() {
	return (this->_ip);
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

void	Client::set_ip(std::string ipadd) {
	this->_ip = ipadd;
}

void	Client::set_status(ClientStatus new_status) {
	this->_status = new_status;
}

void	Client::set_operator(bool op) {
	this->_operator = op;
}