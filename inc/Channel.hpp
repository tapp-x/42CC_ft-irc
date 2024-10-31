/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:54:44 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/31 22:20:54 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <vector>
#include <string>
#include "Client.hpp"

class Channel {
private:
	// MEMBERS
		std::vector<Client *>		_clients;
		std::vector<Client *>		_admins;
		std::vector<std::string>	_invited;

	// ATTRIBUTES
		std::string					_name;
		std::string					_topic;
		std::string					_key;
		std::string					_time;
		std::string					_topic_setter;

	// PARAMETERS
		bool						_inviteOnly;
		bool						_topicRestricted;
		bool						_limited;
		bool						_isKey;
		size_t						_limit;

public:
	// BASICS
		Channel(const std::string &name);
		~Channel();
		Channel(const Channel &other);
		Channel &operator=(const Channel &other);

	// GETTERS
		std::string					getName() const;
		std::string					getTopic() const;
		std::string					getKey() const;
		std::string					getTime() const;
		std::string					getTopicSetter()const;
		size_t						getLimit() const;
		std::vector<Client *>		getClients() const;
		std::vector<Client *>		getAdmins() const;
		std::vector<std::string>	getInvited() const;
		size_t						getNbClients() const;
		bool						isTopicRestricted() const;
		bool						isLimited() const;
		bool						isInviteOnly() const;
		bool						isClient(Client *client) const;
		bool						isAdmin(Client *client) const;
		bool						isWithKey() const;

	// SETTERS
		void						setInviteOnly(bool inviteOnly);
		void						setTopicRestricted(bool topicRestricted);
		void						setTopicSetter(const std::string name);
		void						setTopic(const std::string &topic);
		void						setTime(const std::string &time);
		void						setKey(const std::string &key);
		void						setLimited(bool limited);
		void						setLimit(size_t limit);
		void						setIsKey(bool isKey);

	// METHODS
		void						addClient(Client *client);
		void						removeClient(Client *client);

	// ADMIN METHODS
		void						addAdmin(Client *client);
		void						removeAdmin(Client *client);

	// INVITE METHODS
		void						inviteClient(const std::string &nickname);
		void						removeInvited(const std::string &nickname);

	// SEND METHODS
		void						sendMsgToAll(Client *client, const std::string &message);
		void						sendRespToAll(Client *client, const std::string &message);
};

#endif