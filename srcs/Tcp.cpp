/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tcp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:08:02 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/29 16:14:19 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Tcp.hpp"


// BASICS
Tcp::Tcp(Server *server) : _sockServ(), _server(server) {}
Tcp::~Tcp() {}
Tcp::Tcp(const Tcp &other) : _sockServ(other._sockServ), _sockClient(other._sockClient){}

Tcp &Tcp::operator=(const Tcp &other){
	if (this != &other) {
		_sockServ = other._sockServ;
		_sockClient = other._sockClient;
		_pollfds = other._pollfds;
		_server = other._server;
	}
	return (*this);
}

// ALL GETTERS
int		Tcp::getSockServ() {
	return (_sockServ.getFd());
}

size_t Tcp::getSockClientSize() const {
	return _sockClient.size();
}

int Tcp::getLastFd() const {
	if (!_sockClient.empty()) {
		return _sockClient.back()->getFd();
	}
	return -1;
}

std::string Tcp::getLastIp() const {
	if (!_sockClient.empty()) {
		return _sockClient.back()->getIp();
	}
	return "";
}

bool Tcp::clientExists(int clientFd) const {
	for (size_t i = 0; i < _sockClient.size(); ++i) {
		if (_sockClient[i]->getFd() == clientFd) {
			return true;
		}
	}
	return false;
}

//METHODS
void	Tcp::initServ(int port, int backlog) {
	_sockServ.init(port);
	_sockServ.setNonblock();
	_sockServ.bindSocket();
	_sockServ.listenSocket(backlog);

	this->_newPoll.fd = _sockServ.getFd();
	this->_newPoll.events = POLLIN;
	this->_newPoll.revents = 0;
	_pollfds.push_back(_newPoll);
}

void Tcp::run() {
	while (!globalSig) {
		if (poll(&_pollfds[0], _pollfds.size(), -1) == -1 && !globalSig) {
			throw TCPException("poll() error");
		}
		for (size_t i = 0; i < _pollfds.size(); i++) {
			if (_pollfds[i].revents == 0) {
				continue;
			}
			if (_pollfds[i].revents & POLLIN) {
				if (_pollfds[i].fd == _sockServ.getFd()){
					acceptNewClient();
					return ;
				}
					
				else {
					handleClientMessage(_pollfds[i].fd);
					return ;
				}
			}
		}
	}
	// std::cout << "Server stopped"  << " poll size " << _pollfds.size() << std::endl;	
}

void	Tcp::acceptNewClient() {
	Socket *newClient = new Socket();
	_sockServ.acceptConnection(newClient, _sockServ.getFd());
	_sockClient.push_back(newClient);
	_newPoll.fd = newClient->getFd();
	_newPoll.events = POLLIN;
	_newPoll.revents = 0;
	_pollfds.push_back(_newPoll);
	// std::cout << "New client accepted with fd " << newClient->getFd() << std::endl;
	// std::cout << "Number of clients: " << _sockClient.size() << std::endl;
	// std::cout << "Number of pollfds: " << _pollfds.size() << std::endl;
}

void	Tcp::removeClient(int clientFd) {
	// std::cout << "Removing client with fd " << clientFd << std::endl;
	for (size_t i = 0; i < _sockClient.size(); i++)
	{
		if (_sockClient[i]->getFd() == clientFd)
		{
			delete _sockClient[i];
			_sockClient.erase(_sockClient.begin() + i);
			break;
		}
	}
	for (size_t i = 0; i < _pollfds.size(); i++) {
		if (_pollfds[i].fd == clientFd) {
			_pollfds.erase(_pollfds.begin() + i);
			break;
		}
	}
	// std::cout << "Client " << clientFd << " removed" << std::endl;
}

void	Tcp::handleClientMessage(int clientFd) {
	char buffer[1024];
	int bytesRead = recv(clientFd, buffer, sizeof(buffer), 0);
	if (bytesRead <= 0) {
		// std::cout << "Error or client disconnected with fd " << clientFd << std::endl;
		removeClient(clientFd);
	} else {
		std::string message(buffer, bytesRead);
		// std::cout << "Received message from client " << clientFd << ": " << message << std::endl;
		this->_server->exec_cmd(message, clientFd);
	}
}