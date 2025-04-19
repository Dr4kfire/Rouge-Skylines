#ifndef SHOP_H
#define SHOP_H

#include "playerstats.h"
#include "building.h"

#include <vector>

class Shop
{
	const int SELL_AMMOUNT = 4;

	std::vector<Building> bldngsForSale;
public:
	void updateShop(PlayerStats* stats);
	void buyBuilding(int idx, PlayerStats* stats);

	std::vector<Building> getBuildings();

	std::string displayShop(PlayerStats* stats);
};

#endif // SHOP_H