/*
	Definition file for the Game class
*/

#include "Game.h"

/*
	Game class default constructor
*/
Game::Game()
{
	this->commands = setupCommands();
	createWorld();
	this->elfCalories = 500;
	this->playGame = true;
}

/*
	Uses the constants defined in WorldObjects.cpp to initialize
	the game world and the objects it contains.
*/
void Game::createWorld()
{
	int maxIndexNPC = static_cast<int>(GAME_NPC.size()) - 1;
	int maxIndexItems = static_cast<int>(GAME_ITEMS.size()) - 1;
	// Subtract 2 from size to not populate the Woods
	int maxIndexLoc = static_cast<int>(GAME_LOCATIONS.size()) - 2;
	std::vector<NPC*> gameNPC = {};
	std::string npcName = "";
	std::string locName = "";
	Location* neighbor = new Location();
	std::map < std::string, std::string > dirLocPair = {};

	// Get locations
	for (auto loc : GAME_LOCATIONS)
	{
		// Store a copy
		this->locations.push_back(loc);
	}

	// Get NPCs
	for (auto npc : GAME_NPC)
	{
		// Store a copy
		gameNPC.push_back(new NPC(npc));
		
		// Add NPC messages to NPC
		npcName = gameNPC.back()->getName();
		gameNPC.back()->setMessages(NPC_MESSAGES.at(npcName));
	}

	// Setup neighbors
	for (auto& loc : this->locations)
	{
		// Find map of neighbors for this location
		dirLocPair = LOC_NEIGHBORS.find(loc.getName())->second;

		// Add neighbors to this location
		for (auto dirLoc : dirLocPair)
		{
			// Get the actual Location object for the neighbor
			auto neighbor = std::find_if(this->locations.begin(), this->locations.end(), 
				[&](const Location& curLoc) {return curLoc.getName() == dirLoc.second;});

			// If we found a neighbor
			if (neighbor != this->locations.end())
				
				// Add the neighbor to this location
				loc.addLocation(dirLoc.first, *neighbor);
		}
	}

	// Randomly distribute items to locations
	for (int i = 0; i < maxIndexItems + 1; i++)
	{
		this->locations[randomNumber(maxIndexLoc)].addItem(GAME_ITEMS[i]);
	}

	// Randomly distribute NPCs to locations
	for (int i = 0; i < maxIndexNPC + 1; i++)
	{
		this->locations[randomNumber(maxIndexLoc)].addNPC(gameNPC[i]);
	}

	this->player.setPlayerLoc(*randomLocation());
}

/*
	Creates map of command strings to associated function pointers.
	Returns the completed map.
*/
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
	commands["quit"] = &Game::quit;
	commands["portal"] = &Game::portal;
	commands["game"] = &Game::game;

	return commands;
}

/* 
	Generates a random location
*/
Location* Game::randomLocation()
{
	// Get the last valid location index
	int maxIndex = static_cast<int>(this->locations.size()) - 1;

	// Get the random location based on the return value of the
	// random number function.
	Location* randLoc = &this->locations[randomNumber(maxIndex)];

	// Return the new location
	return randLoc;
}

/*
	Generates a random number from 0 to rngMax using
	the Mersenne twister algorithm.
*/
int Game::randomNumber(const int rngMax)
{
	int randomVal = -1;

	// Seed Mersenne twister with current system time
	std::mt19937 mt(std::chrono::system_clock::now().time_since_epoch().count());

	// Generate uniform distribution over the number of locations
	std::uniform_int_distribution<int> rng(0, rngMax);

	// Generate random value
	randomVal = rng(mt);

	return randomVal;
}

/*
	The core game loop that gets input from the player
	and determines what function to call. At the end it
	checks if the win condition has been met.
*/
void Game::play(std::vector<std::string> target = {})
{
	static bool gameStart = true;		// Static value indicating first call of play
	std::string rawInput = "";			// The raw input from player
	std::vector<std::string> inputTokens = {};	// Collection of tokens from input
	std::string command = "";			// Command token from inputTokens

	// If this is the start of the game
	if (gameStart)
	{
		// It is no longer the start of the game
		gameStart = false;

		// Print start game message
		std::cout << START_MESSAGE << std::endl;
	}

	// Get player input
	std::cout << "Enter command: (Type help to see command information)\n";
	std::getline(std::cin, rawInput);

	// Tokenize player input string
	inputTokens = tokenizeString(rawInput, ' ');

	// If the input was not blank
	if (!inputTokens.empty())
	{
		// The command is always the first token
		command = inputTokens[0];

		// Remove the command from the collection of tokens
		inputTokens.erase(inputTokens.begin());
	}

	try 
	{
		// Is there a command and is it valid?
		if (!command.empty() and 
			std::any_of(this->commands.begin(), this->commands.end(), 
			[&](const auto& cmd) {return cmd.first == command; }))
		{
			// Valid command, call it's associated function
			(this->*commands[command])(inputTokens);
		}
		else
		{
			// Invalid command was entered
			throw Errors<std::string>::InvalidCommand();
		}
	}
	// Catches any exceptions, could be done better
	// but most errors thrown are non-fatal errors
	catch (...)
	{

	}

	// Check if game is over
	if (this->elfCalories <= 0)
	{
		// Game is over
		this->playGame = false;
		std::cout << "You did it! The school is saved!" << std::endl;
	}
}

/*
	Displays the help information to the player.
*/
void Game::showHelp(std::vector<std::string> target)
{
	std::string helpMsg = "\nGVZork Help Hotline\n";
	helpMsg += "Providing the help you need for the commands to succeed.\n";
	helpMsg += "Current Time: " + getTimeString();

	helpMsg += "\n\n";

	helpMsg += "Command Help\n";
	helpMsg += "Commands can be either a single command word or a command"
				"word with a target variable.\n";
	helpMsg += "Target variables are shown below with brackets [] around "
				"them. Such as [Item Name]\n";
	helpMsg += "would denote a place holder for the name of an item to "
				"interact with.\n";
	helpMsg += "Example to go North enter: go north\n";
	helpMsg += "\nCommand Dictionary\n";

	for (auto com : COMMAND_HELP)
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

	std::cout << helpMsg << std::endl;
}

/*
	Prints a message from the target NPC in the player's current location.
	Checks if the NPC exists in the player's current location.
*/
void Game::talk(std::vector<std::string> target = {})
{
	// Pointer to player's current location
	Location* playerLoc = this->player.getPlayerLoc();
	// Collection of NPCs in player's current location
	std::vector<NPC*> locNPC = playerLoc->getNPCs();
	// Flag to indicate if target NPC found in player's current location
	bool found = false;

	// Iterate through the local NPCs
	for (auto it : locNPC)
	{
		// Compare current NPC name with target NPC name
		// Lowercase strings used for case insensitivity
		if (strToLower(it->getName()) == strToLower(target[0]))
		{
			// Print the current message from the NPC
			std::cout << "\n" << it->getMessage() << std::endl;

			// Set the flag indicating the NPC was found
			found = true;
		}
	}

	// If the NPC wasn't found
	if (!found)
	{
		// Throw an error to print a message saying so.
		throw Errors<std::string>::NoMatch("person");
	}
}

/*
	Searches for the target NPC in the player's current location
	and prints their description if found.
*/
void Game::meet(std::vector<std::string> target = {})
{
	// Pointer to player's current location
	Location* playerLoc = this->player.getPlayerLoc();

	// Collection of NPCs in player's current location
	std::vector<NPC*> locNPC = playerLoc->getNPCs();

	// Flag to indicate if NPC was found in player's current location
	bool found = false;

	// Iterate through the NPCs in the current location
	for (auto it : locNPC)
	{
		// Compare name of current NPC to target name
		// Use lowercase strings for case-insensitivity
		if (strToLower(it->getName()) == strToLower(target[0]))
		{
			// NPC found, print it's description
			std::cout << "\n" << it->getDescription() << std::endl;
			found = true;
		}
	}

	// If we didn't find the NPC
	if (!found)
	{
		// Throw an error to print a message saying so
		throw Errors<std::string>::NoMatch("person");
	}
}

/*
	Takes matching item from player's current location
	and adds it to their inventory.
*/
void Game::take(std::vector<std::string> target = {})
{
	// Player's current location
	Location* playerLoc = this->player.getPlayerLoc();
	// Items located at player's current location
	std::vector<Item> locItems = playerLoc->getItems();
	// Flag to indicate if item was found in player's current location
	bool found = false;

	// Iterate through the items in player's current location
	for (auto it : locItems)
	{
		// Check if current item name matches target item name
		// Use lower case string for case insensitive comparison
		if (strToLower(it.getName()) == strToLower(target[0]))
		{
			this->player.addItem(it);
			this->player.getPlayerLoc()->removeItem(it);
			std::cout << "\nPicking up " << it.getName() << std::endl;
			found = true;
		}
	}

	// If the item wasn't found
	if (!found)
	{
		// Throw an error to print a message saying so
		throw Errors<std::string>::NoMatch("item");
	}
}

/*
	Leaves an item in the current location.
	If the item is edible and the player is in the woods, it feeds the elf.
	If the item is not edible, the player is teleported to a random location.
*/
void Game::give(std::vector<std::string> target = {}) 
{
	// Player's current location
	Location* playerLoc = this->player.getPlayerLoc();
	// Items in the player's inventory
	std::vector<Item> playerItems = this->player.getPlayerItems();
	// Flag to indicate the item was found in the player's inventory
	bool found = false;
	// Random location intialized with default constructor
	Location* randLoc = new Location();
	
	// Iterate through items in the player's inventory
	for (auto it : playerItems)
	{
		// Compare the current item name and target item name
		// Uses lowercase comparison for case insensitivity
		if (strToLower(it.getName()) == strToLower(target[0]))
		{
			// Add the item to the player's current location
			playerLoc->addItem(it);
			// Remove the item from the player's inventory
			this->player.removeItem(it);

			std::cout << "\nGave " << it.getName() << std::endl;

			// Is this edible?
			if (it.getCalories() > 0)
			{
				// Is the player in the woods?
				if (strToLower(playerLoc->getName()) == "woods")
				{
					// Subtract the item calories from the elf's calories
					this->elfCalories -= it.getCalories();

					// Remove the item from the player's current location
					playerLoc->removeItem(it);
				}
			}
			// The item is not edible
			else
			{
				// Was the inedible item dropped in the woods?
				if (strToLower(playerLoc->getName()) == "woods")
				{
					// Get a random location
					randLoc = randomLocation();

					// Make sure it's not the player's current location
					while (randLoc->getName() == playerLoc->getName())
					{
						// Get a new random location
						randLoc = randomLocation();
					}

					// Change the player's location to the random location
					this->player.setPlayerLoc(*randLoc);

					// Print a message telling them where they are going
					std::cout << "You have angered Elfo with your inedible trash.\n"
						"A mysterious energy overwhelms you and"
							  "transports you to " << randLoc->getName()\
						<< "." << std::endl;
				}
			}

			// Set the flag indicating the item was found
			found = true;
		}
	}

	// Was the item found?
	if (!found)
	{
		// Throw an error to print a message telling them it was not
		throw Errors<std::string>::NoMatch("item");
	}
}

/*
	Change the player's current location based on a direction.
	Checks that a valid direction has been provided, the player is 
	not overburdened.
*/
void Game::go(std::vector<std::string> target = {})
{
	// The player's current location
	Location* playerLoc = this->player.getPlayerLoc();
	// Map of neighbors to the player's current location
	std::map<std::string, Location*> locNeighbors = playerLoc->getNeighbors();
	// Flag to indicate destination location found
	bool found = false;

	// Set player's current location to visited
	this->player.getPlayerLoc()->setVisited();
	
	// Is there a target destination?
	if (target.size() > 0)
	{
		// Is the player carrying too much to travel?
		if (this->player.getPlayerItemWeight() < 30)
		{
			// Iterate through all possible neighbors
			for (auto dir : locNeighbors)
			{
				// Check if target location matches the current location's name
				// Uses lower case strings for case insensitive comparison
				if (strToLower(dir.first) == strToLower(target[0]))
				{
					// The names match, set found flag
					found = true;

					// Change player's current location to target location
					this->player.setPlayerLoc(*dir.second);

					// Print message showing which location is being traveled to
					std::cout << "\nNow traveling to " << dir.second->getName() << "." \
							  << std::endl;
				}
			}
			// Was the target location found?
			if (!found)
			{
				// Throw an error to print a message saying it was not
				throw Errors<std::string>::NoMatch("location");
			}
		}
		// Player is carrying too much weight to travel
		else
		{
			// Throw an error to print a message saying the player encumbered
			throw Errors<std::string>::Encumbered();
		}
	}
	// No target destination provided
	else
	{
		// Throw an error that prints a message saying so
		throw Errors<std::string>::NoMatch("location");
	}
}

/*
	Prints out a list of the items in the player's inventory
*/
void Game::showItems(std::vector<std::string> target = {})
{
	std::cout << std::endl;
	// Iterate through each item and call it's overloaded
	// stream out operator (<<) defined in the Item class.	
	for (auto it : this->player.getPlayerItems())
	{
		std::cout << it << std::endl << std::endl;
	}

	// Print the total weight carried by the player
	std::cout << "Current Inventory Weight: " << \
		this->player.getPlayerItemWeight() << " lbs" << std::endl;
}

/*
	Calls and prints the return message from the overloaded
	stream out operator (<<) defined in the Location class.
*/
void Game::look(std::vector<std::string> target = {})
{
	std::cout << "\n" << *this->player.getPlayerLoc() << std::endl;
}

/*
	Called when the player exits the game before completing the goal
	and prints a quit message.
*/
void Game::quit(std::vector<std::string> target = {})
{
	std::cout << "\nYou would be the kind of person to quit playing this"
				  "great game.\n" << std::endl;
	this->playGame = false;
}

/*
	Uses the portal gun to transport the player to previously visited regions.
	Checks that the user has the portal gun in their inventory.
*/
void Game::portal(std::vector<std::string> target)
{
	std::vector<Item> playerInv = this->player.getPlayerItems();
	bool hasPortalGun = std::any_of(playerInv.begin(), playerInv.end(), 
		[&](Item item) {return strToLower(item.getName()) == "portal gun";});
	Location* location = new Location();

	if (hasPortalGun)
	{
		location = &(*std::find_if(this->locations.begin(), this->locations.end(),
			[&](Location loc) {return strToLower(loc.getName()) == strToLower(target[0]);}));

		if (location->getVisited())
		{
			this->player.setPlayerLoc(*location);
			std::cout << "\nYou open a portal and travel to " << location->getName() << "." << std::endl;
		}
		else
		{
			throw Errors<std::string>::NoMatch("visited location");
		}
	}
	else
	{
		throw Errors<std::string>::InvalidCommand();
	}
}

/*
	Just a simple game of 21, an offshoot of Blackjack.
	Should have been made into a class and given more functionality.
	Checks that the user has both the Nintendo 3DS and the Golden Nugget
	Casino DS game in their inventory.
*/
void Game::game(std::vector<std::string> target)
{
	std::vector<Item> playerInv = this->player.getPlayerItems();
	bool has3DS = std::any_of(playerInv.begin(), playerInv.end(),
		[&](Item item) {return strToLower(item.getName()) == "nintendo 3ds"; });
	bool hasCasinoGame = std::any_of(playerInv.begin(), playerInv.end(),
		[&](Item item) {return strToLower(item.getName()) == "golden nugget casino ds"; });
	int playerScore = 0;
	int houseScore = 0;
	std::string hitStay = "";
	bool playAgain = true;
	
	if (has3DS and hasCasinoGame)
	{
		std::cout << "\nNow loading 21..." << std::endl;

		// Get a number 1 - 10 for the player's starting score
		playerScore += randomNumber(9) + 1;

		// Get a number between 13-21 for the house score
		houseScore = randomNumber(8) + 13;

		while(playAgain)
		{
			if(playerScore < 21)
			{
				std::cout << "\nYour Score: " << playerScore << "\tHouse Score: ?" << std::endl;
				std::cout << "Hit or Stay?" << std::endl;
				std::getline(std::cin, hitStay);
			}

			if (strToLower(hitStay) == "hit" and playerScore < 21)
			{
				// Get a number 1 - 10 and add it to player's current score
				playerScore += randomNumber(9) + 1;
			}
			else if (strToLower(hitStay) == "stay" or playerScore >= 21)
			{
				std::cout << "\nYour Score: " << playerScore << "\tHouse Score: " << houseScore << std::endl;
				if (playerScore > houseScore and playerScore < 22)
				{
					std::cout << "\nYou Won!" << std::endl;
				}
				else if (playerScore == houseScore)
				{
					std::cout << "\nIt's a tie!" << std::endl;
				}
				else
				{
					std::cout << "\nOh no! You lost!" << std::endl;
				}

				std::cout << "Play again? (Y/N)" << std::endl;
				std::getline(std::cin, hitStay);

				if (strToLower(hitStay) == "n")
				{
					playAgain = false;
					std::cout << "\nGoing back to the real world..." << std::endl;
				}
				else if (strToLower(hitStay) == "y")
				{
					std::cout << "\nStarting a new game..." << std::endl;

					// Get a number 1 - 10 for the player's starting score
					playerScore = randomNumber(9) + 1;

					// Get a number between 13-21 for the house score
					houseScore = randomNumber(8) + 13;
				}
				else
				{
					std::cout << "What was that you wanted to do?" << std::endl;
				}
			}
			else
			{
				std::cout << "What was that you wanted to do?" << std::endl;
			}
		}
	}
	else
	{
		throw Errors<std::string>::InvalidCommand();
	}
}

/*
	This function returns the system time as a 12-hour clock
	with the AM/PM designation.
*/
std::string Game::getTimeString()
{
	// To hold time string stream
	std::ostringstream ts;

	// To hold time string
	std::string timeStr;

	// Get time_point (current point in time) from system clock
	std::chrono::time_point<std::chrono::system_clock> tp(std::chrono::system_clock::now());

	// Convert time_point to time_t to manipulate later
	auto curTime = std::chrono::system_clock::to_time_t(tp);

	// Create static time structure to use threadsafe localtime function
	struct tm timePoint;
	
	// Convert time_t to time structure
	localtime_s(&timePoint, &curTime);

	// Convert time structure into 12-hour am/pm time string stream
	ts << std::put_time(&timePoint, "%I:%M %p");

	// Convert string stream to string
	timeStr = ts.str();

	// Return the time string
	return timeStr;
}

/*
	This function takes in a string and returns a copy of it
	that is entirely lower case. This is done this way to 
	preserve the capitalization of the original string.
*/
std::string Game::strToLower(std::string st)
{
	transform(st.begin(), st.end(), st.begin(), ::tolower);

	return st;
}

/* 
	This function tokenizes a string input around the passed in
	delimiting character and returns a vector containing the
	tokenized strings.

	Originally based on the string split example in Starting Out With 
	C++ From Control Structures Through Objects by Tony Gaddis. 
 */
std::vector<std::string> Game::tokenizeString(std::string raw, const char delim)
{
	
	std::vector<std::string> tokens = {};	// The collection of tokens from the string
	std::string token = "";					// Individual tokens as they are generated
	int startPos = 0;						// Starting index
	int delimPos = raw.find(delim);			// Index of the delimiter

	// Make sure input string isn't empty
	if (!raw.empty())
	{
		// Always take first token
		token = raw.substr(startPos, delimPos - startPos);

		// Store command as a lower case string
		transform(token.begin(), token.end(), token.begin(), ::tolower);
		tokens.push_back(token);

		// If there is more to the string, store it as another token
		if (delimPos != std::string::npos)
		{
			startPos = delimPos + 1;
			delimPos = std::string::npos;

			token = raw.substr(startPos, delimPos - startPos);

			// Store remaining token
			tokens.push_back(token);
		}
	}

	// Return the collection of tokens
	return tokens;
}

/*
	This function returns the number of calories the elf still needs to consume
*/
int Game::getElfCalories() const
{
	return this->elfCalories;
}

/*
	This function returns the play state of the game.

	True = Keep playing
	False = End of game
*/
bool Game::getPlayGame() const
{
	return this->playGame;
}
