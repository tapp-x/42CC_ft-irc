/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:49:41 by tappourc          #+#    #+#             */
/*   Updated: 2024/09/20 11:59:33 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

Server::Server(){
	this->_sig = false;
	this->_port = 0;
	this->_client_max = 0;
	this->_sock_serv = -1;
}

Server::~Server(){}

Server::Server(const Server &server) {
	*this = server;
}

Server &Server::operator=(const Server &server) {
	if (this != &server) {
		_port = server._port;
		_client_max = server._client_max;
		_sock_serv = server._sock_serv;
		_addr = server._addr;
		_pollfds = server.pollfds;
		// need to create other class
		// clients = server.clients;
		// channels = server.channels;
	}
	return (*this);
}

//LAUNCH SERV
void	Server::init(int port, int maxclient, std::string password, std::string hostname){
	this->_port = port;
	this->_client_max = maxclient;
	this->_password = password;
	this->_hostname = hostname;

	this->set_sockserv();

	// pursue with poll etc
	this->_new_cli.fd = _sock_serv;
	this->_new_cli.events = POLLIN;
	this->_new_cli.revents = 0;
	_pollfds.push_back(_new_cli);
	
	std::cout << "server running ..." << std::endl;
	while(this->_sig == false)
	{
		if (poll(&_pollfds[0], _pollfds.size(), -1) == -1) // error occurs in poll
			throw ServerException("poll() error");
		for (size_t i = 0; i < _pollfds.size(); i++)
		{
			if (_pollfds[i].revents & POLLIN)
			{
				// if event occurs here, check if its new user or not
				// if its a new user, add it
				// if not handle buffer to choose action (del usr or exec cmd)
			}
		}
	}
}

void	Server::set_sockserv(){
	this->_sock_serv = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->_sock_serv < 0)
		throw ServerException("Failed at socket creation");
	
	std::cout << "socket(serv) value: " << this->_sock_serv << std::endl;

	this->_addr.sin_addr.s_addr = INADDR_ANY;
	this->_addr.sin_family = AF_INET;
	this->_addr.sin_port = htons(this->_port);
	
	std::cout << "server created at port: " << this->_addr.sin_port << " real value: " << _port << std::endl;

	if (fcntl(this->_sock_serv, F_SETFL, O_NONBLOCK) == -1)
		throw ServerException("Failed at socket fcntl");

	if (bind(this->_sock_serv, (struct sockaddr *)&this->_addr, sizeof(this->_addr)) == -1)
	{
		std::cout << errno << std::endl;
		throw ServerException("Failed at socket bind");
	}
	
	if (listen(this->_sock_serv, this->_client_max) == -1)
		throw ServerException("Failed at socket listen");
}

// ALL SETTERS
void	Server::set_port(int port){
	this->_port = port;
}

void	Server::set_clientmax(int clientmax){
	this->_client_max = clientmax;
}

// ALL GETTERS
int	Server::get_port() {
	return (this->_port);
}

int	Server::get_sockserv() {
	return (this->_sock_serv);
}

std::string	Server::get_password() {
	return (this->_password);
}

std::string	Server::get_hostname() {
	return (this->_hostname);
}

// METHODS
bool Server::_sig = false;
void	Server::sigHandler(int signum) {
	(void)signum;
	std::cout << std::endl << "Signal Received!" << std::endl;
	Server::_sig = true;
}

void	Server::close_serv() {
	for (int i = 0; i < _clients.size(); i++) {
		std::cout << _clients[i].get_fd() << " : this Client is now disconected" << std::endl;
		if (_clients[i].get_fd() != -1)
			close(_clients[i].get_fd());
	}
	if(_sock_serv != -1)
		close(_sock_serv);
	std::cout << "Server closed" << std::endl;
}