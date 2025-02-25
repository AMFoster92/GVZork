#include "Game.h"

//NEEDS COMMENTS
Game::Game()
{
	this->commands = setupCommands();
	createWorld();
	this->player = Player();
	this->player.setPlayerLoc(randomLocation());
	this->elfCalories = 500;
	this->playGame = true;
}

// NEEDS COMMENTS
void Game::createWorld()
{
	int maxIndexNPC = gameNPC.size() - 1;
	int maxIndexItems = gameItems.size() - 1;
	std::string locName = "";
	Location neighbor = Location();
	std::map < std::string, std::string > dirLocPair = {};

	this->locations = gameLocations;

	// Setup neighbors
	for (auto loc : this->locations)
	{
		// Find map of neighbors for this location
		dirLocPair = locNeighbors.find(loc.getName())->second;

		// Add neighbors to this location
		for (auto pair : dirLocPair)
		{
			// Get the actual Location object for the neighbor
			neighbor = *(std::find(this->locations.begin(), this->locations.end(), pair.second));

			// Add the neighbor to this location
			loc.addLocation(pair.first, neighbor);
		}
	}

	// Randomly distribute items to locations
	for (int i = 0; i < maxIndexItems + 1; i++)
	{
		this->locations[randomNumber(maxIndexItems)].addItem(gameItems[i]);
	}

	// Randomly distribute NPCs to locations
	for (int i = 0; i < maxIndexNPC + 1; i++)
	{
		this->locations[randomNumber(maxIndexNPC)].addItem(gameItems[i]);
	}
}

// NEEDS COMMENTS
std::map<std::string, void(Game::*)(std::vector<std::string>)> Game::setupCommands()
{
	std::map<std::string, void(Game::*)(std::vector<std::string>)> commands;

	commands["help"] = &Game::showHelp;
	commands["talk"] = &Game::talk;
	commands["meet"] = &Game::meet;
	commands["take"] = &Game::take;
	commands["give"] = &Game::give;
	commands["go"] = &Game::go;
	commands["show"] = &Game::showItems;
	commands["look"] = &Game::look;

	return commands;
}

// NEEDS COMMENTS
Location Game::randomLocation()
{
	int maxIndex = this->locations.size() - 1;
	Location randLoc = this->locations[randomNumber(maxIndex)];

	return randLoc;
}

int Game::randomNumber(int rngMax)
{
	int randomVal = -1;

	// Seed mersenne twister with current system time
	std::mt19937 mt(system_clock::now().time_since_epoch().count());

	// Generate uniform distribution over the number of locations
	std::uniform_int_distribution<int> rng(0, (this->locations.size() - 1));

	// Generate random value
	randomVal = rng(mt);

	return randomVal;
}

// NOT DONE, NEEDS COMMENTS
void Game::play(std::vector<std::string> target = {})
{
	this->commands = setupCommands();
}

// NOT DONE, NEEDS COMMENTS
void Game::showHelp(std::vector<std::string> target)
{

	std::string helpMsg = "\t\tGVZork Help Hotline\n";
	helpMsg += "Providing you help with the commands that you need to succeed.\n";
	helpMsg += "Current Time: " + getTimeString();

	helpMsg += "\n\n";

	helpMsg += "\t\tCommand Help\n";
	helpMsg += "Commands can be either a single command word or a command word with a target variable.\n";
	helpMsg += "Target variables are shown below with brackets [] around them. Such as [Item Name]\n";
	helpMsg += "would denote a place holder for the name of an item to interact with.\n";
	helpMsg += "\n\t\tCommand Dictionary\n";

	for (auto com : commandHelp)
	{
		helpMsg += "Command Name: " + com.first + "\n";
		
		// Access inner map
		for (auto comText : com.second)
		{
			helpMsg += "Command Description: " + comText.first + "\n";
			helpMsg += "Command Syntax: " + comText.second + "\n";
		}

		helpMsg += "\n";
	}

	helpMsg += getTimeString() + "\n";


}

// NEEDS COMMENTS
void Game::talk(std::vector<std::string> target = {})
{
	Location playerLoc = this->player.getPlayerLoc();
	std::vector<NPC> locNPC = playerLoc.getNPCs();
	bool found = false;
	for (auto it = locNPC.begin(); it != locNPC.end(); it++)
	{
		if (it->getName() == target[0])
		{
			std::cout << it->getMessage();
			found = true;
		}
	}

	if (!found)
	{
		throw Errors<std::string>::NoMatch("person");
	}
}

// NEEDS COMMENTS
void Game::meet(std::vector<std::string> target = {})
{
	Location playerLoc = this->player.getPlayerLoc();
	std::vector<NPC> locNPC = playerLoc.getNPCs();
	bool found = false;
	for (auto it = locNPC.begin(); it != locNPC.end(); it++)
	{
		if (it->getName() == target[0])
		{
			std::cout << it->getDescription();
			found = true;
		}
	}

	if (!found)
	{
		throw Errors<std::string>::NoMatch("person");
	}
}

// NEEDS COMMENTS
void Game::take(std::vector<std::string> target = {})
{
	Location playerLoc = this->player.getPlayerLoc();
	std::vector<Item> locItems = playerLoc.getItems();
	bool found = false;

	for (auto it = locItems.begin(); it != locItems.end(); it++)
	{
		if (it->getName() == target[0])
		{
			this->player.addItem(*it);
			found = true;
		}
	}

	if (!found)
	{
		throw Errors<std::string>::NoMatch("person");
	}
}

// NEEDS COMMENTS
void Game::give(std::vector<std::string> target = {}) 
{
	Location playerLoc = this->player.getPlayerLoc();
	std::vector<Item> playerItems = this->player.getPlayerItems();
	bool found = false;
	std::string tempStr = "";
	Location randLoc = Location();
	

	for (auto it = playerItems.begin(); it != playerItems.end(); it++)
	{
		if (it->getName() == target[0])
		{
			playerLoc.addItem(this->player.removeItem(*it));

			if (it->getCalories() > 0)
			{
				tempStr = playerLoc.getName();
				std::transform(tempStr.begin(), tempStr.end(), tempStr.begin(), ::tolower);

				if (tempStr == "woods")
				{
					this->elfCalories -= it->getCalories();
					playerLoc.removeItem(*it);
				}
				else
				{
					playerLoc.addItem(this->player.removeItem(*it));
				}
			}
			else
			{
				randLoc = randomLocation();

				while (randLoc.getName() == playerLoc.getName())
				{
					randLoc = randomLocation();
				}

				go({ randomLocation().getName(), "override"});
			}

			found = true;
		}
	}

	if (!found)
	{
		throw Errors<std::string>::NoMatch("person");
	}
}

// NEEDS COMMENTS
void Game::go(std::vector<std::string> target = {})
{
	this->player.getPlayerLoc().setVisited();

	if ((target.size() > 1) or (this->player.getPlayerItemWeight() < 30))
	{
		for (auto loc : this->locations)
		{
			if (loc.getName() == target[0])
			{
				this->player.setPlayerLoc(loc);
				std::cout << "Now traveling to " << loc.getName() << "." << std::endl;
			}
		}
	}
	else
	{
		throw Errors<std::string>::Encumbered();
	}
}

// NEEDS COMMENTS
void Game::showItems(std::vector<std::string> target = {})
{
	std::vector<Item> playerInv = this->player.getPlayerItems();
	
	for (auto it = playerInv.begin(); it != playerInv.end(); it++)
	{
		std::cout << *it << std::endl << std::endl;
	}

	std::cout << "Current Inventory Weight: " << this->player.getPlayerItemWeight() << " lbs" << std::endl;
}

// NEEDS COMMENTS
void Game::look(std::vector<std::string> target = {})
{
	// Calls and prints the return message from the overloaded
	// stream out operator (<<) defined in the Location class. 
	std::cout << this->player.getPlayerLoc() << std::endl;
}

// NEEDS COMMENTS
void Game::quit(std::vector<std::string> target = {})
{
	std::cout << "You would be the kind of person to quit playing this great game." << std::endl;
	this->playGame = false;
}

std::string Game::getTimeString()
{
	// To hold time string stream
	std::ostringstream ts;

	// To hold time string
	std::string timeStr;

	// Get time_point (current point in time) from system clock
	time_point<system_clock> tp(system_clock::now());

	// Convert time_point to time_t to manipulate later
	auto curTime = system_clock::to_time_t(tp);

	// Create static time structure to use threadsafe localtime function
	struct tm timePoint;
	
	// Convert time_t to time structure
	localtime_s(&timePoint, &curTime);

	// Convert time structure into 12-hour am/pm time string stream
	ts << std::put_time(&timePoint, "%r %p");

	// Convert string stream to string
	timeStr = ts.str();

	// Return the time string
	return timeStr;
}

int Game::getElfCalories() const
{
	return this->elfCalories;
}

bool Game::getPlayGame() const
{
	return this->playGame;
}
