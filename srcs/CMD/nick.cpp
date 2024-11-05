/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:06:31 by tappourc          #+#    #+#             */
/*   Updated: 2024/11/01 16:48:12 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"	
#include "../../inc/irc.hpp"

void Server::nick_cmd(Client *client, const std::string &nickname) {
	std::string clean_nickname = nickname;
	clean_nickname.erase(clean_nickname.find_last_not_of(" \n\r\t") + 1);
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i]->get_nickname() == clean_nickname) {
			if (_clients[i]->get_fd() == client->get_fd())
			{
				client->sendMessage("You can't change your nickname to your current nickname !\r\n");
				return ;
			}
			client->sendMessage(ERR_NICKNAMEINUSE(clean_nickname));
			return ;
		}
	}
	std::string past_nickname = client->get_nickname();
	client->set_nickname(clean_nickname);
	client->sendMessage(MSG_NICK(clean_nickname));
	if (client->get_username().size() >= 1 && past_nickname.size() == 0)
		client->sendMessage(MSG_WELCOME(client->get_nickname()));
}