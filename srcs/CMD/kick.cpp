/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:17:53 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/30 17:25:45 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/irc.hpp"

std::vector<std::string>	Server::splitter_kick(const std::string &str, char space) {
	std::vector<std::string> tokens;
	std::stringstream ss(str);
	std::string token;
	while (std::getline(ss, token, space)) {
		token.erase(token.find_last_not_of(" \n\r\t") + 1);
		tokens.push_back(token);
	}
	return (tokens);
}

void	Server::kick_cmd(Client *client, const std::string &cmd) {
	std::vector<std::string> cmd_split = splitter_kick(cmd, ' ');
	if (cmd_split.size() < 3) {
		client->sendMessage(ERR_NEEDMOREPARAMS(cmd_split[0]));
		return ;
	}
	std::string channelName = cmd_split[1];
	std::string nickname = cmd_split[2];
	std::string reason = "Kicked";
	if (!cmd_split[3].empty())
		std::string reason = cmd_split[3];
	Channel *channel = get_channel(channelName);
	if (!channel) {
		client->sendMessage(ERR_NOSUCHCHANNEL(channelName));
		return ;
	}
	if (!channel->isClient(client)) {
		client->sendMessage(ERR_CANNOTSENDTOCHAN(channelName));
		return ;
	}
	if (!channel->isAdmin(client)) {
		client->sendMessage(ERR_CHANPRIVSNEEDED(channelName));
		return ;
	}
	Client *target = get_client_by_nick(nickname);
	if (!target) {
		client->sendMessage(ERR_NOSUCHNICK(nickname));
		return ;
	}
	if (!channel->isClient(target)) {
		client->sendMessage(ERR_CANNOTSENDTOCHAN(channelName));
		return ;
	}
	if (!channel->isClient(client) || !channel->isClient(target)) {
		client->sendMessage(ERR_CHANPRIVSNEEDED(channelName));
		return ;
	}
	channel->removeClient(target);
	channel->removeAdmin(target);
	std::string msg = MSG_KICK(client->get_nickname(), channelName, reason);
	channel->sendRespToAll(client, msg);
	client->sendMessage(msg);
}