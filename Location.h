#ifndef LOCATION_H
#define LOCATION_H
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
/*
	Declaration file for the Location class
*/

#include <string>
#include <algorithm>

#include "NPC.h"
#include "Item.h"
#include "Location.h"
#include "Errors.h"

class Location
{
private:
	std::string name;
	std::string description;
	bool visited;
	std::map<std::string, Location*> neighbors;
	std::vector<NPC*> npcs;
	std::vector<Item> items;

public:
	// Default Constructor
	Location();

	// Constructor
	Location(std::string name, std::string description);
	
	// Setters
	void setName(std::string name);
	void setDescription(std::string description);
	void setVisited();
	void setNeighbors(std::map < std::string, Location*>);
	void setNPCs(std::vector<NPC*> npcs);
	void setItems(std::vector<Item> items);

	// Getters
	std::string getName() const;
	std::string getDescription() const;
	bool getVisited() const;
	std::map<std::string, Location*> getNeighbors() const;
	std::vector<NPC*> getNPCs() const;
	std::vector<Item> getItems() const;

	// Helper functions
	void addLocation(std::string direction, Location& location);
	void addNPC(NPC* npc);
	void addItem(Item item);
	void removeItem(Item item);

	// Overloaded operators
	friend std::ostream& operator<< (std::ostream& os, const Location location);
	bool operator== (const Location location) const;
};

#endif
