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


#include "GameObject.h"
#include "Item.h"
#include "Location.h"
#include "NPC.h"
#include "Player.h"

using namespace std::chrono;

class Game {
private:
	std::map < std::string, void(Game::*)(std::vector<std::string>) > commands;
	std::vector<Location> locations;
	Player player;
	int elfCalories;
	bool playGame;

public:
	Game();
	void createWorld();
	std::map<std::string, void(Game::*)(std::vector<std::string>)> setupCommands();
	Location randomLocation();
	int randomNumber(int rngMax);
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
	std::string getTimeString();


	int getElfCalories() const;
	bool getPlayGame() const;
};

const std::vector<Item> gameItems = { Item("testItem", 1, "testItem desc", 0.1f) };
const std::vector<Location> gameLocations = { Location("testLoc", "testLoc desc"), \
											  Location("testLoc2", "testLoc2 desc")};
const std::map<std::string, std::map<std::string, std::string>> locNeighbors = { {"testLoc", {"north", "testLoc2"}}, \
																			  {"testLoc2", { "south", "testLoc"}}};
const std::vector<NPC> gameNPC = { NPC("testNPC", "testNPC desc") };

// {Command, {Description, Syntax}}
const std::map<std::string, std::map<std::string, std::string>> commandHelp = { {"Show Help",{"Shows the help center message", "help"}},
																				{"Talk",{"Talk to an NPC in the current location. ", "talk [NPC Name]"}} };

#endif