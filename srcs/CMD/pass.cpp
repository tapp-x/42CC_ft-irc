/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 10:12:51 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/31 10:55:36 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"
#include "../../inc/irc.hpp"

void	Server::checkPassword(Client *client, std::string &password) {
	std::cout << "Checking password" << std::endl;
	password.erase(password.find_last_not_of(" \n\r\t") + 1);
	if (password == _password) {
		client->set_status(REGISTERED);
		client->sendMessage(MSG_WELCOME(client->get_nickname()));
	} else {
		client->sendMessage("ERROR : Password incorrect\r\n");
	}
}

void	Server::pass_cmd(Client *client, std::vector<std::string> cmd_split) {
	if (cmd_split.size() < 2) {
		client->sendMessage(ERR_NEEDMOREPARAMS(cmd_split[0]));
		return;
	}
	checkPassword(client, cmd_split[1]);
	
}