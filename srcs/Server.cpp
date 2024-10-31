/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:49:41 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/31 11:34:56 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Server.hpp"

//BASICS
Server::Server() {
	this->_TcpHandler = new Tcp(this);
	this->_port = 0;
	this->_client_max = 0;
	this->_password = "";
	this->_hostname = "";
}

Server::~Server() {
	delete _TcpHandler;
	for (size_t i = 0; i < _clients.size(); ++i) {
		delete _clients[i];
	}
	for (size_t i = 0; i < _channels.size(); ++i) {
		delete _channels[i];
	}
}

Server::Server(const Server &other) : _TcpHandler(other._TcpHandler), _clients(other._clients){
	*this = other;
}

Server &Server::operator=(const Server &other) {
	if (this != &other) {
		_port = other._port;
		_client_max = other._client_max;
		_password = other._password;
		_hostname = other._hostname;
		_TcpHandler = new Tcp(this);
		_clients = other._clients;
		_channels = other._channels;
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
	return (_TcpHandler->getSockServ());
}

std::string	Server::get_password() {
	return (this->_password);
}

std::string	Server::get_hostname() {
	return (this->_hostname);
}

Client	*Server::get_client(int fd) {
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i]->get_fd() == fd) {
			return (_clients[i]);
		}
	}
	return (NULL);
}

Client *Server::get_client_by_nick(const std::string &nickname) {
	for (size_t i = 0; i < _clients.size(); i++) {
		std::string nick = _clients[i]->get_nickname();
		if (nick.compare(nickname) == 0) {
			return _clients[i];
		}
	}
	return NULL;
}

Channel	*Server::get_channel(const std::string &channelName) {
	for (size_t i = 0; i < _channels.size(); i++) {
		if (_channels[i]->getName() == channelName) {
			return (_channels[i]);
		}
	}
	return (NULL);
}

// METHODS
// bool Server::_sig = false;
void	Server::sigHandler(int signum) {
	(void)signum;
	std::cout << std::endl << "Signal Received!" << std::endl;
	globalSig = true;
}

// DISPLAY INFO

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

void Server::displayClientInfo(Client *client) {
	if (client == NULL) {
		std::cout << "Client is NULL" << std::endl;
		return;
	}
	std::cout << "Client Information:" << std::endl;
	std::cout << "FD: " << client->get_fd() << std::endl;
	std::cout << "IP: " << client->get_ip() << std::endl;
	std::cout << "Nickname: " << client->get_nickname() << std::endl;
	std::cout << "Username: " << client->get_username() << std::endl;
	std::cout << "Status: " << client->get_status() << std::endl;
	std::cout << "Operator: " << (client->is_operator() ? "Yes" : "No") << std::endl;
}

//LAUNCH & STOP SERV
void	Server::init(int port, int maxclient, std::string password, std::string hostname) {
	this->_port = port;
	this->_client_max = maxclient;
	this->_password = password;
	this->_hostname = hostname;

	_TcpHandler->initServ(_port, _client_max);

	this->display_info();
	std::cout << "Server is running..." << std::endl;
	while(globalSig == false) {
		_TcpHandler->run();
		checkAndAddClient();
		checkAndRemoveClient();
	}
	shutdown_serv();
}

void Server::shutdown_serv() {
	std::cout << "Shutting down server..." << std::endl;
	for (size_t i = 0; i < _clients.size(); i++) {
		close(_clients[i]->get_fd());
		std::cout << "Client " << _clients[i]->get_fd() << " disconnected." << std::endl;
		delete _clients[i];
		_clients.erase(_clients.begin() + i);
	}
	_clients.clear();

	// Fermer les channels
	if (_TcpHandler->getSockServ() != -1)
		close(_TcpHandler->getSockServ());
	std::cout << "Server closed & all clients disconected" << std::endl;
}

// ADD & REMOVE CLIENT
void Server::checkAndAddClient() {
	if (_TcpHandler->getSockClientSize() > _clients.size()) {
		int clientFd = _TcpHandler->getLastFd();
		std::string clientIp = _TcpHandler->getLastIp();
		Client *newClient = new Client();
		newClient->set_fd(clientFd);
		newClient->set_ip(clientIp);
		newClient->set_status(WAITING);
		_clients.push_back(newClient);
		std::cout << "Client added with fd " << clientFd << " and IP " << clientIp << "and nick : " << newClient->get_nickname() << std::endl;
		newClient->set_status(LOGIN);
		// displayClientInfo(newClient);
	}
}

void Server::checkAndRemoveClient() {
	for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); ) {
		int clientFd = (*it)->get_fd();
		if (!_TcpHandler->clientExists(clientFd)) {
			std::cout << "Removing client with fd " << clientFd << " from server" << std::endl;
			it = _clients.erase(it);
		} else
			++it;
	}
}

// HANDLE CHANNELS
void Server::createChannel(const std::string &channelName, Client *client) {
	// std::cout << "-------" << std::endl;
	// displayClientInfo(client);
	// std::cout << "-------" << std::endl;
	std::cout << "enter with client " << client->get_fd() << std::endl;
	std::string clean_channelName = channelName;
	clean_channelName.erase(clean_channelName.find_last_not_of(" \n\r\t") + 1);
	Channel *newChannel = new Channel(clean_channelName);
	newChannel->addAdmin(client);
	newChannel->addClient(client);
	this->_channels.push_back(newChannel);
	std::cout << "Channel " << clean_channelName << " created by client " << client->get_fd() << "." << std::endl;
	std::cout << MSG_JOIN(client->get_nickname(), clean_channelName) << std::endl;
	client->sendMessage(MSG_JOIN(client->get_nickname(), clean_channelName));
}


// EXECUTE CMD
std::vector<std::string> Server::splitter(const std::string &str, char space) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, space)) {
		tokens.push_back(token);
	}
	return (tokens);
}

std::vector<std::string> Server::splitCommands(const std::string &str) {
	return splitter(str, '\n');
}

void Server::exec_cmd(const std::string &cmd, int fd) {
	std::cout << "executing command: " << cmd << std::endl;
	// displayClientInfo(this->get_client(fd));
	this->get_client(fd)->set_cmdBuff(cmd);
	std::vector<std::string> commands = splitCommands(cmd);
	for (size_t i = 0; i < commands.size(); i++) {
		// std::cout << "passed here" << std::endl;
		std::vector<std::string> cmd_split = splitter(commands[i], ' ');
		if (cmd_split[0] == "PASS") {
			pass_cmd(this->get_client(fd), cmd_split);
		}
		if (this->get_client(fd)->get_status() != REGISTERED) {
			std::cout << "Client not registered" << std::endl;
			this->get_client(fd)->sendMessage("ERROR : You must be registered to use this server\r\n");
			this->get_client(fd)->set_cmdBuff("");
			return ;
		}
		if (cmd_split[0] == "JOIN") {
			join_cmd(this->get_client(fd), cmd_split);
		}
		if (cmd_split[0] == "NICK") {
			nick_cmd(this->get_client(fd), cmd_split[1]);
		}
		if (cmd_split[0] == "USER") {
			user_cmd(this->get_client(fd), cmd_split[1]);
		}
		if (cmd_split[0] == "PRIVMSG") {
			privmsg_cmd(this->get_client(fd), cmd);
		}
		if (cmd_split[0] == "QUIT") {
			quit_cmd(this->get_client(fd), cmd);
		}
		if (cmd_split[0] == "INVITE") {
			invite_cmd(this->get_client(fd), cmd_split);
		}
		if (cmd_split[0] == "PART") {
			part_cmd(this->get_client(fd), cmd);
		}
		if (cmd_split[0] == "KICK") {
			kick_cmd(this->get_client(fd), cmd);
		}
		if (cmd_split[0] == "TOPIC") {
			topic_cmd(this->get_client(fd), cmd);
		}
		if (cmd_split[0] == "MODE") {
			mode_cmd(this->get_client(fd), cmd);
		}
	}
	this->get_client(fd)->set_cmdBuff("");
}