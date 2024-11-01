/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:01:30 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/30 16:31:11 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"

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
			this->_channels[i]->addClient(client);
			std::cout << MSG_JOIN(client->get_nickname(), clean_channelName) << std::endl;
			client->sendMessage(MSG_JOIN(client->get_nickname(), clean_channelName));
			_channels[i]->sendRespToAll(client, "has joined the channel.\r\n");
			return ;
		}
	}
	createChannel(clean_channelName, client);
}
