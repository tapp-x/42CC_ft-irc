/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:49:41 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/11 18:10:53 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

//BASICS
Server::Server() : _TcpHandler() {
	this->_port = 0;
	this->_client_max = 0;
	this->_password = "";
	this->_hostname = "";
}

Server::~Server(){}

Server::Server(const Server &other) : _TcpHandler(other._TcpHandler), _clients(other._clients){
	*this = other;
}

Server &Server::operator=(const Server &other) {
	if (this != &other) {
		_port = other._port;
		_client_max = other._client_max;
		_password = other._password;
		_hostname = other._hostname;
		_TcpHandler = other._TcpHandler;
		_clients = other._clients;
		// channels = server.channels;
	}
	return (*this);
}


// ALL SETTERS
void	Server::set_port(int port){
	this->_port = port;
}

void	Server::set_clientmax(int clientmax){
	this->_client_max = clientmax;
}

void	Server::set_hostname(std::string hostname){
	this->_hostname = hostname;
}

void	Server::set_password(std::string password){
	this->_password = password;
}

// ALL GETTERS
int	Server::get_port() {
	return (this->_port);
}

int	Server::get_sockserv() {
	return (_TcpHandler.getSockServ());
}

std::string	Server::get_password() {
	return (this->_password);
}

std::string	Server::get_hostname() {
	return (this->_hostname);
}

// METHODS
// bool Server::_sig = false;
void	Server::sigHandler(int signum) {
	(void)signum;
	std::cout << std::endl << "Signal Received!" << std::endl;
	globalSig = true;
}

void Server::display_info() {
	std::cout << "===================================" << std::endl;
	std::cout << "|	SERVER RUNNING		  |" << std::endl;
	std::cout << "===================================" << std::endl;

	std::cout << std::left << std::setw(15) << "Hostname:" << get_hostname() << std::endl;
	std::cout << std::left << std::setw(15) << "Port:" << get_port() << std::endl;
	std::cout << std::left << std::setw(15) << "ServSocket ID:" << get_sockserv() << std::endl;
	std::cout << std::left << std::setw(15) << "Password:" << get_password() << std::endl;
	std::cout << std::left << std::setw(15) << "Usr logged:" << _clients.size() << std::endl;

	std::cout << "===================================" << std::endl;
}

//LAUNCH SERV
void	Server::init(int port, int maxclient, std::string password, std::string hostname) {
	this->_port = port;
	this->_client_max = maxclient;
	this->_password = password;
	this->_hostname = hostname;

	_TcpHandler.initServ(_port, _client_max);
	std::cout << "server initialised" << std::endl;

	this->display_info();
	while(globalSig == false) {
		_TcpHandler.run();
		//function to update the list of clients etc
	}
}