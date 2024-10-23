/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tcp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:08:02 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/23 12:28:07 by tappourc         ###   ########.fr       */
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
	_sockServ.init();
	_sockServ.setNonblock();
	_sockServ.bindSocket(port);
	_sockServ.listenSocket(backlog);

	//pursue with poll
	this->_newPoll.fd = _sockServ.getFd();
	this->_newPoll.events = POLLIN;
	this->_newPoll.revents = 0;
	_pollfds.push_back(_newPoll);
}

Socket	Tcp::acceptNewClient() {
	 return (_sockServ.acceptConnection(_sockServ.getFd()));
}

void Tcp::run() {
	std::cout << "Server running" << std::endl;
	while (!globalSig) {
		if (poll(&_pollfds[0], _pollfds.size(), -1) == -1 && !globalSig) {
			throw TCPException("poll() error");
		}
		for (size_t i = 0; i < _pollfds.size(); i++) {
			if (_pollfds[i].revents == 0) {
				continue;
			}
			if (_pollfds[i].revents & POLLIN) {
				if (_pollfds[i].fd == _sockServ.getFd()) {
					std::cout << "Accepting new client" << std::endl;
					Socket newClient = acceptNewClient();
					std::cout << "New client accepted with fd " << newClient.getFd() << std::endl;
					_sockClient.push_back(newClient);
					_newPoll.fd = newClient.getFd();
					_newPoll.events = POLLIN;
					_newPoll.revents = 0;
					_pollfds.push_back(_newPoll);
					// _sockClient.push_back(acceptNewClient());
				} else {
					std::cout << "Handling message from client with fd " << _pollfds[i].fd << std::endl;
					handleClientMessage(_pollfds[i].fd);
				}
			}
			if (_pollfds[i].revents & POLLHUP) {
				std::cout << "Client with fd " << _pollfds[i].fd << " disconnected" << std::endl;
				removeClient(_pollfds[i].fd);
			}
		}
	}
}

void	Tcp::removeClient(int clientFd) {
	std::cout << "Removing client with fd " << clientFd << std::endl;
	for (size_t i = 0; i < _sockClient.size(); i++)
	{
		if (_sockClient[i].getFd() == clientFd)
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
		// Error or client disconnected
		std::cout << "Error or client disconnected with fd " << clientFd << std::endl;
		removeClient(clientFd);
	} else {
		// Process the message
		std::string message(buffer, bytesRead);
		std::cout << "Received message from client " << clientFd << ": " << message << std::endl;
		// Add your message handling logic here
	}
}