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
	NPC();
	NPC(std::string name, std::string description);

	void setName(std::string name);
	void setDescription(std::string description);
	void setMessages(std::vector<std::string> messages);

	std::string getName() const;
	std::string getDescription() const;
	std::string getMessage() const;
	
	void incrementMessage();

	friend std::ostream& operator<< (std::ostream& os, const NPC npc);
	bool operator== (const NPC npc);

};



#endif
