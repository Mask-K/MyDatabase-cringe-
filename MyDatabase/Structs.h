#pragma once
#pragma warning(disable : 4996)
#include <string>

struct Player {
	int id;
	std::string name;
	long address_of_first_loot = -1;
	int amountOfLoot = 0;
};


struct Loot {
	int id;
	std::string name;
	int player_Id;
	bool isFree; 
	long my_address;
	long nextL_address;
};

struct Indexing {
	int id;
	int address;
	bool exists; 
};