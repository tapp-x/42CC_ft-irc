/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   who.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wneel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:17:08 by tappourc          #+#    #+#             */
/*   Updated: 2024/11/01 16:41:42 by wneel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/irc.hpp"

void	Server::who_cmd(Client *client, const std::string &cmd) {
	std::vector<std::string> cmd_split = this->splitter(cmd, ' ');
	if (cmd_split.size() != 2) {
		return;
	}
	std::string clean_channelName = cmd_split[1];
	if (clean_channelName[0] != '#')
	{
		// client->sendMessage("ERROR : channels must start with <#> character !\r\n");
		return ;
	}
	clean_channelName.erase(clean_channelName.find_last_not_of(" \n\r\t") + 1);
	for(size_t i = 0; i < this->_channels.size(); i++) {
		if (this->_channels[i]->getName() == clean_channelName) {

			client->sendMessage(WHO_START(client->get_nickname(), clean_channelName));
			_channels[i]->sendRespToAll(client, WHO_START(client->get_nickname(), clean_channelName));
			for (size_t j = 0; j < _channels[i]->getNbClients(); j++)
			{
				client->sendMessage(WHO_USER(_channels[i]->getClients()[j]->get_nickname()));
				_channels[i]->sendRespToAll(client, WHO_USER(_channels[i]->getClients()[j]->get_nickname()));
			}
			client->sendMessage(WHO_END(client->get_nickname(), clean_channelName));
			_channels[i]->sendRespToAll(client, WHO_END(client->get_nickname(), clean_channelName));
			return ;
		}
	}
	createChannel(clean_channelName, client);
}
