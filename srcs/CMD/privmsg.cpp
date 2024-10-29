/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:28:41 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/29 19:00:58 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/irc.hpp"



void	Server::msgOnChannel(Client *client, const std::string &channelName, const std::string &message) {
	// std::cout << "MSG ON CHANNEL for channel "<< channelName << std::endl;
	Channel *channel = get_channel(channelName);
	if (channel == NULL) {
		std::cout << "Channel " << channelName << " does not exist." << std::endl;
		client->sendMessage(ERR_NOSUCHNICK(channelName));
		return;
	}
	if (!channel->isClient(client)) {
		std::cout << "Client " << client->get_nickname() << " is not on channel " << channelName << "." << std::endl;
		client->sendMessage(ERR_CANNOTSENDTOCHAN(channelName));
		return;
	}
	channel->sendToAll(client, message);
}

void	Server::msgPrivate(Client *client, const std::string &target, const std::string &message) {
	// std::cout << "MSG PRIVATE for target "<< target << std::endl;
	Client *clientTarget = get_client_by_nick(target);
	// std::cout << "MY TARGET FOR MSG : " << clientTarget->get_nickname() << std::endl;
	if (clientTarget == NULL) {
		client->sendMessage(ERR_NOSUCHNICK(target));
		return;
	}
	clientTarget->sendMessage(MSG_PRIVMSG(client->get_nickname(), target, message));
}

void	Server::privmsg_cmd(Client *client, const std::string &cmd) {
	std::vector<std::string> cmd_split = splitter(cmd, ' ');
	if (cmd_split.size() < 3) {
		client->sendMessage(ERR_NEEDMOREPARAMS(cmd_split[0]));
		return;
	}
	std::string channelName = cmd_split[1];
	std::string message = cmd.substr(cmd.find(cmd_split[2]));
	// std::cout << "-----------------------------------" << std::endl;
	// std::cout << "PRIVMSG " << channelName << " " << message << std::endl;
	// displayClientInfo(client);
	// std::cout << "-----------------------------------" << std::endl;
	if (channelName[0] == '#')
		msgOnChannel(client, channelName, message);
	else
		msgPrivate(client, channelName, message);
}