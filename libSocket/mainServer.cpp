#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "server.h"
#include "client.h"
#include <string>

int main(int argc, char** argv) {

	// Validate the parameters
	if (argc != 2) {
		std::cout << "usage: " << argv[0] << " port" << std::endl;
		return 1;
	}

	//On créer dans un premier temps un objet de type serveur, et on lance dans un nouveau thread l'attente de connexion.
	std::shared_ptr<uqac::Server> my_server = std::make_shared<uqac::Server>("TCP", argv[1],
		[](uqac::Connection* c) { std::cout << "Client connected." << std::endl; },
		[&](uqac::Connection* c, char* recvBuffer) { std::cout << "Broadcasting message: " << recvBuffer << std::endl; my_server->broadcast(recvBuffer, c); },
		[](uqac::Connection* c) { std::cout << "Client disconnected." << std::endl; });



	std::string input = "";
	bool quit = false;

	std::cout << "===================================================================\n"
			"===\t8INF912 Programmation reseau dans les Jeux Video\t===\n"
			"===\t\t\tTP1 - Socket de Berkeley\t\t===\n"
			"===\tOscar Trosseau - Hippolyte Gossoin - Florent Bogacz\t===\n"
			"===\t\t\t\tSERVEUR\t\t\t\t===\n"
			"===\t\t\t\tPort: "<< argv[1] <<"\t\t\t===\n"
			"===\t\t\t\t\t\t\t\t===\n"
			"===\t\tEcrivez \"quit\" pour quitter l'application\t===\n"
			"===================================================================\n\n" << std::endl;
	
	
	while(quit == false) {
		std::getline(std::cin, input);
		if (input == "quit") {
			quit = true;
		}
		else {
			if (!input.empty()) {
				my_server->broadcast(input.c_str());
			}
		}
	}
	my_server->Quit();

	return 0;
}