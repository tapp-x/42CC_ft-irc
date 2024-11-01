/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:15:45 by tappourc          #+#    #+#             */
/*   Updated: 2024/11/01 16:48:35 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
#define SERVER_HPP

#include "irc.hpp"
#include "Tcp.hpp"
#include "Client.hpp"
#include "Channel.hpp"

class Client;
class Channel;
class Tcp;

class Server {

	private:
	// GLOBAL INFOS
		int					_port;
		int					_client_max;
		std::string			_password;
		std::string			_hostname;

	// SOCKET PART
		Tcp					*_TcpHandler;

	// LIST OF USER
		std::vector<Client *>	_clients;

	// LIST OF CHANNELS
		std::vector<Channel *>	_channels;
	public:
	// BASICS
		Server();
		~Server();		
		Server(const Server &other);
		Server	&operator=(const Server &other);

	// SETTERS
		void				init(int port, int maxclient, std::string password, std::string hostname);
		void				set_port(int port);
		void				set_clientmax(int port);
		void				set_hostname(std::string hostname);
		void				set_password(std::string password);
		
	// GETTERS
		int					get_port();
		int					get_clientmax();
		int					get_sockserv();
		std::string			get_password();
		std::string			get_hostname();
		Client				*get_client(int fd);
		Client				*get_client_by_nick(const std::string &nickname);
		Channel				*get_channel(const std::string &channelName);

	// METHODS
		static void			sigHandler(int signum);
		void				shutdown_serv();
		void				checkAndAddClient();
		void				checkAndRemoveClient();
		void				createChannel(const std::string &channelName, Client *client);

	// COMMANDS
		void				join_cmd(Client *client, std::vector<std::string> &cmd_split);
		void				user_cmd(Client *client, const std::string &username);
		void				nick_cmd(Client *client, const std::string &nickname);
		void				privmsg_cmd(Client *client, const std::string &cmd);
		void				quit_cmd(Client *client, const std::string &cmd);
		void				invite_cmd(Client *client, std::vector<std::string> cmd_split);
		void				part_cmd(Client *client, const std::string &cmd);
		void				kick_cmd(Client *client, const std::string &cmd);
		void				pass_cmd(Client *client, const std::vector<std::string> cmd_split);
		void				topic_cmd(Client *client, const std::string &cmd);
		void				mode_cmd(Client *client, const std::string &cmd);
		void				who_cmd(Client *client, std::vector<std::string> &cmd_split);

	// UTILS FOR EXEC	
		std::vector<std::string>	splitter(const std::string &str, char space);
		std::vector<std::string>	splitCommands(const std::string &str);
		std::vector<std::string>	splitter_kick(const std::string &str, char space);
		std::string					current_time();	
		std::string					find_reasonQuit(const std::string &cmd);
		std::string					find_reasonPart(const std::string &cmd);
		void						exec_cmd(const std::string &cmd, int fd);
		void						msgOnChannel(Client *client, const std::string &channelName, const std::string &message);
		void						msgPrivate(Client *client, const std::string &target, const std::string &message);
		void						checkPassword(Client *client, std::string &password);
		void						change_topic_cmd(Client *client, const std::string &cmd, const std::vector<std::string> &cmd_split, Channel *channel);
		void						show_topic(Client *client, std::string &channel, Channel *channelObj);
		void						setInviteOnlyMode(Client *client, const std::string &channelName, char mode);
		void						setLimitMode(Client *client, const std::string &channelName, char mode, std::string limit_str);
		void						setTopicProtectionMode(Client *client, const std::string &channelName, char mode);
		void						setOperatorMode(Client *client_sender, const std::string &channelName, char mode, const std::string &nickname);
		void						setKeyMode(Client *client, const std::string &channelName, char mode, const std::string &key);
		void						checkPermToJoin(Client *client, Channel *chan, std::vector<std::string> &cmd_split);

	// DEBUG
		void				display_info();
		void				displayClientInfo(Client *client);
		
		
		class ServerException : public Except {
			public:
				ServerException(std::string message) : Except("Server error", message) {}
		};
};

#endif