/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 17:44:10 by tappourc          #+#    #+#             */
/*   Updated: 2024/11/05 20:21:42 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMAT_HPP
#define FORMAT_HPP

#define EOL "\r\n"

#define MSG_WELCOME(nickname) ":localhost 001 " + nickname + " :Welcome to IRC network !\r\n"
#define MSG_NICK(nickname) "Your nickname is " + nickname + EOL
#define MSG_USER(username) "Your username is " + username + EOL
#define MSG_YOURHOST(host) "Your host is " + host + EOL
#define MSG_CREATED(date) "This server was created " + date + EOL
#define MSG_JOIN(nickname, username, channel) ":" + nickname + "!" + username + "@localhost JOIN " + channel + EOL
#define MSG_INVITE(nickname, channel) ":" + nickname + " INVITE " + channel + EOL
#define MSG_KICK(nickname, channel, reason) ":" + nickname + " KICK " + channel + " :" + reason + EOL
#define MSG_MODE(nickname, channel, mode) ":" + nickname + " MODE " + channel + " " + mode + EOL
#define MSG_PART(nickname, channel, reason) ":" + nickname + " PART " + channel + " :" + reason + EOL
#define MSG_PRIVMSG(nickname, target, message) ":" + nickname + "!" + nickname + "@localhost PRIVMSG " + target + " " + message + EOL
#define MSG_QUIT(nickname, username, reason) ":" + nickname + "!~" + username + "@localhost QUIT " + reason + EOL
#define MSG_TOPIC(nickname, channel, topic) ":" + nickname + " TOPIC " + channel + " :" + topic + EOL
#define MSG_TOPICTIME(nickname, channel, time) ": 333 " + nickname + " " + channel + " " + nickname + " " + time + EOL
#define MSG_CHANMODE(nickname, channel, mode, args) ":" + nickname + " MODE " + channel + " " + mode + " " + args + EOL
#define WHO_START(nickname, channel) ":localhost 353 " + nickname + " @ " + channel + " :"
#define WHO_OP(nickname) "@" + nickname + " "
#define WHO_USER(nickname) "+" + nickname + " "
#define WHO_END(nickname, channel) "\r\n:localhost 366 " + nickname + " " + channel + " :END of /NAMES list" + EOL

#define RPL_INVITING(sender, receiver, channel) "341 " + sender + " " + receiver + " " + channel + EOL
#define RPL_INVITED(receiver, channel) ":" + receiver + "!" + receiver + " INVITE " + receiver + " " + channel + EOL

#define ERR_NOSUCHNICK(nickname) "401 " + nickname + " :No such nick/channel" + EOL
#define ERR_NOSUCHCHANNEL(channel) "403 " + channel + " :No such channel" + EOL
#define ERR_CANNOTSENDTOCHAN(channel) "404 " + channel + " :Cannot send to channel" + EOL
#define ERR_NICKNAMEINUSE(nickname) ": 433 " + nickname + " :Nickname is already in use" + EOL
#define ERR_USRNAMEINUSE(username) ": 433 " + username + " :Username is already in use" + EOL
#define ERR_NEEDMOREPARAMS(command) "461 " + command + " :Not enough parameters" + EOL
#define ERR_ALREADYINVITED(nickname) "467 :" + nickname + " Already invited" + EOL
#define ERR_CHANPRIVSNEEDED(channel) "482 " + channel + " :You're not channel operator" + EOL
#define ERR_NOTONCHANNEL(channel) "442 " + channel + " :You're not on that channel" + EOL
#define ERR_NOTOPIC(nickname, channel) ": 331 " + nickname + " " + channel + " :No topic is set" + EOL


#define ERR_NOTINVITED(nickname, channel) ":localhost 473 " + nickname + " " + channel + " :Cannot join channel (+i)" + EOL
#define ERR_PASSWDMISMATCH(nickname, channel) ":localhost 475 :" + nickname + " " + channel + " :Cannot join channel (+k) - bad key" + EOL
#define ERR_CHANLISFULL(nickname, channel) ":localhost 471 " + nickname + " " + channel + " :Cannot join channel (+l)" + EOL

#endif