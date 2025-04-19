#include "shop.h"

#include "building.h"
#include "objects/playerstats.h"
#include <vector>
#include <string>

using namespace std;

void Shop::updateShop(PlayerStats* stats) {
	this->bldngsForSale.clear();
	for (int i = 0; i < SELL_AMMOUNT; i++)
	{
		vector<Building::types> types = {
			Building::residential, Building::comercial,
			Building::industrial, Building::decoration
		};
		this->bldngsForSale.emplace_back(
			Building::getRndBldng(&stats->bldngs, types[i])
		);
	}
}
void Shop::buyBuilding(int idx, PlayerStats* stats) {
	if (stats->getMoney() - this->bldngsForSale[idx].getCost() < 0)
	{
		return;
	}

	stats->addMoney(-this->bldngsForSale[idx].getCost());
	stats->bldngs.emplace_back(this->bldngsForSale[idx]);

	this->bldngsForSale.erase(this->bldngsForSale.begin() + idx);
}

vector<Building> Shop::getBuildings() {
	return this->bldngsForSale;
}

string Shop::displayShop(PlayerStats* stats) {
	string display;

	display += "===========================================\n";
	display += "                    SHOP\n";
	display += "===========================================\n";
	display += " #  ICON  RARITY   INCOME      COST\n";
	display += "-------------------------------------------\n";

	int number = 0;
	for (auto& bldng : this->bldngsForSale)
	{
		number++;
		display += (
			number < 10 ? " " + to_string(number) + "  " : to_string(number) + "  "
			);

		display += bldng.getIcon() + "     ";

		switch (bldng.getTier())
		{
		case Building::highest:
			display += "&6Highest&0  ";
			break;
		case Building::high:
			display += "&5High&0     ";
			break;
		case Building::mid:
			display += "&4Mid&0      ";
			break;
		case Building::low:
			display += "&3Low&0      ";
			break;
		case Building::lowest:
			display += "&1Lowest&0   ";
			break;
		}

		int maxIncomeLength = 10;
		int incomeLength = 0;
		if (bldng.getType() == Building::decoration)
		{
			incomeLength = (int)to_string(bldng.getIncomeMax()).length() + 1;
			display += "$-" + to_string(bldng.getIncomeMax());
		}
		else
		{
			incomeLength = (int)to_string(bldng.getIncomeMax()).length();
			display += "$" + to_string(bldng.getIncomeMax());
		}
		for (int i = 0; i < (maxIncomeLength - incomeLength); i++)
		{
			display += " ";
		}
		display += " ";

		int maxCostLength = 10;
		int costLength = (int)to_string(bldng.getCost()).length();
		display += "$" + to_string(bldng.getCost());
		for (int i = 0; i < (maxCostLength - costLength); i++)
		{
			display += " ";
		}
		display += " \n";
	}

	display += "-------------------------------------------\n";
	display += "[Your balance: $" + to_string(stats->getMoney()) + "]\n\n";
	display += "Commands: \n";
	display += " - Type &1buy&0 and the number of the item to\n";
	display += "buy it\n";
	display += " - Type &1shopinfo&0 and the number of the\n";
	display += "item to display information about it\n";
	display += " - Type &1view&0 to go to city view\n";
	display += "===========================================\n";

	return display;
}