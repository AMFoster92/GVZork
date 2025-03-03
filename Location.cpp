/*
	Definition file for the Location class
*/

#include "Location.h"

/*
	Location class default constructor
*/
Location::Location()
{
	this->name = "NoName";
	this -> description = "NoDesc";
	this->visited = false;
	this->neighbors = {};
	this->npcs = {};
	this->items = {};
}

/*
	Location constructor
	Takes a name string, and description string.
*/
Location::Location(std::string name, std::string description)
{
	this->name = name;
	this->description = description;
	this->visited = false;
	this->neighbors = {};
	this->npcs = {};
	this->items = {};
}

/*
	Sets the Location's name to the name string passed in
*/
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

/*
	Sets the Location's description to the description string passed in
*/
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

/*
	Sets the Location's visited flag
*/
void Location::setVisited()
{
	this->visited = true;
}

/*
	Sets the Location's neighbors to the neighbors map passed in
*/
void Location::setNeighbors(std::map<std::string, Location*> neighbors)
{
	this->neighbors = neighbors;
}

/*
	Sets the Location's NPC vector to the npcs vector passed in.
*/
void Location::setNPCs(std::vector<NPC*> npcs)
{
	this->npcs = npcs;
}

/*
	Sets the Location's item vector to the items vector passed in.
*/
void Location::setItems(std::vector<Item> items)
{
	this->items = items;
}

/*
	Returns the Location's name
*/
std::string Location::getName() const
{
	return this->name;
}

/*
	Returns the Location's description string
*/
std::string Location::getDescription() const
{
	return this->description;
}

/*
	Returns the Location's visited flag
*/
bool Location::getVisited() const
{
	return this->visited;
}

/*
	Returns the Location's neighbors map
*/
std::map<std::string, Location*> Location::getNeighbors() const
{
	return this->neighbors;
}

/*
	Returns the Location's vector of NPCs
*/
std::vector<NPC*> Location::getNPCs() const
{
	return this->npcs;
}

/*
	Returns the Location's vector of Items
*/
std::vector<Item> Location::getItems() const
{
	return this->items;
}

/*
	Adds the direction string and Location pointer pair to the Location's
	map of neighbors
*/
void Location::addLocation(std::string direction, Location& location)
{
	this->neighbors[direction] = &location;
}

/*
	Adds the passed in npc to the Location's vector of NPCs
*/
void Location::addNPC(NPC* npc)
{
	this->npcs.push_back(npc);
}

/*
	Adds the passed in item to the Location's vector of Items
*/
void Location::addItem(Item item)
{
	this->items.push_back(item);
}

/*
	Removes the target item passed in from the Location's vector of items
*/
void Location::removeItem(Item item)
{
	// Call to remove() finds the item and moves it to the end of the vector
	// Call to erase() actually deletes the item from memory
	this->items.erase(remove(this->items.begin(), this->items.end(), item), 
					                                      this->items.end());
}

/*
	Overloaded outstream operator to print the Location's information
*/
std::ostream& operator<<(std::ostream& os, const Location location)
{
	// Output message
	std::string message = "";
	// Output string stream to return output message
	std::ostringstream outStream;
	// Vector of NPCs in the location passed in
	std::vector<NPC*> npcs = location.getNPCs();
	// Vector of Items in the location passed in
	std::vector<Item> items = location.getItems();
	// Map of neighbors for the location passed in
	std::map<std::string, Location*> neighbors = location.getNeighbors();

	// Add location description to the message
	message += location.getName() + " - " + location.getDescription() + "\n";

	// Are there any NPCs in the location?
	if (npcs.size() > 0)
	{
		message += "\nYou see the following NPCs:\n";

		// Iterate through the location's NPCs and add their
		// string output to the output message
		for (auto it : npcs)
		{
			outStream << "\t- " << *it << std::endl;
			message += outStream.str();

			// Set the output string stream to an empty string
			outStream.str("");
			// Clear any flags on the output string stream
			outStream.clear();
		}
	}
	// There are no NPCs here
	else
	{
		message += "\nYou are alone.\n";
	}

	message += "\n";

	// Are there any items in the location?
	if (items.size() > 0)
	{
		message += "You see the following Items:\n";

		// Iterate through the location's items and add their
		// string output to the output message
		for (auto it : items)
		{
			outStream << "\t- " << it << std::endl;
			message += outStream.str();

			// Set the output string stream to an empty string
			outStream.str("");
			// Clear any flags on the output string stream
			outStream.clear();
		}
	}
	// There are no items in this location
	else
	{
		message += "There are no items here.\n";
	}
	message += "\n";

	message += "You can go in the following Directions:\n";

	// Iterate through the location's neighbors and add
	// their direction and name to the output message
	for (auto it : neighbors)
	{
		message += "\t- " + it.first + " - ";

		// Has the neighbor in the current direction been visited?
		if (it.second->getVisited())
		{
			// Print it's name and visited status
			message += it.second->getName() + " (Visited)";
		}
		else
		{
			message += "Unknown";
		}

		message += "\n";
	}

	// Send the output message to the output stream
	os << message;

	// Return the output stream
	return os;
}

/*
	Overloaded comparison operator to compare Locations
*/
bool Location::operator==(const Location location) const
{
	bool match = false;

	if (this->name == location.getName())
	{
		match = true;
	}

	return match;
}