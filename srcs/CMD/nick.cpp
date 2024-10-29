/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 18:06:31 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/29 18:09:41 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server.hpp"	
#include "../../inc/irc.hpp"

void Server::nick_cmd(Client *client, const std::string &nickname) {
	std::string clean_nickname = nickname;
	clean_nickname.erase(clean_nickname.find_last_not_of(" \n\r\t") + 1);
	client->set_nickname(clean_nickname);
	client->sendMessage(MSG_NICK(clean_nickname));
}