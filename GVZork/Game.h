#ifndef GAME_H
#define GAME_H
#include <map>
#include <string>
#include <vector>
#include <iostream>


#include "GameObject.h"
#include "Item.h"
#include "Location.h"
#include "NPC.h"
#include "Player.h"


class Game {
private:
	std::map < std::string, void(Game::*)(std::vector<std::string>) > commands;
	std::vector<Location> locations;
	Player player;
	int elfCalories;
	bool playGame;



public:
	Game();
	void CreateWorld();
	std::map<std::string, void(Game::*)(std::vector<std::string>)> SetupCommands();
	Location RandomLocation();
	void play();
	void showHelp();
	void talk(NPC npc);
	void meet(std::vector<std::string> target);
	void take(std::vector<std::string> target);
	void give(std::vector<std::string> target);
	void go(std::vector<std::string> target);
	void showItems(std::vector<std::string> target);
	void look(std::vector<std::string> target);
	void quit(std::vector<std::string> target);


	int getElfCalories() const;
	bool getPlayGame() const;


	//void DrawScreen();

	//void GetInput();

	//std::string TokenizeInput();
};



#endif