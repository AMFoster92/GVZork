/*
	Declaration file for the Player class
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

#include "Item.h"
#include "Location.h"

extern const int MAX_WEIGHT;

class Player
{
private:
	std::vector<Item> playerItems;
	float playerItemWeight;
	Location* playerLoc;

public:
	// Default Constructor
	Player();
	
	// Constructor
	Player(std::vector<Item>, Location&);

	// Setters
	void setPlayerItems(const std::vector<Item> items);
	void setPlayerLoc(Location& location);

	// Getters
	float getPlayerItemWeight() const;
	Location* getPlayerLoc() const;
	std::vector<Item> getPlayerItems() const;

	// Helper functions
	void updatePlayerItemWeight();
	void addItem(Item item);
	void removeItem(Item item);
};

#endif
