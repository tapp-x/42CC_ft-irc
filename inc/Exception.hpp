/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 18:15:35 by tappourc          #+#    #+#             */
/*   Updated: 2024/09/17 18:20:17 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRCEXCEPTION_HPP
# define IRCEXCEPTION_HPP

#include "irc.hpp"

class Except : public std::exception {
	private:
		std::string	message;

	public:
		Except(std::string prefix = "Exception", std::string message = "") {
			if (message.empty())
				this->message = "Unknown exception";
			else
				this->message = prefix + ": " + message;
		}
		~Except() throw() {}

		const char	*what() const throw() {
			return message.c_str();
		}
};

#endif