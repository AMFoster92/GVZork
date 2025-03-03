/*
    Definition file for the NPC class
*/

#include "NPC.h"

/*
    NPC class default constructor
*/
NPC::NPC()
{
    this->name = "NoName";
    this->description = "NoDesc";
    this->messageNumber = 0;
    this->messages = {};
}

/*
    NPC class constructor
    Takes a string for the name and a string for the description
*/
NPC::NPC(const std::string name, const std::string description)
{
    setName(name);
    setDescription(description);
    this->messageNumber = 0;
    this->messages = {};
}

/*
    NPC class copy constructor
*/
NPC::NPC(const NPC& npc)
{
    this->name = npc.name;
    this->description = npc.description;
    this->messageNumber = npc.messageNumber;
    this->messages = npc.messages;
}

/*
     Set the NPC name to the name string passed in.
*/
void NPC::setName(const std::string name)
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
    Set the NPC description to the description string passed in
*/
void NPC::setDescription(const std::string description)
{
    if (!description.empty())
    {
        this->description = description;
    }
    else
    {
        throw Errors<std::string>::EmptyString("Description");
    }
}

/*
    Set the NPC message vector to the messages vector passed in.
*/
void NPC::setMessages(const std::vector<std::string> messages)
{
    this->messages = messages;
}

/*
    Return the NPC's name
*/
std::string NPC::getName() const
{
    return this->name;
}

/*
    Return the NPC's description
*/
std::string NPC::getDescription() const
{
    return this->description;
}

/*
    Increment the current message number. 
    Called after displaying a message.
*/
void NPC::incrementMessage()
{
    this->messageNumber++;
    
    if (this->messageNumber > this->messages.size()-1)
    {
        // First message is always the initial greeting
        // Roll back to second message to loop regular messages.
        messageNumber = 1;
    }
}

/*
    Overloaded comparison operator to compare NPCs
*/
bool NPC::operator==(const NPC npc)
{
    bool match = false;
    if (this->name == npc.getName())
    {
        match = true;
    }

    return match;
}

/*
    Get the current NPC message and increment the message number.
*/
std::string NPC::getMessage()
{
    std::string message = this->messages[this->messageNumber];
    this->incrementMessage();

    return message;
}

/*
    Overloaded outstream operator to print an NPC
*/
std::ostream& operator<<(std::ostream& os, const NPC npc)
{
    os << npc.getName();
    return os;
}
