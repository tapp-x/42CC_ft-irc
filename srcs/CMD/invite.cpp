/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:16:25 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/30 16:09:22 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/irc.hpp"

void Server::invite_cmd(Client *client, std::vector<std::string> cmd_split) {
	if (cmd_split.size() < 3) {
		client->sendMessage(ERR_NEEDMOREPARAMS(cmd_split[0]));
		return;
	}
	std::string channelName = cmd_split[2];
	channelName.erase(channelName.find_last_not_of(" \n\r\t") + 1);
	std::string nickname = cmd_split[1];
	nickname.erase(nickname.find_last_not_of(" \n\r\t") + 1);
	Channel *channel = get_channel(channelName);
	if (channel == NULL) {
		client->sendMessage(ERR_NOSUCHCHANNEL(channelName));
		return;
	}
	if (!channel->isClient(client)) {
		client->sendMessage(ERR_CANNOTSENDTOCHAN(channelName));
		return;
	}
	Client *invited = get_client_by_nick(nickname);
	if (invited == NULL) {
		client->sendMessage(ERR_NOSUCHNICK(nickname));
		return;
	}
	if (channel->isClient(invited)) {
		client->sendMessage(ERR_ALREADYINVITED(nickname));
		return;
	}
	channel->inviteClient(nickname);
	client->sendMessage(RPL_INVITING(client->get_nickname(), nickname, channelName));
	invited->sendMessage(RPL_INVITED(nickname, channelName));
}