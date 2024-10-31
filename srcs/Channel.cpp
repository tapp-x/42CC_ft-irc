/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:54:34 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/31 22:21:51 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/Channel.hpp"
#include <algorithm>
#include <iostream>

// BASICS
Channel::Channel(const std::string &name)
	: _name(name), _inviteOnly(false), _topicRestricted(false), _limited(false), _limit(0) {}

Channel::~Channel() {}

Channel::Channel(const Channel &other) {
	*this = other;
}

Channel &Channel::operator=(const Channel &other) {
	if (this != &other) {
		_name = other._name;
		_inviteOnly = other._inviteOnly;
		_topicRestricted = other._topicRestricted;
		_topic = other._topic;
		_key = other._key;
		_limited = other._limited;
		_limit = other._limit;
		_time = other._time;
		_topic_setter= other._topic_setter;
		_clients = other._clients;
		_admins = other._admins;
		_invited = other._invited;
	}
	return (*this);
}

// GETTERS
std::string Channel::getName() const {
	return (_name);
}

bool Channel::isInviteOnly() const {
	return (_inviteOnly);
}

bool Channel::isTopicRestricted() const {
	return (_topicRestricted);
}

std::string Channel::getTopic() const {
	return (_topic);
}

std::string Channel::getKey() const {
	return (_key);
}

std::string Channel::getTime() const {
	return (_time);
}

bool Channel::isLimited() const {
	return (_limited);
}

size_t Channel::getLimit() const {
	return (_limit);
}

std::vector<Client *> Channel::getClients() const {
	return (_clients);
}

size_t	Channel::getNbClients() const {
	return (_clients.size());
}

std::vector<Client *> Channel::getAdmins() const {
	return (_admins);
}

std::vector<std::string> Channel::getInvited() const {
	return (_invited);
}

bool Channel::isClient(Client *client) const {
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i] == client)
			return (true);
	}
	return (false);
}

bool Channel::isAdmin(Client *client) const {
	for (size_t i = 0; i < _admins.size(); i++) {
		if (_admins[i] == client)
			return (true);
	}
	return (false);
}

std::string	Channel::getTopicSetter() const {
	return (_topic_setter);	
}

bool Channel::isWithKey() const {
	return (_isKey);
}

// SETTERS
void Channel::setInviteOnly(bool inviteOnly) {
	_inviteOnly = inviteOnly;
}

void Channel::setTopicRestricted(bool topicRestricted) {
	_topicRestricted = topicRestricted;
}

void Channel::setTopic(const std::string &topic) {
	_topic = topic;
}

void Channel::setKey(const std::string &key) {
	_key = key;
}

void Channel::setLimited(bool limited) {
	_limited = limited;
}

void Channel::setLimit(size_t limit) {
	_limit = limit;
}

void Channel::setTime(const std::string &time) {
	_time = time;
}

void Channel::setTopicSetter(const std::string name) {
	_topic_setter = name;
}

void Channel::setIsKey(bool isKey) {
	_isKey = isKey;
}

// METHODS
void Channel::addClient(Client *client) {
	if (_limited && _clients.size() >= _limit) {
		std::cerr << "Channel limit reached. Cannot add more clients." << std::endl;
		return;
	}
	_clients.push_back(client);
	std::cout << "Client " << client->get_fd() << " added to channel " << _name << std::endl;
}

void Channel::removeClient(Client *client) {
	std::vector<Client *>::iterator it = std::find(_clients.begin(), _clients.end(), client);
	if (it != _clients.end()) {
		_clients.erase(it);
		std::cout << "Client " << client->get_fd() << " removed from channel " << _name << std::endl;
	}
}

void Channel::addAdmin(Client *client) {
	_admins.push_back(client);
	std::cout << "Client " << client->get_fd() << " added as admin to channel " << _name << std::endl;
}

void Channel::removeAdmin(Client *client) {
	std::vector<Client *>::iterator it = std::find(_admins.begin(), _admins.end(), client);
	if (it != _admins.end()) {
		_admins.erase(it);
		std::cout << "Client " << client->get_fd() << " removed as admin from channel " << _name << std::endl;
	}
}

void Channel::inviteClient(const std::string &nickname) {
	_invited.push_back(nickname);
	std::cout << "Client " << nickname << " invited to channel " << _name << std::endl;
}

void Channel::removeInvited(const std::string &nickname) {
	std::vector<std::string>::iterator it = std::find(_invited.begin(), _invited.end(), nickname);
	if (it != _invited.end()) {
		_invited.erase(it);
		std::cout << "Client " << nickname << " removed from invited list of channel " << _name << std::endl;
	}
}

void	Channel::sendMsgToAll(Client *client, const std::string &message) {
	// std::cout << "msg : " << message << std::endl;
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i] != client) {
			_clients[i]->sendMessage(MSG_PRIVMSG(client->get_nickname(), _name, message));
		}
	}
}

void	Channel::sendRespToAll(Client *client, const std::string &message) {
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i] != client) {
			_clients[i]->sendMessage(message);
		}
	}
}