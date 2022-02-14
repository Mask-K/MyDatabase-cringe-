#pragma once
#pragma warning(disable : 4996)

#include "Player.h"

bool IsUnique(Player gr, Loot& st, int id) {

	if (gr.address_of_first_loot == -1)
		return true;
	FILE* db = fopen("loot.fl", "r+b");
	
	fseek(db, gr.address_of_first_loot, SEEK_SET);

	for (int i = 0; i < gr.amountOfLoot; ++i) {
		fread(&st, sizeof(Loot), 1, db);
		fclose(db);

		if (st.id == id)
			return false;
		db = fopen("loot.fl", "r+b");
		fseek(db, st.nextL_address, SEEK_SET);
	}
	fclose(db);
	return true;
}

void getEveryone(Player* gr) {
	FILE* index = fopen("player.ind", "rb");
	if (index == NULL) {
		std::cout << "Database can't be found\n";
		return;
	}
	int st_count = 0;
	int gr_count = 0;

	fseek(index, 0, SEEK_END);
	int indAmount = ftell(index) / sizeof(Indexing);


	for (int i = 1; i <= indAmount; ++i) {
		if (getPlayer(gr, i)) {
			gr_count++;
			st_count += gr->amountOfLoot;

			std::cout << "Player " << gr->name << " has " << gr->amountOfLoot << " loot\n";
		}
	}
	fclose(index);

	std::cout << "Players: " << gr_count << std::endl;
	std::cout << "Items: " << st_count;
	std::cout << std::endl;
}


