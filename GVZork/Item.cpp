#include "Item.h"

Item::Item()
{
    this->name = "NoName";
    this->description = "NoDesc";
    this->calories = 0;
    this->weight = 0;
}

Item::Item(std::string name="NoName", int calories=0, std::string description="NoDescription", float weight = 0)
{
    this->name = name;
    this->calories = calories;
    this->description = description;
    this->weight = weight;
}

void Item::setName(std::string name)
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

void Item::setCalories(int calories)
{
    if (typeid(calories).name() == typeid(int).name())
    {
        if (calories >= CALORIES_LOW and calories <= CALORIES_HIGH)
        {
            this->calories = calories;
        }
        else
        {
            throw Errors<int>::OutOfRange("calories", CALORIES_LOW, CALORIES_HIGH);
        }
    }
    else
    {
        throw Errors<int>::TypeError("calories", "int");
    }
}

void Item::setDescription(std::string description)
{
    if (typeid(description).name() == typeid(std::string).name())
    {
        if (!description.empty())
        {
            this->name = name;
        }
        else
        {
            throw Errors<std::string>::EmptyString("Description");
        }
    }
    else
    {
        throw Errors<std::string>::TypeError("description", "string");
    }
}

void Item::setWeight(float weight)
{
    if (typeid(weight).name() == typeid(float).name())
    {
        if (weight >= 0 and weight <= 500)
        {
            this->weight = weight;
        }
        else
        {
            throw Errors<float>::OutOfRange("weight", WEIGHT_LOW, WEIGHT_HIGH);
        }
    }
    else
    {
        throw Errors<float>::TypeError("weight", "float");
    }
}

std::string Item::getName() const
{
    return this->name;
}

int Item::getCalories() const
{
    return this->calories;
}

std::string Item::getDescription() const
{
    return this->description;
}

float Item::getWeight() const
{
    return this->weight;
}

std::ostream& operator<<(std::ostream& os, const Item item)
{
    std::string message = item.getName() + "(" + std::to_string(item.getCalories()) + " calories - "
        + std::to_string(item.getWeight()) + " lb - " + item.getDescription();

    os << message;

    return os;
}
