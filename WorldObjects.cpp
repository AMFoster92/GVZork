/*
	This file holds constant references to the game objects that will
	be present in the game world. It was done this way to separate the
	game object data from the code that acts on it. This allows new game
	scenarios to be made by simply replacing the contents of this file.
*/

#include <vector>
#include <map>
#include <string>
#include <unordered_map>
#include "Item.h"
#include "Location.h"
#include "NPC.h"


const std::vector<std::string> LOC_NAMES = {
	"Recreation Center", "Laker Store", "Mackinac Hall",
	"Padnos Hall of Science", "Student Services Building",
	"Mary Idema Pew Library", "Kirkhof Center", "Lake Superior Hall",
	"Woods" };

// { Item( Name, Calories, Description, Weight)}
extern const std::vector<Item> GAME_ITEMS = { 
	Item("Bacon", 86, "It's a shame what happened to Wilbur. He tastes so good though. ", 1.0f),

	Item("Kombucha", 30, "A fizzy, fermented drink made from tea, sugar, and yeast.", 2.5f), 

	Item("Nintendo 3DS", 0, "You don't know it yet, but Nintendo is going to sabotage this in 2024.", 0.5f),

	Item("Portal Gun", 0, "The cake is a lie. This portable portal generator" 
		" allows you to travel to any visited location.", 10.0f),

	Item("Standard Notebook", 0, "Are you even going to use this thing?", 0.5f),

	Item("Hot Dog", 151, "A well cooked sausage that will later be called a glizzy for some reason.", 1.0f), 

	Item("Monster Energy Drink", 101, "We get it Kyle, you hate dry wall.", 1.2f),

	Item("Beans", 42, "The breakfast of champion gunslingers and a magical fruit.", 1.0f), 

	Item("Pop Tart", 197, "Pumpkin Pie flavored for Halloween 2011.", 0.2f),

	Item("Golden Nugget Casino DS", 0, "Gambling? In this economy?! Oh, it's fake.", 0.2f) };

// { Location( Name, Description)}
extern const std::vector<Location> GAME_LOCATIONS = { 
	Location(LOC_NAMES[0], "The hours aren't great, but there's lots of exercise equipment inside."),
	Location(LOC_NAMES[1], "Has the supplies you need to succeed!"),
	Location(LOC_NAMES[2], "Classrooms, labs, and offices. It has it all."),
	Location(LOC_NAMES[3], "Don't buy an RV to use what you learn here to pay off your student loans."),
	Location(LOC_NAMES[4], "Has a collection of services catered to help students through school and beyond."),
	Location(LOC_NAMES[5], "A large library with lots of books and even some helpful services"),
	Location(LOC_NAMES[6], "If you're feeling peckish, this is the place to be."),
	Location(LOC_NAMES[7], "It's not a prison, but it sure feels like one."),
	Location(LOC_NAMES[8], "The home of Elfo the Elf")};

// { Name, {{ Direction, Location}}}
extern const std::map<std::string, std::map<std::string, std::string>> LOC_NEIGHBORS = {
	{LOC_NAMES[0],{{"south", LOC_NAMES[1]},{"east", LOC_NAMES[2]}}},
	{LOC_NAMES[1],{{"north", LOC_NAMES[0]}, {"east",LOC_NAMES[3]}}},
	{LOC_NAMES[2],{{"south", LOC_NAMES[3]}, {"west", LOC_NAMES[0]}}},
	{LOC_NAMES[3],{{"north", LOC_NAMES[2]}, {"south", LOC_NAMES[4]}, {"west", LOC_NAMES[1]}}},
	{LOC_NAMES[4],{{"north", LOC_NAMES[3]}, {"south", LOC_NAMES[5]}}},
	{LOC_NAMES[5],{{"north", LOC_NAMES[4]}, {"east", LOC_NAMES[6]}}},
	{LOC_NAMES[6],{{"west", LOC_NAMES[5]}, {"east", LOC_NAMES[7]}}},
	{LOC_NAMES[7],{{"west", LOC_NAMES[6]}, {"east", LOC_NAMES[8]}}},
	{LOC_NAMES[8],{{"west", LOC_NAMES[7]}}}};

// { NPC( Name, Description)}
extern const std::vector<NPC> GAME_NPC = { 
	NPC("Rango", "An eccentric but heroic chameleon masquerading as a gunslinger."),
	NPC("Nyan Cat", "A flying Pop Tart cat that poops rainbows. Yes, you read that right."),
	NPC("GLaDOS", "An artificial intelligence created by Aperture Science. Be wary of her."),
	NPC("Mr. W", "A friendly seasoned professor brimming with knowledge about computer science and North Carolina."),
	NPC("Professor Ferguson", "A friendly newer professor who is always willing to talk more about computer programming.")};

// { Name, { Greeting, Message,...}
extern const std::map<std::string, std::vector<std::string>> NPC_MESSAGES = { 
	{"Rango",{"I couldn't help but notice you noticing me noticing you.",  
			  "Now, remember son: stay in school, eat your veggies,"
			  " burn everything but Shakespeare.", 
			  "I think the metaphor broke my spleen.",}},

	{"Nyan Cat",{"Nyan nyan nyan?", "Nya nya nya nya nya nya nya nya nya...",
									"... nya nya nya nya nya nya nya nya."}},

	{"GLaDOS",{"Oh... It's you.", "You look great, by the way. Very healthy.", 
			   "It's been fun. Don't come back.", "BECAUSE I'M A POTATO.", 
			   "Seriously, though. Goodbye. "}},

	{"Mr. W",{"Welcome to the class, are you ready to have fun?", 
			  "Hold on, this marker is dead... DUCK!", 
			  "Always remember, variables hold values."}},

	{"Professor Ferguson",{"Hey! How's it going?",
						   "Let me draw an example on the board really quick",
						   "Of course this marker is dead.. I don't want to throw it"
						   " though, my aim isn't that great."}}};

// {Command, {Description, Syntax}}
extern const std::unordered_map<std::string, std::map<std::string, std::string>> COMMAND_HELP = {
	{"Show Help",{{"Shows the help center message", "help"}}}, 
	{"Talk", { {"Talk to an NPC in your current location. ", "talk [NPC Name]"}}},
	{"Meet", { {"Meet an NPC in your current location. ", "meet [NPC Name]"}}},
	{"Take", { {"Take an Item from your current location. ", "take [Item Name]"}}},
	{"Give", { {"Leave an Item in your current location. ", "give [Item Name]"}}},
	{"Go", { {"Go to a new location. ", "go [Direction]"}}},
	{"Show Items", { {"View items in your inventory. ", "show"}}},
	{"Look", { {"Inspect your current location. ", "look"}}},
	{"Quit", { {"Quit the game. ", "quit"}}},
	{"Portal", { {"Teleport to a visited location. ", "portal [Location Name]"}}},
	{"Game", { {"Play a minigame. ", "game"}}}};

extern const std::string START_MESSAGE = "Greetings, Adventurer! GVSU\n"
"has fallen under a curse and needs your help! The Wicked Wizard of the\n"
"West has sent us back to the year 2011 and the pop culture references are\n"
"aging the students! You must go to the Woods and and help Elfo the Elf\n"
"regain his strength to lift this affliction and bring us back to 2025.\n"
"Be warned though, you can fail and be trapped here in the past if you\n"
"don't play your cards right. Also, watch out for arrows, it would be a\n"
"shame to catch one in the knee!\n";

extern const std::vector<std::string> WORD_FILTER = { "the" };