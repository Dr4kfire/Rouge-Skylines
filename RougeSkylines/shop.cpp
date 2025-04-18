#include "shop.h"

#include "building.h"
#include <vector>
#include <string>

using namespace std;

void shop::updateShop(playerStats* stats) {
	this->bldngsForSale.clear();
	for (int i = 0; i < SELL_AMMOUNT; i++)
	{
		vector<building::types> types = {
			building::residential, building::comercial,
			building::industrial, building::decoration
		};
		this->bldngsForSale.emplace_back(
			building::getRndBldng(&stats->bldngs, types[i])
		);
	}
}
void shop::buyBuilding(int idx, playerStats* stats) {
	if (stats->getMoney() - this->bldngsForSale[idx].getCost() < 0)
	{
		return;
	}

	stats->addMoney(-this->bldngsForSale[idx].getCost());
	stats->bldngs.emplace_back(this->bldngsForSale[idx]);

	this->bldngsForSale.erase(this->bldngsForSale.begin() + idx);
}

vector<building> shop::getBuildings() {
	return this->bldngsForSale;
}

string shop::displayShop(playerStats* stats) {
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
		case building::highest:
			display += "&6Highest&0  ";
			break;
		case building::high:
			display += "&5High&0     ";
			break;
		case building::mid:
			display += "&4Mid&0      ";
			break;
		case building::low:
			display += "&3Low&0      ";
			break;
		case building::lowest:
			display += "&1Lowest&0   ";
			break;
		}

		int maxIncomeLength = 10;
		int incomeLength = 0;
		if (bldng.getType() == building::decoration)
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
