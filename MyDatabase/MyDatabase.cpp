#include <iostream>
#include "Structs.h"
#include "Smth.h"
#include "Loot.h"

int main()
{
    Player pl;
    Loot lt;
	
	std::cout << "Avaliable commands:\n"
		<< "get-m, get-s, del-m, del-s, update-m, update-s, insert-m, insert-s, info-all, close\n";


	while (true)
	{
		std::string task;
		int id;

		std::cin >> task;
		if (task == "get-m") {
			std::cout << "Enter Player's Id\n";
			std::cin >> id;
			if (id > 0 && getPlayer(&pl, id)) {
				printPlayer(&pl);
			}
			else
				std::cout << "Player wasn't found" << std::endl;
		}
		else if (task == "get-s") {
			std::cout << "Enter Player's Id\n";
			std::cin >> id;
			if (getPlayer(&pl, id)) {
				std::cout << "Enter Loot's Id\n";
				std::cin >> id;
				if (getLoot(&lt, pl, id)) {
					printLoot(lt, pl);
				}
				else {
					std::cout << "Wrong loot Id" << std::endl;
				}
			}
			else
				std::cout << "Wrong player Id" << std::endl;
		}
		else if (task == "del-m") {
			std::cout << "Enter Player's Id\n";
			std::cin >> id;
			if (!getPlayer(&pl, id))
				std::cout << "Wrong player Id" << std::endl;
			else if (delPlayer(&pl, lt))
				std::cout << "The Player has been successfully deleted\n";
			else
				std::cout << "Something went wrong =(" << std::endl;
		}
		else if (task == "del-s") {
			std::cout << "Enter Player's Id\n";
			std::cin >> id;
			if (getPlayer(&pl, id)) {
				std::cout << "Enter Loot's Id\n";
				std::cin >> id;
				if (getLoot(&lt, pl, id)) {
					delLoot(lt, &pl);
					std::cout << "Item has been successfully deleted\n";
				}
				else
					std::cout << "Wrong Loot Id" << std::endl;
			}
			else
				std::cout << "Wrong Player Id" << std::endl;
		}
		else if (task == "update-m") {
			std::cout << "Enter Player's Id\n";
			std::cin >> id;

			pl.id = id;
			if (!getPlayer(&pl, id))
				std::cout << "Wrong Player Id" << std::endl;
			else {
				readPlayer(&pl);
				if (updatePlayer(&pl))
					std::cout << "The Player has been updated\n";
				else
					std::cout << "Something went wrong =(" << std::endl;
			}
		}
		else if (task == "update-s") {
			std::cout << "Enter Player's Id\n";
			std::cin >> id;
			if (getPlayer(&pl, id)) {
				std::cout << "Enter Loot's Id\n";
				std::cin >> id;
				if (getLoot(&lt, pl, id)) {
					std::string name;
					std::cout << "Enter Loot's name\n";
					std::cin >> name;
					lt.name = name;
					updateLoot(lt, id);
					std::cout << "Loot has been updated\n";
				}
				else
					std::cout << "Wrong Loot Id" << std::endl;
			}
			else
				std::cout << "Wrong Player Id" << std::endl;
		}
		else if (task == "insert-m") {
			readPlayer(&pl);
			insertPlayer(pl);
		}
		else if (task == "insert-s") {
			std::cout << "Enter Player's Id\n";
			std::cin >> id;
			if (getPlayer(&pl, id)) {
				int id_c = id;
				lt.player_Id = id;
				std::cout << "Enter Loot's Id\n";
				std::cin >> id;
				if (IsUnique(pl, lt, id)) {
					lt.id = id;
					lt.player_Id = id_c;
					std::string name;
					std::cout << "Enter Loot's name\n";
					std::cin >> name;
					lt.name = name;
					insertLoot(lt, pl);
					std::cout << "Loot has been added\n";
				}
				else
					std::cout << "Player already has that Id\n";
			}
			else
				std::cout << "Wrong Player Id" << std::endl;
		}
		else if(task == "info-all")
				getEveryone(&pl);
		else if (task == "close") {
			std::cout << "Have a nice day!";
			exit(0);
		}
		else
			std::cout<<"Wrong command\n";

		std::cout << std::endl;
	}
	return 0;
}
