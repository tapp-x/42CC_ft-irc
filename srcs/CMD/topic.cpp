/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:17:08 by tappourc          #+#    #+#             */
/*   Updated: 2024/11/06 14:53:41 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/irc.hpp"

std::string	Server::current_time() {
	std::time_t current = std::time(NULL);
	std::stringstream res;

	res << current;
	return res.str();
}

void	Server::show_topic(Client *client, std::string &channel, Channel *chan) {
	std::string topic = chan->getTopic();
	std::string time = chan->getTime();
	if (topic.empty()) {
		client->sendMessage(ERR_NOTOPIC(client->get_nickname(), channel));
		return ;
	}
	client->sendMessage(MSG_TOPIC(chan->getTopicSetter(), channel, topic));
	client->sendMessage(MSG_TOPICTIME(chan->getTopicSetter(), channel, time));
}

void Server::change_topic_cmd(Client *client, const std::string &cmd, const std::vector<std::string> &cmd_split, Channel *channel) {
	std::string channelName = cmd_split[1];
	std::string tmp;
	tmp = cmd.substr(cmd_split[0].length() + cmd_split[1].length() + 1);
	size_t pos = tmp.find(':');
	std::string newTopic = tmp.substr(pos + 1);

	if (newTopic.length() > 80) {
		client->sendMessage("Error: Topic is too long. Maximum length is 80 characters.\r\n");
		return;
	}
	if (channel == NULL) {
		client->sendMessage(ERR_NOSUCHCHANNEL(channelName));
		return;
	}

	if (!channel->isClient(client)) {
		client->sendMessage(ERR_NOTONCHANNEL(channelName));
		return;
	}
	if (channel->isTopicRestricted() && !channel->isAdmin(client)) {
		client->sendMessage(ERR_CHANPRIVSNEEDED(channelName));
		return;
	}
	channel->setTopic(newTopic);
	channel->setTime(current_time());
	channel->setTopicSetter(client->get_nickname());
	std::string topicMessage = MSG_TOPIC(client->get_nickname(), channelName, newTopic);
	std::cout << "TOPIC MESSAGE CHANGE ----->: " << topicMessage << std::endl;
	channel->sendRespToAll(client, topicMessage);
	client->sendMessage(MSG_TOPIC(client->get_nickname(), channelName, newTopic));
}

void	Server::topic_cmd(Client *client, const std::string &cmd) {
	std::cout << "TOPIC CMD with :" << cmd <<std::endl;
	std::vector<std::string> cmd_split = this->splitter(cmd, ' ');
	if (cmd_split.size() < 2) {
		client->sendMessage(ERR_NEEDMOREPARAMS(cmd_split[0]));
		return ;
	}
	std::string channelName = cmd_split[1];
	channelName.erase(channelName.find_last_not_of(" \n\r\t") + 1);
	if (!get_channel(channelName)) {
		client->sendMessage(ERR_NOSUCHCHANNEL(channelName));
		return ;
	}
	if (!get_channel(channelName)->isClient(client)) {
		client->sendMessage(ERR_CANNOTSENDTOCHAN(channelName));
		return ;
	}
	Channel *channel = get_channel(channelName);	
	if (cmd_split.size() == 2) {
		show_topic(client, channelName, channel);
		return ;
	}
	if (channel->isTopicRestricted() && !channel->isAdmin(client)) {
		client->sendMessage(ERR_CHANPRIVSNEEDED(channelName));
		return;
	}
	if (cmd_split.size() == 3) {
		if (cmd_split[2][0] == ':')
			cmd_split[2] = cmd_split[2].substr(1);
		channel->setTopic(cmd_split[2]);
		channel->setTime(current_time());
		channel->setTopicSetter(client->get_nickname());
		channel->sendRespToAll(client, MSG_TOPIC(client->get_nickname(), channelName, cmd_split[2]));
		client->sendMessage(MSG_TOPIC(client->get_nickname(), channelName, cmd_split[2]));
		return ;
	}
	if (cmd_split.size() > 3) {
		change_topic_cmd(client, cmd, cmd_split, channel);
		return ;
	}
}