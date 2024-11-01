/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:01:30 by tappourc          #+#    #+#             */
/*   Updated: 2024/11/01 15:27:37 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

void	Server::checkPermToJoin(Client *client, Channel *chan, std::vector<std::string> &cmd_split) {
	bool canJoin = true;
	if (chan->isWithKey() == true) {
		if (cmd_split.size() == 3) {
			if (cmd_split[2] != chan->getKey()) {
				canJoin = false;
				client->sendMessage(ERR_PASSWDMISMATCH(client->get_nickname(), chan->getName()));
			}
			else
				canJoin = true;
		} else {
			canJoin = false;
			client->sendMessage(ERR_PASSWDMISMATCH(client->get_nickname(), chan->getName()));
		}
	}
	if (chan->isInviteOnly() == true) {
		std::vector<std::string> invited = chan->getInvited();
		if (std::find(invited.begin(), invited.end(), client->get_nickname()) == invited.end()) {
			canJoin = false;	
			client->sendMessage(ERR_NOTINVITED(client->get_nickname(), chan->getName()));
		}
	}
	if (chan->isLimited() == true) {
		if (chan->getLimit() <= chan->getNbClients()) {
			canJoin = false;
			client->sendMessage(ERR_CHANLISFULL(client->get_nickname(), chan->getName()));
		}
		else
			canJoin = true;
	}
	if (canJoin == true) {
		chan->addClient(client);
		std::cout << MSG_JOIN(client->get_nickname(), chan->getName()) << std::endl;
		client->sendMessage(MSG_JOIN(client->get_nickname(), chan->getName()));
		chan->sendMsgToAll(client, "has joined the channel.");
    who_cmd(client, cmd_split);
	}
}

void	Server::join_cmd(Client *client, std::vector<std::string> &cmd_split) {
	if (cmd_split.size() == 1) {
		client->sendMessage("ERROR : You must provide a valid channel name\r\n");
		return ;
	}
	std::string clean_channelName = cmd_split[1];
	if (clean_channelName[0] != '#')
	{
		client->sendMessage("ERROR : channels must start with <#> character !\r\n");
		return ;
	}
	clean_channelName.erase(clean_channelName.find_last_not_of(" \n\r\t") + 1);
	for(size_t i = 0; i < this->_channels.size(); i++) {
		if (this->_channels[i]->getName() == clean_channelName) {
			checkPermToJoin(client, this->_channels[i], cmd_split);
			return ;
		}
	}
	createChannel(clean_channelName, client);
}
