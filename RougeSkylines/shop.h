#pragma once

#include "playerStats.h"
#include "building.h"

#include <vector>

class shop
{
	const int SELL_AMMOUNT = 4;

	std::vector<building> bldngsForSale;
public:
	void updateShop(playerStats* stats);
	void buyBuilding(int idx, playerStats* stats);

	std::vector<building> getBuildings();

	std::string displayShop(playerStats* stats);
};

