#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Item.h"
#include "Location.h"

class Player
{
private:
	std::vector<Item> playerItems;
	int playerItemWeight;
	Location playerLoc;

public:
	Player();
	Player(std::vector<Item>, Location);

	void setPlayerItems(std::vector<Item> items);
	void updatePlayerItemWeight();
	void setPlayerLoc(Location loc);

	int getPlayerItemWeight() const;
	Location getPlayerLoc() const;
	std::vector<Item> getPlayerItems() const;
};

#endif
