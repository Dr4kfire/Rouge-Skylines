#include "playerStats.h"

using namespace std;


void playerStats::setMoney(int value) {
	this->money = value;
}
void playerStats::setDaysMax(int value) {
	this->daysMax = value;
}
void playerStats::setBldngPos(int idx, string newPos, bool override = false) {
	if (!this->bldngs[idx].getPosition().empty() && !override)
	{
		return;
	}

	for (int i = 0; i < (int)this->bldngs.size(); i++)
	{
		if (this->bldngs[idx].getPosition() == newPos && idx != i)
		{
			return;
		}
	}
	this->bldngs[idx].setPosition(newPos);
}

int playerStats::getMoney() {
	return this->money;
}
int playerStats::getMoneyTotal() {
	return this->moneyTotal;
}
int playerStats::getPopulation() {
	return this->population;
}
int playerStats::getPopulationLost() {
	return this->populationLost;
}
int playerStats::getDay() {
	return this->dayCurrent;
}
int playerStats::getDaysMax() {
	return this->daysMax;
}
int playerStats::getScore() {
	return this->score;
}

void playerStats::addMoney(int ammount) {
	this->money += ammount;
	if (ammount > 0)
	{
		this->moneyTotal += ammount;
	}
}
void playerStats::sellBldng(int idx) {
	addMoney(this->bldngs[idx].getSell());
	this->bldngs.erase(this->bldngs.begin() + idx);
}
void playerStats::gatherIncome() {
	int income = 0;
	for (auto& bldng : this->bldngs)
	{
		bldng.updateAll();
		if (!bldng.getPosition().empty())
		{
			income += bldng.getIncome();
		}
	}
	addMoney(income);
}
void playerStats::advanceDay(int ammount)
{
	this->dayCurrent += ammount;
	for (auto& bldng : this->bldngs)
	{
		gatherIncome();
		bldng.updateAll();
	}
}

void playerStats::calculatePopulation() {
	int calcPopulation = 0;
	for (auto& bldng : this->bldngs)
	{
		calcPopulation += bldng.getPopulation();
	}
	this->population = calcPopulation;
}
void playerStats::calculateScore() {
	return;
	for (auto& bldng : this->bldngs)
	{
		return;
	}
}

string playerStats::displayInventory() {
	string display;

	display += "===========================================\n";
	display += "                 INVENTORY\n";
	display += "===========================================\n";
	display += " #  ICON  RARITY   INCOME      SELL VALUE  \n";
	display += "-------------------------------------------\n";

	int number = 0;
	for (auto& bldng : this->bldngs)
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

		int maxSellLength = 10;
		int sellLength = (int)to_string(bldng.getSell()).length();
		display += "$" + to_string(bldng.getSell());
		for (int i = 0; i < (maxSellLength - sellLength); i++)
		{
			display += " ";
		}
		display += " \n";
	}

	display += "-------------------------------------------\n";
	display += "[Your balance: $" + to_string(this->money) + "]\n\n";
	display += "Commands: \n";
	display += " - Type &1sell&0 and the number of the item\n";
	display += "to sell it\n";
	display += " - Type &1invinfo&0 and the number of the item\n";
	display += "to display information about it\n";
	display += " - Type &1view&0 to go to city\n";
	display += "===========================================\n";

	return display;
}