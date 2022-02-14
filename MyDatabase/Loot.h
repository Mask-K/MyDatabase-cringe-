#pragma once
#pragma warning(disable : 4996)

#include "Structs.h"
#include "Player.h"
#include <vector>

Loot lt3_12p;

bool updatePlayer(Player* pl);

void printLoot(Loot loot, Player pl){
	std::cout << "Player's name is " << pl.name
		<< " Loot's name is " << loot.name << std::endl;
}

void getToLastAddress(FILE* db, Loot& loot, Player pl) {
	long add = loot.my_address;
	db = fopen("loot.fl", "r+b");

	fseek(db, pl.address_of_first_loot, SEEK_SET);

	for (int i = 0; i < pl.amountOfLoot; ++i) {
		fread(&loot, sizeof(Loot), 1, db);
		fseek(db, loot.nextL_address, SEEK_SET);
	}

	loot.nextL_address = add;
	fwrite(&loot, sizeof(Loot), 1, db);
}


void changeAddresses(FILE* db, Loot loot, Loot prev_l, Player* pl) {
	if (loot.my_address == pl->address_of_first_loot) {
		if (loot.my_address == loot.nextL_address)
			pl->address_of_first_loot = -1;
		else
			pl->address_of_first_loot = loot.nextL_address;
	}
	else {
		if (loot.my_address == loot.nextL_address)
			prev_l.my_address = prev_l.nextL_address;
		else
			prev_l.nextL_address = loot.nextL_address;

		fseek(db, prev_l.my_address, SEEK_SET);
		fwrite(&prev_l, sizeof(Loot), 1, db);
	}
}



void deleteAddress(long lt_address) {
	FILE* trash = fopen("lt_trash.txt", "rb");
	int count = 0;
	
	fread(&count, sizeof(int), 1, trash);

	std::vector<long> queue(count);
	for (int i = 0; i < count; ++i)
		fread(&queue[i], sizeof(long), 1, trash);

	fclose(trash);

	trash = fopen("lt_trash.txt", "wb");
	++count;
	fwrite(&count, sizeof(int), 1, trash);

	for (auto el : queue)
		fwrite(&el, sizeof(long), 1, trash);
	
	fwrite(&lt_address, sizeof(long), 1, trash);

	fclose(trash);
}

void changeTrash(FILE* trash, Loot* lt, int counter) {
	std::vector<long> del(counter);
	for (int i = 0; i < counter; ++i)
		fread(&del[i], sizeof(long), 1, trash);
	
	lt->my_address = del[0];
	lt->nextL_address = del[0];

	fclose(trash);
	trash = fopen("lt_trash.txt", "wb");
	--counter;

	fwrite(&counter, sizeof(long), 1, trash);

	for (int i = 1; i <= counter; ++i)
		fwrite(&del[i], sizeof(long), 1, trash);

	fclose(trash);
}

bool insertLoot(Loot& lt, Player& pl) {
	lt.isFree = true;

	FILE* db = fopen("loot.fl", "a+b");
	FILE* trash = fopen("lt_trash.txt", "a+b");

	int count = 0;
	fread(&count, sizeof(int), 1, trash);
	if (count > 0) {
		changeTrash(trash, &lt, count);
		fclose(db);
		db = fopen("loot.fl", "r+b");
		fseek(db, lt.my_address, SEEK_SET);
	}
	else {
		fseek(db, 0, SEEK_END);

		int dbSize = ftell(db);

		lt.my_address = dbSize;
		lt.nextL_address = dbSize;
	}

	fwrite(&lt, sizeof(Loot), 1, db);

	if (!pl.amountOfLoot) {
		pl.address_of_first_loot = lt.my_address;
	}
	else {
		fclose(db);
		getToLastAddress(db, lt, pl);
	}

	fclose(db);
	++pl.amountOfLoot;
	updatePlayer(&pl);
	return true;
}

bool getLoot(Loot* lt, Player pl, int id) {

	if (pl.amountOfLoot == 0) {
		return false;
	}


	FILE* db = fopen("loot.fl", "rb");

	fseek(db, pl.address_of_first_loot, SEEK_SET);
	fread(lt, sizeof(struct Loot), 1, db);

	for (int i = 0; i < pl.amountOfLoot; ++i) {
		if (lt->id == id) {
			fclose(db);
			return true;
		}
		fseek(db, lt->nextL_address, SEEK_SET);
		fread(lt, sizeof(struct Loot), 1, db);
	}
	fclose(db);
	return false;
}

bool updateLoot(Loot lt, int id) {
	FILE* db = fopen("loot.fl", "r+b");
	
	fseek(db, lt.my_address, SEEK_SET);
	fwrite(&lt, sizeof(Loot), 1, db);
	fclose(db);

	return true;
}

void delLoot(Loot& lt, Player* pl) {
	FILE* db = fopen("loot.fl", "r+b");

	fseek(db, pl->address_of_first_loot, SEEK_SET);
	do {
		fread(&lt3_12p, sizeof(Loot), 1, db);
		fseek(db, lt3_12p.nextL_address, SEEK_SET);
	} while (lt3_12p.nextL_address != lt.my_address && lt.my_address != pl->address_of_first_loot);

	changeAddresses(db, lt, lt3_12p, pl);
	lt.isFree = 0;
	deleteAddress(lt.my_address);


	fseek(db, lt.my_address, SEEK_SET);
	fwrite(&lt, sizeof(Loot), 1, db);
	fclose(db);

	--pl->amountOfLoot;
	updatePlayer(pl);


}

