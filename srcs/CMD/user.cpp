/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:06:00 by tappourc          #+#    #+#             */
/*   Updated: 2024/11/01 17:05:29 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"	
#include "../../inc/irc.hpp"

void Server::user_cmd(Client *client, const std::string &username) {
	std::string clean_username = username;
	clean_username.erase(clean_username.find_last_not_of(" \n\r\t") + 1);
	for (size_t i = 0; i < _clients.size(); i++) {
		if (_clients[i]->get_username() == clean_username) {
			return ;
		}
	}
	client->set_username(clean_username);
	client->sendMessage(MSG_USER(clean_username));
}