/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bot_bonus.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wneel <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 19:17:08 by tappourc          #+#    #+#             */
/*   Updated: 2024/11/03 19:00:12 by wneel            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/Server_bonus.hpp"
#include "../../inc/irc.hpp"

std::string	get_jokedepapa() {
	std::vector<std::string> super_jokedepapa;
	super_jokedepapa.push_back("Pourquoi les plongeurs plongent-ils toujours en arrière et jamais en avant ? Parce que sinon ils tombent dans le bateau !");
	super_jokedepapa.push_back("Comment appelle-t-on un chien qui fait de la magie ? Un labracadabrador !");
	super_jokedepapa.push_back("Pourquoi les fantômes sont-ils de si mauvais menteurs ? Parce qu'on peut les voir à travers !");
	super_jokedepapa.push_back("Quel est le comble pour un électricien ? De ne pas être au courant !");
	super_jokedepapa.push_back("Pourquoi les maths sont-elles tristes ? Parce qu'elles ont trop de problèmes !");
	super_jokedepapa.push_back("Que dit une imprimante dans l'eau ? Aidez-moi, je suis coincée !");
	super_jokedepapa.push_back("Pourquoi les canards sont-ils toujours à l'heure ? Parce qu'ils sont dans le coin !");
	super_jokedepapa.push_back("Quel est le comble pour un jardinier ? D'avoir la main verte !");
	super_jokedepapa.push_back("Pourquoi les squelettes ne se battent-ils jamais ? Parce qu'ils n'ont pas de tripes !");
	super_jokedepapa.push_back("Comment appelle-t-on un chat qui va dans l'espace ? Un miaou-tre !");

	std::srand(static_cast<unsigned int>(std::time(NULL)));
	int randomIndex = std::rand() % super_jokedepapa.size();

	return (super_jokedepapa[randomIndex]);
}

void	Server::jokedepapa(Client *client) {
	for (size_t i = 0; i < _clients.size(); i++)
	{
		displayClientInfo(_clients[i]);
		if (_clients[i]->get_status() == BOT) {
			msgPrivate(_clients[i], client->get_nickname(), get_jokedepapa());
			std::cout << "sending a jokedepapa to " << client->get_nickname() << std::endl;
			return ;
		}
	}
}
