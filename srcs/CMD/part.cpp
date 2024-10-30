/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:16:17 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/30 16:36:35 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/irc.hpp"

std::string	Server::find_reasonPart(const std::string &cmd) {
	std::vector<std::string> cmd_split = splitter(cmd, ' ');
	if (cmd_split.size() > 2) {
		std::string res = (cmd.substr(cmd_split[0].size() + cmd_split[1].size() + 2));
		res.erase(res.find_last_not_of(" \n\r\t") + 1);
		return (res);
	}
	return ("");
}

void	Server::part_cmd(Client *client, const std::string &cmd) {
	std::string reason = find_reasonPart(cmd);
	std::vector<std::string> cmd_split = splitter(cmd, ' ');
	if (cmd_split.size() < 2) {
		client->sendMessage(ERR_NEEDMOREPARAMS(cmd_split[0]));
		return ;
	}
	std::string channelName = cmd_split[1];
	channelName.erase(channelName.find_last_not_of(" \n\r\t") + 1);
	Channel *channel = get_channel(channelName);
	if (!channel) {
		client->sendMessage(ERR_NOSUCHCHANNEL(channelName));
		return ;
	}
	if (!channel->isClient(client)) {
		client->sendMessage(ERR_CANNOTSENDTOCHAN(channelName));
		return ;
	}
	channel->removeClient(client);
	channel->removeAdmin(client);
	if (channel->getNbClients() == 0) {
		_channels.erase(std::remove(_channels.begin(), _channels.end(), channel), _channels.end());
		delete channel;
	}
	else {
		std::string msg = MSG_PART(client->get_nickname(), channelName, reason);
		channel->sendRespToAll(client, msg);
	}
	client->sendMessage(MSG_PART(client->get_nickname(), channelName, reason));
}