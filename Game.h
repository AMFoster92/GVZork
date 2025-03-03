/*
	Declaration file for the Game Class
*/

#ifndef GAME_H
#define GAME_H
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <unordered_map>

#include "GameObject.h"
#include "Item.h"
#include "Location.h"
#include "NPC.h"
#include "Player.h"

// Constants defined in WorldObjects.cpp
extern const std::vector<Item> GAME_ITEMS;
extern const std::vector<Location> GAME_LOCATIONS;
extern const std::map<std::string, 
	std::map<std::string, std::string>> LOC_NEIGHBORS;
extern const std::vector<NPC> GAME_NPC;
extern const std::unordered_map<std::string, 
	std::map<std::string, std::string>> COMMAND_HELP;
extern const std::string START_MESSAGE;
extern const std::map<std::string, std::vector<std::string>> NPC_MESSAGES;

class Game {
private:
	std::map < std::string, void(Game::*)(std::vector<std::string>) > commands;
	std::vector<Location> locations;
	Player player;
	int elfCalories;
	bool playGame;

public:
	// Default constructor
	Game();

	// Helper functions
	void createWorld();
	std::map<std::string, void(Game::*)(std::vector<std::string>)> setupCommands();
	Location* randomLocation();
	int randomNumber(const int rngMax);
	std::string getTimeString();
	std::string strToLower(std::string st);
	std::vector<std::string> tokenizeString(const std::string raw, 
										    const char delim);

	// Command functions
	void play(std::vector<std::string> target);
	void showHelp(std::vector<std::string> target);
	void talk(std::vector<std::string> target);
	void meet(std::vector<std::string> target);
	void take(std::vector<std::string> target);
	void give(std::vector<std::string> target);
	void go(std::vector<std::string> target);
	void showItems(std::vector<std::string> target);
	void look(std::vector<std::string> target);
	void quit(std::vector<std::string> target);
	void portal(std::vector<std::string> target);
	void game(std::vector<std::string> target);

	// Getters
	int getElfCalories() const;
	bool getPlayGame() const;
};

#endif