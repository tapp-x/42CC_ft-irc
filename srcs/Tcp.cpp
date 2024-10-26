/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tcp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:08:02 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/26 12:58:28 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Tcp.hpp"


// BASICS
Tcp::Tcp() : _sockServ() {}
Tcp::~Tcp() {}
Tcp::Tcp(const Tcp &other) : _sockServ(other._sockServ), _sockClient(other._sockClient){}

Tcp &Tcp::operator=(const Tcp &other){
	if (this != &other) {
		_sockServ = other._sockServ;
		_sockClient = other._sockClient;
		_pollfds = other._pollfds;
	}
	return (*this);
}
// ALL GETTERS
int		Tcp::getSockServ() {
	return (_sockServ.getFd());
}

// ALL SETTERS

//METHODS
void	Tcp::initServ(int port, int backlog) {
	_sockServ.init(port);
	_sockServ.setNonblock();
	_sockServ.bindSocket();
	_sockServ.listenSocket(backlog);

	//pursue with poll
	this->_newPoll.fd = _sockServ.getFd();
	this->_newPoll.events = POLLIN;
	this->_newPoll.revents = 0;
	_pollfds.push_back(_newPoll);
}

void	Tcp::acceptNewClient() {
	Socket *newClient;
	_sockServ.acceptConnection(newClient, _sockServ.getFd());
	std::cout << "New client accepted with fd " << newClient->getFd() << std::endl;
	_sockClient.push_back(newClient);
	_newPoll.fd = newClient->getFd();
	_newPoll.events = POLLIN;
	_newPoll.revents = 0;
	_pollfds.push_back(_newPoll);
	std::cout << "Number of clients: " << _sockClient.size() << std::endl;
	std::cout << "Number of pollfds: " << _pollfds.size() << std::endl;
}

void Tcp::run() {
	std::cout << "Server running " << std::endl;
	while (!globalSig) {
		if (poll(&_pollfds[0], _pollfds.size(), -1) == -1 && !globalSig) {
			throw TCPException("poll() error");
		}
		for (size_t i = 0; i < _pollfds.size(); i++) {
			if (_pollfds[i].revents == 0) {
				continue;
			}
			if (_pollfds[i].revents & POLLIN) {
				if (_pollfds[i].fd == _sockServ.getFd())
					acceptNewClient();
				else {
					handleClientMessage(_pollfds[i].fd);
				}
			}
		}
	}
	std::cout << "Server stopped"  << " poll size " << _pollfds.size() << std::endl;	
}

void	Tcp::removeClient(int clientFd) {
	std::cout << "Removing client with fd " << clientFd << std::endl;
	for (size_t i = 0; i < _sockClient.size(); i++)
	{
		if (_sockClient[i]->getFd() == clientFd)
		{
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
	std::cout << "Client " << clientFd << " removed" << std::endl;
}

void	Tcp::handleClientMessage(int clientFd) {
	char buffer[1024];
	int bytesRead = recv(clientFd, buffer, sizeof(buffer), 0);
	if (bytesRead <= 0) {
		std::cout << "Error or client disconnected with fd " << clientFd << std::endl;
		removeClient(clientFd);
	} else {
		std::string message(buffer, bytesRead);
		std::cout << "Received message from client " << clientFd << ": " << message << std::endl;
	}
}