#include "building.h"

#include "rnd.h"
#include "formater.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

const char icons[4] = { 'H', 'S', 'I', 'D' };
vector<pair<building::tiers, double>> tierChances = {
	{building::highest, 0.01},
	{building::high, 0.05},
	{building::mid, 0.10},
	{building::low, 0.5},
	{building::lowest, 1.0},
};
map<building::tiers, pair<int, int>> populationRanges = {
	{building::highest, {500, 1000}},
	{building::high, {100, 500}},
	{building::mid, {50, 100}},
	{building::low, {20, 50}},
	{building::lowest, {10, 20}}
};
map<building::tiers, pair<int, int>> costRanges = {
	{building::highest, {50000, 100000}},
	{building::high, {20000, 50000}},
	{building::mid, {10000, 20000}},
	{building::low, {5500, 10000}},
	{building::lowest, {1000, 5500}}
};

building::building(vector<building>* buildings, char newIcon, types newType)
	: bldngs(buildings), icon(newIcon), type(newType)
{
	for (auto costTierPair : costRanges)
	{
		building::tiers costTier = costTierPair.first;
		pair<int, int> costRange = costTierPair.second;

		if (costTier == this->tier)
		{
			cost = formater::niceNumber(rnd::getRandInt(costRange.first, costRange.second));
		}
	}
}

void building::setPosition(string newPos) {
	this->position = newPos;
}
void building::setCost(int newCost) {
	this->cost = newCost;
}
void building::setIncomeMax(int newIncomeMax)
{
	this->incomeMax = newIncomeMax;
}
void building::setPopulation(int newPopulation)
{
	this->population = newPopulation;
}
void building::setPopulationMax(int newPopulationMax)
{
	this->populationMax = newPopulationMax;
}
void building::setType(types newType)
{
	this->type = newType;
}
void building::setTier(building::tiers newTier)
{
	this->tier = newTier;
}


building::tiers building::getTier()
{
	return this->tier;
}
building::types building::getType()
{
	return this->type;
}
int building::getCost()
{
	return this->cost;
}
int building::getSell()
{
	return this->sellValue;
}
int building::getIncome()
{
	return this->income;
}
int building::getIncomeMax()
{
	return this->incomeMax;
}
int building::getPopulation()
{
	return this->population;
}
int building::getPopulationMax()
{
	return this->populationMax;
}
vector<building>* building::getBldngs()
{
	return this->bldngs;
}
string building::getPosition() 
{
	return this->position;
}
string building::getIcon()
{
	string newIcon;

	string colorTiers[] = {
		"&0", "&3",
		"&4", "&5",
		"&6"
	};
	newIcon += colorTiers[this->tier];
	newIcon += this->icon;
	newIcon += "&0";

	return newIcon;
}
string building::getName()
{
	string newName = this->name;

	if (this->name.length() > 22)
	{
		newName = this->name.substr(0, 19);
		newName += "...";
	}

	return newName;
}
string building::getDescription()
{
	updateAll();
	string description;
	description += "===========================================\n";
	description += "                DESCRIPTION\n";
	description += "===========================================\n";
	description += " ICON  RARITY     BUILDING TYPE  BUY COST\n";
	description += "-------------------------------------------\n";
	description += " " + this->getIcon() + "   ";
	switch (getTier())
	{
	case highest:
		description += "  &6Highest&0  ";
		break;
	case high:
		description += "  &5High&0     ";
		break;
	case mid:
		description += "  &4Mid&0      ";
		break;
	case low:
		description += "  &3Low&0      ";
		break;
	case lowest:
		description += "  &1Lowest&0   ";
		break;
	}
	switch (getType())
	{
	case residential:
		description += "  Residential  ";
		break;
	case comercial:
		description += "  Comercial    ";
		break;
	case industrial:
		description += "  Industrial   ";
		break;
	case decoration:
		description += "  Decoration   ";
		break;
	}
	description += "  $" + to_string(getCost()) + "\n";
	description += "\n";
	description += "===========================================\n";
	description += " SELL COST    ";
	if (getType() == residential)
	{
		description += "DAILY INCOME    POPULATION\n";
	}
	else if (getType() == decoration)
	{
		description += "DAILY COST\n";
	}
	else
	{
		description += "DAILY INCOME\n";
	}
	description += "-------------------------------------------\n";

	// SELL
	description += " $";
	string sellText = to_string(getSell());
	description += sellText;
	for (int i = 0; i < 10 - (int)sellText.length(); i++)
	{
		description += " ";
	}
	// DAILY INCOME
	if (getType() != decoration)
	{
		description += "  ";
		string dailyIncomeText = "$" + to_string(getIncome()) + "/" + to_string(getIncomeMax());
		description += formater::formatText(dailyIncomeText, 14, "..");
		for (int i = 0; i < 14 - (int)dailyIncomeText.length(); i++)
		{
			description += " ";
		}
	}
	else if (getType() == decoration)
	{
		description += "  ";
		string dailyCostText = "$" + to_string(getIncome());
		description += dailyCostText;
	}
	// OTHER
	if (getType() == residential)
	{
		description += "  ";
		string populationText = to_string(getPopulation()) + "/" + to_string(getPopulationMax());
		description += populationText;
		for (int i = 0; i < 16 - (int)populationText.length(); i++)
		{
			description += " ";
		}
	}

	description += "\n-------------------------------------------\n";
	description += "Commands: \n";
	description += " - Type &1inv&0 to show inventory\n";
	description += " - Type &1shop&0 to show shop\n";
	description += " - Type &1view&0 to go to city\n";
	description += "===========================================\n";

	return description;
}

void building::updatePopulation()
{
	map<types, int> ammounts;
	for (building b : *bldngs)
	{
		ammounts[b.getType()] += 1;
	}

	if ((int)ammounts.size() == 0 || this->position.empty())
	{
		this->population = 0;
		return;
	}

	double tierTolerances[] = { 2.0, 1.5, 1.0, 0.75, 0.5 };
	double tierTolerance = tierTolerances[this->tier];

	int lostPopulation = 0;
	if (ammounts[comercial] > ammounts[residential] * (this->comTolerance * tierTolerance))
	{
		double tolerance = this->comTolerance * tierTolerance;
		lostPopulation += ammounts[comercial] - (int)round(ammounts[residential] * tolerance);
	}
	if (ammounts[industrial] > ammounts[residential] * (this->indTolerance * tierTolerance))
	{
		double tolerance = this->comTolerance * tierTolerance;
		int indLostPop = ammounts[industrial] - (int)round(ammounts[residential] * tolerance);
		lostPopulation = (lostPopulation < indLostPop) ? indLostPop : lostPopulation;
	}
	if (ammounts[decoration] > 0)
	{
		lostPopulation -= (int)round(ammounts[decoration] / getBldngs()->size());
	}

	this->population = (int)round(this->populationMax - lostPopulation);

	if (this->population > this->populationMax)
	{
		this->population = this->populationMax;
	}
	else if (this->population < 0)
	{
		this->population = 0;
	}
}
void building::updateCost()
{
	for (auto costTierPair : costRanges)
	{
		tiers costTier = costTierPair.first;
		pair<int, int> costRange = costTierPair.second;

		if (costTier == this->tier)
		{
			this->cost = formater::niceNumber(rnd::getRandInt(costRange.first, costRange.second));
			this->sellValue = formater::niceNumber((int)round(cost * rnd::getRandDouble(0.25, 0.75)));
		}
	}
}
void building::updateIncome()
{
	double incomePercent = 1.0;
	if (this->type == residential)
	{
		if (this->population == 0)
		{
			incomePercent = 0.0;
		}
		else
		{
			incomePercent = (double)this->population / (double)this->populationMax;
		}
	}
	else if (this->type == decoration)
	{
		incomePercent = -1.0;
	}
	this->income = formater::niceNumber((int)(round(this->incomeMax * incomePercent)));
}
void building::updateAll()
{
	if (this->type == residential)
	{
		updatePopulation();
	}
	updateCost();
	updateIncome();
}

building::tiers building::getRndTier(vector<pair<tiers, double>> chances)
{
	while (true) {
		for (int i = 0; i < (int)chances.size(); i++)
		{
			double roll = rnd::getRandDouble(0.0, 1.0);
			if (roll < chances[i].second)
			{
				return chances[i].first;
			}
		}
	}
}
building building::getRndBldng(std::vector<building>* bldngs, types bldngType)
{
	building bldng = { bldngs, icons[bldngType], bldngType };

	bldng.setTier(getRndTier(tierChances));

	bldng.updateCost();

	if (bldng.type == residential)
	{
		tiers bldngTier = bldng.getTier();
		int newPopulationMax = rnd::getRandInt(populationRanges[bldngTier].first, populationRanges[bldngTier].second);
		bldng.setPopulationMax(formater::niceNumber(newPopulationMax));
	}
	double minIncome = 0.25, maxIncome = 0.5;
	if (bldng.getType() == decoration)
	{
		minIncome = 0.125;
		maxIncome = 0.25;
	}
	int newIncomeMax = (int)round((double)bldng.getCost() * rnd::getRandDouble(minIncome, maxIncome));
	bldng.setIncomeMax(formater::niceNumber(newIncomeMax));

	return bldng;
}