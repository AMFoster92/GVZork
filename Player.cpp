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
    this->updatePlayerItemWeight();
}

void Player::updatePlayerItemWeight()
{
    float itemWeight = 0.0f;
    for (auto it = this->playerItems.begin(); it != this->playerItems.end(); it++)
    {
        itemWeight += it->getWeight();
    }

    this->playerItemWeight = itemWeight; 
}

void Player::setPlayerLoc(Location location)
{
    this->playerLoc = location;
}

void Player::addItem(Item item)
{
    this->playerItems.push_back(item);
}

Item Player::removeItem(Item item)
{
    Item removedItem = item;
    this->playerItems.erase(remove(this->playerItems.begin(), this->playerItems.end(), item), this->playerItems.end());

    return removedItem;
}

float Player::getPlayerItemWeight() const
{
    return this->playerItemWeight;
}

Location Player::getPlayerLoc() const
{
    return this->playerLoc;
}

std::vector<Item> Player::getPlayerItems() const
{
    return this->playerItems;
}
