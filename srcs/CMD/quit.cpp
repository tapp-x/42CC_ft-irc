/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:16:41 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/30 17:33:39 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/irc.hpp"

std::string	Server::find_reasonQuit(const std::string &cmd) {
	std::vector<std::string> cmd_split = splitter(cmd, ' ');
	if (cmd_split.size() > 1) {
		return (cmd.substr(cmd_split[0].size() + 1));
	}
	return ("");
}

void	Server::quit_cmd(Client *client, const std::string &cmd) {
	// std::cout << "enter with client " << client->get_fd() << std::endl;
	// std::cout << "CMD: " << cmd << std::endl;
	std::string reason = find_reasonQuit(cmd);
	reason.erase(reason.find_last_not_of(" \n\r\t") + 1);
	// std::cout << "reason: " << reason << std::endl;

	for (size_t i = 0; i < _channels.size(); i++) {
		_channels[i]->removeClient(client);
		_channels[i]->removeAdmin(client);
		if (_channels[i]->getNbClients() == 0) {
			delete _channels[i];
			_channels.erase(_channels.begin() + i);
		}
		else {
			// std::cout << "Sending leaving message to all clients in channel " << _channels[i]->getName() <<
			// "he is leaving : " << client->get_nickname() << std::endl;
			std::string msg = MSG_QUIT(client->get_nickname(), client->get_username(), reason);
			_channels[i]->sendRespToAll(client, msg);
		}
	}
}