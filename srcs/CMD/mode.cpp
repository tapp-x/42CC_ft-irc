/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:19:44 by tappourc          #+#    #+#             */
/*   Updated: 2024/11/06 10:32:49 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/irc.hpp"

void Server::setInviteOnlyMode(Client *client, const std::string &channelName, char mode) {
	Channel *channel = get_channel(channelName);
	if (!channel)
		return;
	std::string mode_str;
	if (mode == '+') {
		channel->setInviteOnly(true);
		mode_str = "+i";
	}
	else {
		channel->setInviteOnly(false);
		mode_str = "-i";
	}
	client->sendMessage(MSG_CHANMODE(client->get_nickname(), channelName, mode_str, ""));
	channel->sendRespToAll(client, MSG_CHANMODE(client->get_nickname(), channelName, mode_str, ""));
}

void	Server::setKeyMode(Client *client, const std::string &channelName, char mode, const std::string &key) {
	Channel *channel = get_channel(channelName);
	if (!channel)
		return;
	std::string mode_str;
	if (mode == '+') {
		mode_str = "+k";
		channel->setKey(key);
		channel->setIsKey(true);
	} else {
		mode_str = "-k";
		channel->setKey("");
		channel->setIsKey(false);
	}
	client->sendMessage(MSG_CHANMODE(client->get_nickname(), channelName, mode_str, key));
	channel->sendRespToAll(client, MSG_CHANMODE(client->get_nickname(), channelName, mode_str, key));
}

void	Server::setLimitMode(Client *client, const std::string &channelName, char mode, std::string limit_str) {
	Channel *channel = get_channel(channelName);
	if (!channel)
		return;
	size_t limit;
	std::stringstream ss(limit_str);
	ss >> limit;
	std::string mode_str;
	if (mode == '+') {
		mode_str = "+l";
		channel->setLimit(limit);
		channel->setLimited(true);
	} else {
		mode_str = "-l";
		channel->setLimit(0);
		channel->setLimited(false);
	}
	client->sendMessage(MSG_CHANMODE(client->get_nickname(), channelName, mode_str, limit_str));
	channel->sendRespToAll(client, MSG_CHANMODE(client->get_nickname(), channelName, mode_str, limit_str));
}

void Server::setTopicProtectionMode(Client *client, const std::string &channelName, char mode) {
	Channel *channel = get_channel(channelName);
	if (!channel)
		return;
	std::string mode_str;
	if (mode == '+') {
		mode_str = "+t";
		channel->setTopicRestricted(true);
	}
	else {
		mode_str = "-t";	
		channel->setTopicRestricted(false);
	}
	client->sendMessage(MSG_CHANMODE(client->get_nickname(), channelName, mode_str, ""));
	channel->sendRespToAll(client, MSG_CHANMODE(client->get_nickname(), channelName, mode_str, ""));
}

void	Server::setOperatorMode(Client *client_sender, const std::string &channelName, char mode, const std::string &nickname) {
	Channel *channel = get_channel(channelName);
	if (!channel)
		return;
	std::string clean_nickname = nickname;
	clean_nickname.erase(clean_nickname.find_last_not_of(" \n\r\t") + 1);
	Client *client = get_client_by_nick(clean_nickname);
	if (!client)
		return;
	std::string mode_str;
	if (mode == '+') {
		if (!channel->isAdmin(client))
		channel->addAdmin(client);
		mode_str = "+o";
	}
	else {
		mode_str = "-o";
		channel->removeAdmin(client);
	}
	
	client_sender->sendMessage(MSG_CHANMODE(client->get_nickname(), channelName, mode_str, clean_nickname));
	channel->sendRespToAll(client_sender, MSG_CHANMODE(client->get_nickname(), channelName, mode_str, clean_nickname));
	{
		client_sender->sendMessage(WHO_START(client_sender->get_nickname(), channel->getName()));
		channel->sendRespToAll(client_sender, WHO_START(client_sender->get_nickname(), channel->getName()));
		for (size_t j = 0; j < channel->getNbClients(); j++)
		{
			client_sender->sendMessage(channel->isAdmin(channel->getClients()[j]) ? WHO_OP(channel->getClients()[j]->get_nickname()) : WHO_USER(channel->getClients()[j]->get_nickname()));
			channel->sendRespToAll(client_sender, channel->isAdmin(channel->getClients()[j]) ? WHO_OP(channel->getClients()[j]->get_nickname()) : WHO_USER(channel->getClients()[j]->get_nickname()));
		}
		client_sender->sendMessage(WHO_END(client_sender->get_nickname(), channel->getName()));
		channel->sendRespToAll(client_sender, WHO_END(client_sender->get_nickname(), channel->getName()));
	}
}

void Server::mode_cmd(Client *client, const std::string &cmd) {
	std::vector<std::string> tokens = this->splitter(cmd, ' ');
	if (tokens.size() < 3) {
		client->sendMessage("Error: Not enough parameters\r\n");
		return;
	}
	std::string channelName = tokens[1];
	std::string mode = tokens[2];
	if (!get_channel(channelName)) {
		client->sendMessage(ERR_NOSUCHCHANNEL(channelName));
		return;
	}
	if (!get_channel(channelName)->isClient(client)) {
		client->sendMessage(ERR_NOTONCHANNEL(channelName));
		return;
	}
	if (!get_channel(channelName)->isAdmin(client)) {
		client->sendMessage(ERR_CHANPRIVSNEEDED(channelName));
		return;
	}
	if (mode[0] != '+' && mode[0] != '-') {
		client->sendMessage("Error: Invalid mode format\r\n");
		return;
	}
	for (size_t i = 1; i < mode.size(); ++i) {
		char modeChar = mode[i];
		if (modeChar == 'i') {
			setInviteOnlyMode(client, channelName, mode[0]);
		} else if (modeChar == 'k') {
			if (tokens.size() < 4) {
				client->sendMessage("Error: Key mode requires a parameter\r\n");
				return;
			}
			setKeyMode(client, channelName, mode[0], tokens[3]);
		} else if (modeChar == 'l') {
			if (tokens.size() < 4) {
				client->sendMessage("Error: Limit mode requires a parameter\r\n");
				return;
			}
			setLimitMode(client, channelName, mode[0], tokens[3]);
		} else if (modeChar == 't') {
			setTopicProtectionMode(client, channelName, mode[0]);
		} else if (modeChar == 'o') {
			if (tokens.size() < 4) {
				client->sendMessage("Error: Operator mode requires a parameter\r\n");
				return;
			}
			setOperatorMode(client, channelName, mode[0], tokens[3]);
		} else {
			client->sendMessage("Error: Unknown mode character\r\n");
			return;
		}
	}
}