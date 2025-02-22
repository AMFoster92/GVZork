#include "Player.h"

Player::Player()
{
    this->playerItems = {};
    this->playerItemWeight = 0;
    this->playerLoc = Location();
}

Player::Player(std::vector<Item> items, Location loc)
{
    this->playerItems = items; 
    this->playerLoc = loc;

    updatePlayerItemWeight();
}

void Player::setPlayerItems(std::vector<Item> items)
{
    this->playerItems = items;
}

void Player::updatePlayerItemWeight()
{
    for (auto it = this->playerItems.begin(); it != this->playerItems.end(); it++)
    {
        this->playerItemWeight += it->getWeight();
    }
}

void Player::setPlayerLoc(Location location)
{
    this->playerLoc = location;
}

int Player::getPlayerItemWeight() const
{
    return this->playerItemWeight;
}

Location Player::getPlayerLoc() const
{
    return this->playerLoc;
}

std::vector<Item> Player::getPlayerItems() const
{
    return this->items;
}
