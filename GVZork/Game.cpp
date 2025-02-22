#include "Game.h"

Game::Game()
{
	this->commands = SetupCommands();
}

void Game::CreateWorld()
{
}

std::map<std::string, void(Game::*)(...)> Game::SetupCommands()
{
	std::map<std::string, void(Game::*)(...)> commands;

	commands["help"] = showHelp;
	commands["talk"] = talk;
	commands["meet"] = meet;
	commands["take"] = take;
	commands["give"] = give;
	commands["go"] = go;
	commands["show"] = showItems;
	commands["look"] = look;

	return commands;
}

Location Game::RandomLocation()
{
	return Location();
}

void Game::play()
{
}

void Game::showHelp()
{
}

void Game::talk(NPC npc)
{
	Location playerLoc = this->player.getPlayerLoc();
	std::vector<NPC> locNPC = playerLoc.getNPCs();
	auto it = std::find(locNPC.begin(), locNPC.end(), npc);

	if (it != locNPC.end())
	{
		it->getMessage();
	}
	else
	{
		std::cout << "There is no one here by that name." << std::endl;
	}
}

void Game::meet(std::vector<std::string> target)
{

}

void Game::take(std::vector<std::string> target)
{
}

void Game::give(std::vector<std::string> target)
{
}

void Game::go(std::vector<std::string> target)
{
}

void Game::showItems(std::vector<std::string> target)
{
}

void Game::look(std::vector<std::string> target)
{
}

void Game::quit(std::vector<std::string> target)
{
}

int Game::getElfCalories() const
{
	return this->elfCalories;
}

bool Game::getPlayGame() const
{
	return this->playGame;
}
