/*
    Definition file for the Player class
*/

#include "Player.h"

/*
    Max weight the player can carry before becoming encumbered
*/
const int MAX_WEIGHT = 30;

/*
    Player class default constructor
*/
Player::Player()
{
    this->playerItems = {};
    this->playerItemWeight = 0;
    this->playerLoc = new Location();
}

/*
    Player class constructor
    Takes a vector of Items and an address to a Location object
*/
Player::Player(std::vector<Item> items, Location& loc)
{
    this->playerItems = items; 
    this->playerLoc = &loc;
    this->updatePlayerItemWeight();
}

/*
    Set the player's inventory items to the items vector passed in
*/
void Player::setPlayerItems(const std::vector<Item> items)
{
    this->playerItems = items;
    this->updatePlayerItemWeight();
}

/* 
    Update the player's inventory weight
    Called after adding/removing an item from the player's inventory
*/
void Player::updatePlayerItemWeight()
{
    float itemWeight = 0.0f;
    for (auto it : this->playerItems)
    {
        itemWeight += it.getWeight();
    }

    this->playerItemWeight = itemWeight; 
}

/*
    Set the player's current location to the location passed in
*/
void Player::setPlayerLoc(Location& location)
{
    this->playerLoc = &location;
}

/*
    Adds the passed in item to the player's inventory
    and calls the function to update the player's
    current carrying weight.
*/
void Player::addItem(Item item)
{
    this->playerItems.push_back(item);
    this->updatePlayerItemWeight();
}

/*
    Removes the target item passed in from the player's inventory
    and calls the function to update the player's current carrying 
    weight.
*/
void Player::removeItem(Item item)
{
    this->playerItems.erase(remove(this->playerItems.begin(), 
        this->playerItems.end(), item), this->playerItems.end());
    this->updatePlayerItemWeight();
}

/*
    Returns the player's current carrying weight
*/
float Player::getPlayerItemWeight() const
{
    return this->playerItemWeight;
}

/*
    Returns the player's current location
*/
Location* Player::getPlayerLoc() const
{
    return this->playerLoc;
}

/*
    Returns a vector containing the Items
    in the player's inventory.
*/
std::vector<Item> Player::getPlayerItems() const
{
    return this->playerItems;
}
