#pragma once

#include "building.h"

class playerStats
{
	int money = 0, moneyTotal = 0;
	int population = 0, populationLost = 0;
	int dayCurrent = 0, daysMax = 0;
	int score = 0;
public:
	std::vector<building> bldngs;

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

