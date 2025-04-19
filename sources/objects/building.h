#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <vector>

class Building
{
public:
    enum types { residential, comercial, industrial, decoration };
    enum tiers { lowest, low, mid, high, highest };
private:
    types type = residential;
    tiers tier = lowest;

    std::vector<Building>* bldngs;

    char icon;
    std::string name, position;

    double comTolerance = 0.5, indTolerance = 0.5;

    int cost = 0, sellValue = 0;
    int income = 0, incomeMax = 0; // incomeBase=0
    int population = 0, populationMax = 0; // populationBase=0

public:
Building(std::vector<Building>* buildings, char newIcon, types newType);

    void setPosition(std::string newPos);
    void setCost(int newCost);
    void setIncomeMax(int newIncomeMax);
    void setPopulation(int newPopulation);
    void setPopulationMax(int newPopulationMax);

    void setType(Building::types newType);
    void setTier(Building::tiers newTier);

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
    std::vector<Building>* getBldngs();
    std::string getPosition();

    void updatePopulation();
    void updateCost();
    void updateIncome();
    void updateAll();

    static Building::tiers getRndTier(std::vector<std::pair<tiers, double>> tierChances);

    static Building getRndBldng(std::vector<Building>* bldngs, types bldngType);
};

#endif // BUILDING_H