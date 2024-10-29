/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tappourc <tappourc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 10:53:19 by tappourc          #+#    #+#             */
/*   Updated: 2024/10/28 19:29:38 by tappourc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_HPP
#define IRC_HPP

// CLASSIC LIBRARY
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <cstdlib>

// ERROR LIBRARY
#include <exception>
#include <errno.h>
#include <csignal>

// OTHER LIBRARY
#include <fcntl.h>

// SOCKET LIBRARY
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <poll.h>
#include <arpa/inet.h>
#include <netinet/in.h>

// CONTAINERS LIBRARY
#include <algorithm>
#include <iterator>
#include <vector>

// MY HPP FILES
#include "Exception.hpp"
#include "format.hpp"

extern bool globalSig;

#endif