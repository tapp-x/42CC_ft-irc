/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:49:48 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/26 19:55:12 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Socket.hpp"

//BASICS
Socket::Socket() : _fd(-1), _ip("") {
	memset(&_addr, 0, sizeof(_addr));
}

Socket::~Socket() {
	if (_fd != -1) {
		close(_fd);
	}
}

Socket::Socket(const Socket &other) {
	_fd = other._fd;
	_ip = other._ip;
	_addr = other._addr;
}

Socket &Socket::operator=(const Socket &other) {
	if (this != &other) {
		_fd = other._fd;
		_addr = other._addr;
		_ip = other._ip;
	}
	return (*this);
}

// ALL GETTERS
int Socket::getFd() const {
	return (_fd);
}

const struct sockaddr_in& Socket::getAddr() const {
	return (_addr);
}

std::string Socket::getIp() const{
	return (_ip);
}

// ALL SETTERS
void Socket::setFd(int fd) {
	this->_fd = fd;
}

void Socket::setAddr(const struct sockaddr_in& addr) {
	_addr = addr;
}

void Socket::setIp(const std::string &newIp) {
	_ip = newIp;
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

	_ip = "127.0.0.1";

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
	std::string newIp = inet_ntoa(clientAddr.sin_addr);
	clientSocket->setIp(newIp);
	// std::cout << "Accepted connection from " << clientSocket->getFd() << std::endl;
}

void	Socket::setNonblock() {
	if (fcntl(_fd, F_SETFL, O_NONBLOCK) == -1)
		throw SocketException("Failed at socket fcntl");
}