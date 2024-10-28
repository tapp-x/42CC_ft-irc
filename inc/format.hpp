/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:44:10 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/28 19:36:01 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMAT_HPP
#define FORMAT_HPP

#define EOL "\r\n"

#define MSG_WELCOME(name) "Welcome to IRC network " + name + "!" + EOL
#define MSG_NICK(nickname) "Your nickname is " + nickname + EOL
#define MSG_USER(username) "Your username is " + username + EOL
#define MSG_YOURHOST(host) "Your host is " + host + EOL
#define MSG_CREATED(date) "This server was created " + date + EOL
#define MSG_JOIN(nickname, channel) ":" + nickname + " JOIN " + channel + EOL
#define MSG_INVITE(nickname, channel) ":" + nickname + " INVITE " + channel + EOL
#define MSG_KICK(nickname, channel, reason) ":" + nickname + " KICK " + channel + " :" + reason + EOL
#define MSG_MODE(nickname, channel, mode) ":" + nickname + " MODE " + channel + " " + mode + EOL
#define MSG_PART(nickname, channel, reason) ":" + nickname + " PART " + channel + " :" + reason + EOL
#define MSG_PRIVMSG(nickname, target, message) ":" + nickname + " PRIVMSG " + target + " :" + message + EOL
#define MSG_QUIT(nickname, reason) ":" + nickname + " QUIT :" + reason + EOL
#define MSG_TOPIC(nickname, channel, topic) ":" + nickname + " TOPIC " + channel + " :" + topic + EOL

#endif