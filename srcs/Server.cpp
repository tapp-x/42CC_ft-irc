/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:49:41 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/26 20:10:15 by tappourc         ###   ########.fr       */
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

int	Server::get_clientmax() {
	return (this->_client_max);
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

	this->display_info();
	std::cout << "Server is running..." << std::endl;
	while(globalSig == false) {
		_TcpHandler.run();
		checkAndAddClient();
		checkAndRemoveClient();
	}
	shutdown_serv();
}

void Server::shutdown_serv() {
	std::cout << "Shutting down server..." << std::endl;
	for (size_t i = 0; i < _clients.size(); i++) {
		close(_clients[i].get_fd());
		std::cout << "Client " << _clients[i].get_fd() << " disconnected." << std::endl;
		delete &_clients[i];
		_clients.erase(_clients.begin() + i);
	}
	_clients.clear();

	// Fermer les channels
	
	close(_TcpHandler.getSockServ());
	std::cout << "Server closed & all clients disconected" << std::endl;
}

void Server::checkAndAddClient() {
	if (_TcpHandler.getSockClientSize() > _clients.size()) {
		int clientFd = _TcpHandler.getLastFd();
		std::string clientIp = _TcpHandler.getLastIp();
		Client newClient;
		newClient.set_fd(clientFd);
		newClient.set_ip(clientIp);
		newClient.set_status(WAITING);
		_clients.push_back(newClient);
		std::cout << "Client added with fd " << clientFd << " and IP " << clientIp << std::endl;
	}
}

void Server::checkAndRemoveClient() {
	for (std::vector<Client>::iterator it = _clients.begin(); it != _clients.end(); ) {
		int clientFd = it->get_fd();
		if (!_TcpHandler.clientExists(clientFd)) {
			std::cout << "Removing client with fd " << clientFd << " from server" << std::endl;
			it = _clients.erase(it);
		} else {
			++it;
		}
	}
}