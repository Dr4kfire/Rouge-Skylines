#pragma once

#include <string>
#include <vector>
#include <map>

class building
{
public:
    enum types { residential, comercial, industrial, decoration };
    enum tiers { lowest, low, mid, high, highest };
private:
    types type = residential;
    tiers tier = lowest;

    std::vector<building>* bldngs;

    char icon;
    std::string name, position;

    double comTolerance = 0.5, indTolerance = 0.5;

    int cost = 0, sellValue = 0;
    int income = 0, incomeMax = 0; // incomeBase=0
    int population = 0, populationMax = 0; // populationBase=0

public:
    building(std::vector<building>* buildings, char newIcon, types newType);

    void setPosition(std::string newPos);
    void setCost(int newCost);
    void setIncomeMax(int newIncomeMax);
    void setPopulation(int newPopulation);
    void setPopulationMax(int newPopulationMax);

    void setType(building::types newType);
    void setTier(building::tiers newTier);

    std::string getIcon();
    std::string getName();
    std::string getDescription();
    tiers getTier();
    types getType();
    int getCost();
    int getSell();
    int getIncome();
    int getIncomeMax();
    int getPopulation();
    int getPopulationMax();
    std::vector<building>* getBldngs();
    std::string getPosition();

    void updatePopulation();
    void updateCost();
    void updateIncome();
    void updateAll();

    static building::tiers getRndTier(std::vector<std::pair<tiers, double>> tierChances);

    static building getRndBldng(std::vector<building>* bldngs, types bldngType);
};

