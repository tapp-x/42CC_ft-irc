/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theoappourchaux <theoappourchaux@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:49:41 by tappourc          #+#    #+#             */
/*   Updated: 2024/09/04 19:54:50 by theoappourc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

Server::Server(){
	this->port = 0;
	this->client_max = 0;
	this->sock_serv = -1;
}

Server::~Server(){}

Server::Server(const Server &server) {
	*this = server;
}

Server &Server::operator=(const Server &server) {
	if (this != &server) {
		port = server.port;
		client_max = server.client_max;
		sock_serv = server.sock_serv;
		addr = server.addr;
		// need to create other class
		// clients = server.clients;
		// channels = server.channels;
	}
	return (*this);
}

// ALL SETTERS
void	Server::init(int port, int maxclient, std::string password, std::string hostname){
	this->port = port;
	this->client_max = maxclient;
	this->password = password;
	this->hostname = hostname;
}

void	Server::set_port(int port){
	this->port = port;
}

void	Server::set_clientmax(int clientmax){
	this->client_max = clientmax;
}

// void	Server::set_sockserv(){
	
// }

// ALL GETTERS
int	Server::get_port() {
	return (this->port);	
}

int	Server::get_sockserv() {
	return (this->sock_serv);	
}

std::string	Server::get_password() {
	return (this->password);	
}

std::string	Server::get_hostname() {
	return (this->hostname);	
}
