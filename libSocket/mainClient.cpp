#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "server.h"
#include "client.h"
#include <string>

int main(int argc, char** argv) {

	// Validate the parameters
	if (argc != 3) {
		std::cout << "usage: "<< argv[0] <<" adresse port" << std::endl;
		return 1;
	}

	std::shared_ptr<uqac::Client> my_client = std::make_shared<uqac::Client>("TCP", argv[1], argv[2],
		[&](uqac::Connection* c, char* recvBuffer) { std::cout << "Received message: " << recvBuffer << std::endl; },
		[](uqac::Connection* c) { std::cout << "Server disconnected." << std::endl; });

	std::string input = "";
	bool quit = false;

	std::cout << "===================================================================\n"
		"===\t8INF912 Programmation reseau dans les Jeux Video\t===\n"
		"===\t\t\tTP1 - Socket de Berkeley\t\t===\n"
		"===\tOscar Trosseau - Hippolyte Gossoin - Florent Bogacz\t===\n"
		"===\t\t\t\tCLIENT\t\t\t\t===\n"
		"===\t\t\t\tPort: " << argv[1] << "\t\t\t===\n"
		"===\t\t\t\t\t\t\t\t===\n"
		"===\t\tEcrivez \"quit\" pour quitter l'application\t===\n"
		"===================================================================\n\n" << std::endl;

	while (quit == false && my_client->isServerUp()) {
		std::getline(std::cin, input);

		if (input == "quit" || !my_client->isServerUp()) {	//La seconde partie est nécessaire si c'est le serveur qui se déconnecte, car on aura set "quit" dans le thread
			quit = true;
		}
		else {
			if (!input.empty()) {
				my_client->broadcast(input.c_str());
			}
		}
	}
	if (!my_client->isServerUp()) {
		std::cout << "The server has been shut down, disconnecting the client" << std::endl;
	}
	my_client->Quit();
	
	return 0;

}