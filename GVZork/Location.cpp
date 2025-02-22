#include "Location.h"

Location::Location()
{
	this->name = "NoName";
	this -> description = "NoDesc";
	this->visited = false;
	this->neighbors = {};
	this->npcs = {};
	this->items = {};
}

Location::Location(std::string name, std::string description)
{
	this->name = name;
	this->description = description;
	this->visited = false;
	this->neighbors = {};
	this->npcs = {};
	this->items = {};
}

void Location::setName(std::string name)
{
	if (!name.empty())
	{
		this->name = name;
	}
	else
	{
		throw Errors<std::string>::EmptyString("Name");
	}
}

void Location::setDescription(std::string description)
{
	if (!name.empty())
	{
		this->description = description;
	}
	else
	{
		throw Errors<std::string>::EmptyString("Description");
	}
}

void Location::setVisited(bool visited)
{
	this->visited = true;
}

void Location::setNeighbors(std::map<std::string, Location> neighbors)
{
	this->neighbors = neighbors;
}

void Location::setNPCs(std::vector<NPC> npcs)
{
	this->npcs = npcs;
}

void Location::setItems(std::vector<Item> items)
{
	this->items = items;
}

std::string Location::getName() const
{
	return this->name;
}

std::string Location::getDescription() const
{
	return this->description;
}

bool Location::getVisited() const
{
	return this->visited;
}

std::map<std::string, Location> Location::getNeighbors() const
{
	return this->neighbors;
}

std::vector<NPC> Location::getNPCs() const
{
	return this->npcs;
}

std::vector<Item> Location::getItems() const
{
	return this->items;
}

std::map<std::string, Location> Location::getLocations()
{
	return std::map<std::string, Location>();
}

void Location::addLocation(std::string direction, Location location)
{
	this->neighbors.insert({ direction, location });
}

void Location::addNPC(NPC npc)
{
	this->npcs.push_back(npc);
}

void Location::addItem(Item item)
{
	this->items.push_back(item);
}

std::ostream& operator<<(std::ostream& os, const Location location)
{
	std::string message = "";
	std::ostringstream outStream;
	std::vector<NPC> npcs = location.getNPCs();
	std::vector<Item> items = location.getItems();
	std::map<std::string, Location> neighbors = location.getNeighbors();

	message += location.getName() + " - " + location.getDescription() + "\n";

	if (npcs.size() > 0)
	{
		message += "You see the following NPCs:\n";

		for (auto it = npcs.begin(); it != npcs.end(); it++)
		{
			outStream << *it;
			message += outStream.str();
		}
	}
	else
	{
		message += "There is nobody here.";
	}


	message += "\n";

	if (items.size() > 0)
	{
		message += "You see the following Items:\n";

		for (auto it = items.begin(); it != items.end(); it++)
		{
			outStream << *it;
			message += outStream.str();
		}
	}
	else
	{
		message += "There are no items here.";
	}
	message += "\n";

	message += "You can go in the following Directions:\n";

	for (auto it = neighbors.begin(); it != neighbors.end(); it++)
	{
		message += "\t- " + it->first + " - ";

		if (it->second.getVisited())
		{
			message += it->second.getName() + "(Visited)";
		}

		message += "\n";
	}

	os << message;

	return os;
}
