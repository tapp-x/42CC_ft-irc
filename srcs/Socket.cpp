/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:49:48 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/26 13:03:56 by tappourc         ###   ########.fr       */
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
	this->_fd = fd;
}

void Socket::setAddr(const struct sockaddr_in& addr) {
	_addr = addr;
}


// METHODS
void Socket::init(int port) {
	int servfd = socket(AF_INET, SOCK_STREAM, 0);
	std::cout << servfd << std::endl;
	this->setFd(servfd);
	if (_fd < 0)
		throw SocketException("Failed at socket creation");
	
	_addr.sin_family = AF_INET;
	_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	_addr.sin_port = htons(port);

	int opt = 1;
	if (setsockopt(_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw SocketException("Failed at socket setsockopt");
}

void Socket::bindSocket() {
	if (bind(this->getFd(), (struct sockaddr*)&_addr, sizeof(_addr)) < 0)
		throw SocketException("Failed at socket bind");
}

void Socket::listenSocket(int backlog) {
	if (listen(this->getFd(), backlog) < 0)
		throw SocketException("Failed at socket listen");
}

void Socket::acceptConnection(Socket *clientSocket, int sockServ) {
	struct sockaddr_in clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);
	int clientFd = accept(sockServ, (struct sockaddr*)&clientAddr, &clientAddrLen);
	if (clientFd < 0)
		throw SocketException("Failed to accept connection");

	if (fcntl(clientFd, F_SETFL, O_NONBLOCK) < 0)
		throw SocketException("Failed at socket fcntl");

	clientSocket->setFd(clientFd);
	clientSocket->setAddr(clientAddr);
}

void	Socket::setNonblock() {
	if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1)
		throw SocketException("Failed at socket fcntl");
}