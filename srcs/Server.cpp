/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:49:41 by tappourc          #+#    #+#             */
/*   Updated: 2024/09/28 10:35:41 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/irc.hpp"

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
		_pollfds = server._pollfds;
		// need to create other class
		// clients = server.clients;
		// channels = server.channels;
	}
	return (*this);
}

//LAUNCH SERV
void	Server::init(int port, int maxclient, std::string password, std::string hostname) {
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
			if (_pollfds[i].revents == 0 && this->_sig == false) // nothing happen here just continue
				continue ;
			if (_pollfds[i].revents & POLLIN) // there is data to read in this section
			{
				if (_pollfds[i].fd == this->get_sockserv())
				{
					add_client();
					break;
				}
				// else
				// 	std::cout << "new msg from : " << _pollfds[i].fd << std::endl;
				// this->start_exec(with the msg / buffer or fd)
			}
			if (_pollfds[i].revents & POLLHUP) // deconnection requested for this client
			{
				std::cout << _pollfds[i].fd << " want a deconexion" << std::endl;
				rmv_client(_pollfds[i].fd);
				break ;
			}
		}
	}
	this->close_serv();
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
	for (size_t i = 0; i < _clients.size(); i++) {
		std::cout << _clients[i].get_fd() << " : this Client is now disconected" << std::endl;
		if (_clients[i].get_fd() != -1) {
			// std::cout << _clients[i].get_fd() << " client closed" << std::endl;
			close(_clients[i].get_fd());
		}
	}
	if(_sock_serv != -1)
		close(_sock_serv);
	std::cout << "Server closed" << std::endl;
}

void	Server::add_client() {
	int			fd;
	sockaddr_in	addr = {};
	socklen_t	size = sizeof(addr);

	fd = accept(this->get_sockserv(), (sockaddr *) &addr, &size);
	if (fd < 0)
		throw ServerException("Failed at accepting new client");
	if (fcntl(fd, F_SETFL, O_NONBLOCK) == -1)
		throw ServerException("Failed at socket fcntl");

	pollfd new_pfd;
	new_pfd.fd = fd;
	new_pfd.events = POLLIN;
	new_pfd.revents = 0;
	_pollfds.push_back(new_pfd);

	Client newcli;
	newcli.set_fd(fd);
	newcli.set_ip(inet_ntoa((addr.sin_addr)));
	_clients.push_back(newcli);
	newcli.set_status(LOGIN);
	std::cout << fd << " this client is now connected" << std::endl;
}

void	Server::rmv_client(int fd) {
	for (size_t i = 0; i < this->_clients.size(); i++) {
		if (this->_clients[i].get_fd() == fd) {
			this->_clients.erase(this->_clients.begin() + i);
			std::cout << _clients[i].get_fd() << " this client is now disconnected" << std::endl;
			return;
		}
	}
}
