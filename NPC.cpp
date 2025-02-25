#include "NPC.h"

NPC::NPC()
{
    this->name = "NoName";
    this->description = "NoDesc";
    this->messageNumber = 0;
    this->messages = {};
}

NPC::NPC(std::string name, std::string description)
{
    setName(name);
    setDescription(description);
    this->messageNumber = 0;
    this->messages = {};
}

void NPC::setName(std::string name)
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

void NPC::setDescription(std::string description)
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

void NPC::setMessages(std::vector<std::string> messages)
{
    this->messages = messages;
}

std::string NPC::getName() const
{
    return this->name;
}

std::string NPC::getDescription() const
{
    return this->description;
}

void NPC::incrementMessage()
{
    this->messageNumber++;
    
    if (this->messageNumber > this->messages.size())
    {
        messageNumber = 1;
    }
}

bool NPC::operator==(const NPC npc)
{
    bool match = false;
    if (this->name == npc.getName())
    {
        match = true;
    }

    return match;
}

std::string NPC::getMessage() const
{
    return this->messages[this->messageNumber];;
}

std::ostream& operator<<(std::ostream& os, const NPC npc)
{
    os << npc.getName();
    return os;
}
