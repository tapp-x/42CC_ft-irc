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
			client->sendMessage(ERR_NICKNAMEINUSE(clean_nickname));
			return ;
		}
	}
	client->set_nickname(clean_nickname);
	client->sendMessage(MSG_NICK(clean_nickname));
}