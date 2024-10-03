/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tcp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:08:02 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/03 15:29:11 by tappourc         ###   ########.fr       */
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
	_sockServ.bindSocket(port);
	_sockServ.listenSocket(backlog);
}

Socket	Tcp::acceptNewClient() {
	 _sockClient.push_back(_sockServ.acceptConnection());
	 return (_sockServ.acceptConnection());
}


bool	Tcp::_sigTCP = true;
void	Tcp::stop_sig() {
	this->_sigTCP = false;
}

void	Tcp::run() {
	if (poll(&_pollfds[0], _pollfds.size(), -1) == -1 && _sigTCP == false) // error occurs in poll
		throw TCPException("poll() error");
	for (size_t i = 0; i < _pollfds.size(); i++)
	{
		if (_pollfds[i].revents == 0) // nothing happen here just continue
			continue ;
		if (_pollfds[i].revents & POLLIN) // there is data to read in this section
		{
			if (_pollfds[i].fd == _sockServ.getFd())
			{
				this->acceptNewClient();
				break;
			}
			// else
			// 	handle the msg from clients already logged
		}
		// if (_pollfds[i].revents & POLLHUP) // deconnection requested for this client
		// handl disconect
	}
}