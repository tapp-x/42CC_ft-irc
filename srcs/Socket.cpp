/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:49:48 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/03 15:57:55 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Socket.hpp"

//BASICS
Socket::Socket() : _fd(-1) {
	std::cout << "socket create" << std::endl;
	memset(&_addr, 0, sizeof(_addr));
}

Socket::~Socket() {
	if (_fd != -1) {
		close(_fd);
	}
}

Socket::Socket(const Socket &other) {
	_fd = other._fd;
	_addr = other._addr;
}

Socket &Socket::operator=(const Socket &other) {
	if (this != &other) {
		_fd = other._fd;
		_addr = other._addr;
	}
	return (*this);
}

// ALL GETTERS
int Socket::getFd() {
	return (_fd);
}

const struct sockaddr_in& Socket::getAddr() {
	return (_addr);
}

// ALL SETTERS
void Socket::setFd(int fd) {
	std::cout << this->getFd() << std::endl;
	this->_fd = fd;
}

void Socket::setAddr(const struct sockaddr_in& addr) {
	_addr = addr;
}


// METHODS
void Socket::init() {
	int servfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	std::cout << servfd << std::endl;
	this->setFd(servfd);
	if (_fd < 0)
		throw SocketException("Failed at socket creation");
}

void Socket::bindSocket(int port) {
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = INADDR_ANY;
	_addr.sin_port = htons(port);

	if (bind(this->getFd(), (struct sockaddr*)&_addr, sizeof(_addr)) < 0)
		throw SocketException("Failed at socket bind");
}

void Socket::listenSocket(int backlog) {
	if (listen(this->getFd(), backlog) < 0)
		throw SocketException("Failed at socket listen");
}

Socket Socket::acceptConnection(int	sockServ) {
	std::cout << "passed here" << std::endl;
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);
	int clientFd = accept(sockServ, (struct sockaddr*)&clientAddr, &clientAddrLen);
	if (clientFd < 0)
		throw SocketException("Failed to accept connection");

	Socket clientSocket;
	clientSocket._fd = clientFd;
	clientSocket._addr = clientAddr;
	std::cout << "socket nb: " << clientFd <<" added !" <<std::endl;
	return (clientSocket);
}

void	Socket::setNonblock() {
	if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1)
		throw SocketException("Failed at socket fcntl");
}