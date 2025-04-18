#include "raylib.h"

#include "txtFormat.h"
#include "txtInput.h"
#include "playerStats.h"
#include "shop.h"

#include <vector>
#include <map>

using namespace std;

static string createGrid(vector<building> bldngs, const int size[], char emptyIcon = ' ') {
	string grid = "  .  ";
	const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	for (int letter = 0; letter < size[0]; letter++)
	{
		grid += " ";
		grid += ALPHABET[letter];
		grid += "  ";
	}
	grid += "\n";

	for (int v = 0; v < size[1]; v++)
	{
		grid += (v + 1 < 10 ? "  " + to_string(v + 1) + "  " : " " + to_string(v + 1) + "  ");
		for (int h = 0; h < size[0]; h++)
		{
			string slot = " "; slot += emptyIcon; slot += "  ";
			for (building b : bldngs)
			{
				string coordinate = ALPHABET[h] + to_string(v + 1);
				if (b.getPosition() == coordinate)
				{
					slot = " ";
					slot += b.getIcon();
					slot += "  ";
				}
			}
			grid += slot;
		}
		grid += "\n";
	}
	return grid;
} 
string showHelp() {
	string display;
	display += "===========================================\n";
	display += "                    INFO\n";
	display += "===========================================\n";
	display += " CMD        DESCRIPTION\n";
	display += "-------------------------------------------\n";
	display += " &1help&0       - Information about all commands\n";
	display += " &1endday&0     - Ends current day and gathers\n";
	display += "            all income\n";
	display += " &1view&0       - Shows the city\n";
	display += " &1shop&0       - Shop\n";
	display += " &1inv&0        - Inventory\n";
	display += " &1shopinfo <idx>&0 - Shows information about the \n";
	display += "            building from the shop\n";
	display += " &1invinfo <idx>&0 - Shows information about the \n";
	display += "            building from the inventory\n";
	display += " &1buy  <idx>&0 - Buy the <idx> building\n";
	display += " &1sell <idx>&0 - Sell the <idx> building\n";
	display += " &1spos <idx> <pos>&0 - Set the <idx>'s \n";
	display += "            building position to <pos>\n";
	display += "==========================================\n";
	return display;
}
string showShop(shop* Shop, playerStats* stats) {
	string display;
	display = Shop->displayShop(stats);
	return display;
}
string showInventory(playerStats* stats) {
	string display;
	display = stats->displayInventory();
	return display;
}
string showCity(playerStats* stats, const int gridSize[]) {
	string display;
	display += "===========================================\n";
	display += "                CITY VIEW\n";
	display += "===========================================\n";
	// DAY: 2/100 | MONEY: $12345 | SCORE: 645
	display += " DAY: " + to_string(stats->getDay());
	display += "/" + to_string(stats->getDaysMax());
	display += " | MONEY: $" + to_string(stats->getMoney());
	display += " | SCORE: " + to_string(stats->getScore());
	display += "\n-------------------------------------------\n";
	display += "\n";
	display += createGrid(stats->bldngs, gridSize);
	display += "\n-------------------------------------------\n";
	display += " - Type &1help&0 to view all commands\n";
	display += "===========================================\n";
	return display;
}
string showBuildingInfo(vector<building> bldngs, int idx) {
	string display;
	display += bldngs[idx].getDescription();
	return display;
}
void setBuildingPosition(playerStats* stats, int idx, string position)
{
	stats->bldngs[idx].setPosition(position);
}


int main()
{
	Vector2 SCREEN_SIZE = { 800, 600 };
	InitWindow(static_cast<int>(SCREEN_SIZE.x), static_cast<int>(SCREEN_SIZE.y), "Rouge Skylines");
	SetTargetFPS(60);

	txtInput consoleInput(11, SCREEN_SIZE);
	Font monospaced = LoadFont("Peaberry-Mono.otf");

	string display;


	// GAME SETTINGS
	const int GRID_SIZE[2] = { 10, 10 };

	//
	playerStats stats;
	stats.setMoney(10000);
	stats.setDaysMax(100);

	vector<building>* bldngs = &stats.bldngs;

	//
	shop Shop;
	Shop.updateShop(&stats);

	//
	vector<string> commands = {
		"help", "shopinfo", "invinfo", "view",
		"inv", "shop", "buy", "sell", "spos",
		"endday", "reroll"
	};

	display = showCity(&stats, GRID_SIZE);

	while (!WindowShouldClose()) {
		consoleInput.framesCounter++;
		consoleInput.handleInput();
		string textInput;
		if (consoleInput.isInputReady) {
			textInput = consoleInput.getTextInput();
		}
		vector<string> input = txtInput::split(textInput, " ");
		
		if (input[0] == commands[0]) {
			display = showHelp();
		}
		else if (input[0] == commands[1]) {
			vector<building> shopBuildings = Shop.getBuildings();
			string sIndex = input.size() > 1 ? input[1] : 0;
			int idx = stoi(sIndex) - 1;
			if (idx < (int)shopBuildings.size() && idx > -1)
			{
				display = showBuildingInfo(shopBuildings, idx);
			}
			else {
				display = "&7THERE IS NO SUCH BUILDING (index out of range)!&0";
			}
		}
		else if (input[0] == commands[2]) {
			string sIndex = input.size() > 1 ? input[1] : 0;
			int idx = stoi(sIndex) - 1;
			if (idx < (int)stats.bldngs.size() && idx > -1)
			{
				display = showBuildingInfo(stats.bldngs, idx);
			}
			else
			{
				display = "&7THERE IS NO SUCH BUILDING (index out of range)!&0";
			}
		}
		else if (input[0] == commands[3]) {
			display = showCity(&stats, GRID_SIZE);
		}
		else if (input[0] == commands[4]) {
			display = showInventory(&stats);
		}
		else if (input[0] == commands[5]) {
			display = showShop(&Shop, &stats);
		}
		else if (input[0] == commands[6])
		{
			vector<building> shopBuildings = Shop.getBuildings();
			string sIndex = input.size() > 1 ? input[1] : 0;
			int idx = stoi(sIndex) - 1;
			if (idx < (int)shopBuildings.size() && idx > -1)
			{
				if (Shop.getBuildings()[idx].getCost() > stats.getMoney())
				{
					display = "&7YOU DON'T HAVE ENOUGH FUNDS!&0";
				}
				else
				{
					Shop.buyBuilding(idx, &stats);
					display = showShop(&Shop, &stats);
					display += "&0Bought building &6succesfully&0!";
				}
			}
			else
			{
				display = "&7THERE IS NO SUCH BUILDING (index out of range)!&0";
			}
		}
		else if (input[0] == commands[7])
		{
			string sIndex = input.size() > 1 ? input[1] : 0;
			int idx = stoi(sIndex) - 1;
			if (idx < (int)stats.bldngs.size() && idx > -1)
			{
				stats.sellBldng(idx);
				display = showInventory(&stats);
				display += "&0Sold building &6succesfully&0!";
			}
			else
			{
				display = "&7THERE IS NO SUCH BUILDING (index out of range)!&0";
			}
		}
		else if (input[0] == commands[8])
		{
			string sIndex = input.size() > 1 ? input[1] : 0;
			int idx = stoi(sIndex) - 1;
			if (idx < (int)stats.bldngs.size() && idx > -1)
			{
				const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
				char coordX = input[2][0];
				int coordY = stoi(input[2].substr(1, input[2].size()));
				if (coordX >= 'A' && coordX <= ALPHABET[GRID_SIZE[0]] && coordY <= GRID_SIZE[1])
				{
					setBuildingPosition(&stats, idx, input[2]);
					display = "&0Position set &6succesfully&0!";
				}
				else
				{
					display = "&7THERE IS NO SUCH COORDINATE (pos out of range)!&0\n";
					display += "&0use &1view&0 to see all coordinates and buildings";
				}
			}
			else
			{
				display = "&7THERE IS NO SUCH BUILDING (index out of range)!&0";
			}
		}
		else if (input[0] == commands[9])
		{
			stats.advanceDay(1);
			Shop.updateShop(&stats);

			string newDisplay;
			newDisplay += "===========================================\n";
			newDisplay += "                  NEXT DAY\n";
			newDisplay += "===========================================\n";
			newDisplay += "DAY: " + to_string(stats.getDay());
			newDisplay += "/" + to_string(stats.getDaysMax());
			newDisplay += " | MONEY: $" + to_string(stats.getMoney());
			newDisplay += " | SCORE: " + to_string(stats.getScore());
			newDisplay += "\n";
			newDisplay += "-------------------------------------------\n";
			newDisplay += "[Your balance: $" + to_string(stats.getMoney()) + "]\n\n";
			newDisplay += "Commands: \n";
			newDisplay += " - Type &1shop&0 to enter shop\n";
			newDisplay += " - Type &1inv&0 to enter inventory\n";
			newDisplay += " - Type &1view&0 to go to city view\n";
			newDisplay += " - Type &1help&0 to list all commands\n";
			newDisplay += "===========================================\n";
			display = newDisplay;
		}
		else if (input[0] == commands[10])
		{
			Shop.updateShop(&stats);
			display = showShop(&Shop, &stats);
			display += "&0Shop rerolled!";
		}
		else if (input.size() == 0) {
			display = "&7COMMAND NOT FOUND!&0";
		}
		

		BeginDrawing();
		ClearBackground(BLACK);

		txtFormat::drawFormatedString(display, Vector2{0, 0}, monospaced);
		consoleInput.drawInputBox();

		EndDrawing();
	}

	CloseWindow();
}
