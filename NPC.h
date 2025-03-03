/*
	Declaration file for the NPC Class
*/

#ifndef NPC_H
#define NPC_H
#include <iostream>
#include <vector>
#include <string> 

#include "Errors.h"

class NPC
{
private:
	std::string name;
	std::string description;
	int messageNumber;
	std::vector<std::string> messages;

public:
	// Default constructor
	NPC();

	// Constructor
	NPC(const std::string name, const std::string description);

	// Copy constructor
	NPC(const NPC& npc);

	// Setters
	void setName(const std::string name);
	void setDescription(const std::string description);
	void setMessages(const std::vector<std::string> messages);

	// Getters
	std::string getName() const;
	std::string getDescription() const;
	std::string getMessage();	// Not const to increment message number
	
	// Helper function
	void incrementMessage();

	// Overloaded Operators
	friend std::ostream& operator<< (std::ostream& os, const NPC npc);
	bool operator== (const NPC npc);

};



#endif
