#ifndef PLAYER_STATS_H
#define PLAYER_STATS_H

#include "building.h"

class PlayerStats
{
	int money = 0, moneyTotal = 0;
	int population = 0, populationLost = 0;
	int dayCurrent = 0, daysMax = 0;
	int score = 0;
public:
	std::vector<Building> bldngs;

	void setMoney(int value);
	void setDaysMax(int value);

	int getMoney();
	int getMoneyTotal();
	int getPopulation();
	int getPopulationLost();
	int getDay();
	int getDaysMax();
	int getScore();

	void addMoney(int ammount);
	void sellBldng(int idx);
	void setBldngPos(int idx, std::string newPos, bool override);

	void calculatePopulation();
	void calculateScore();

	void gatherIncome();
	void advanceDay(int ammount);

	std::string displayInventory();
};

#endif // PLAYER_STATS_H