/*
    Definition file for the Item Class
*/
#include "Item.h"

const int WEIGHT_LOW = 0;
const int WEIGHT_HIGH = 500;
const int CALORIES_LOW = 0;
const int CALORIES_HIGH = 1000;

/*
    Default Item class constructor
*/
Item::Item()
{
    this->name = "NoName";
    this->description = "NoDesc";
    this->calories = 0;
    this->weight = 0;
}

/*
    Item class constructor
    Takes a name string, calorie integer, description string, weight float.
*/
Item::Item(std::string name="NoName", int calories=0, 
    std::string description="NoDescription", float weight = 0)
{
    this->setName(name);
    this->setCalories(calories);
    this->setDescription(description);
    this->setWeight(weight);
}

/*
    Sets the Item name to the name string passed in.
*/
void Item::setName(const std::string name)
{
    // Is the name string empty?
    if (!name.empty())
    {
        this->name = name;
    }
    // The name string is empty
    else
    {
        // Throw an error to print a message saying so
        throw Errors<std::string>::EmptyString("Name");
    }
}

/*
    Sets the Item calories to the calorie integer value passed in
*/
void Item::setCalories(const int calories)
{
    // Is the value an integer?
    if (typeid(calories).name() == typeid(int).name())
    {
        // Is the value in range?
        if (calories >= CALORIES_LOW and calories <= CALORIES_HIGH)
        {
            this->calories = calories;
        }
        // It is not in range
        else
        {
            // Throw an error to print a message saying so
            throw Errors<int>::OutOfRange("calories", CALORIES_LOW, 
                                                      CALORIES_HIGH);
        }
    }
    // It's not an integer
    else
    {
        // Throw an error to print a message saying so
        throw Errors<int>::TypeError("calories", "int");
    }
}

/*
    Sets the Item description to the description string passed in
*/
void Item::setDescription(const std::string description)
{
    // Is the description a string?
    if (typeid(description).name() == typeid(std::string).name())
    {
        // Is the description string empty?
        if (!description.empty())
        {
            this->description = description;
        }
        // Description string is empty
        else
        {
            // Throw an error to print a message saying so
            throw Errors<std::string>::EmptyString("description");
        }
    }
    // It's not a string
    else
    {
        // Throw an error to print a message saying so
        throw Errors<std::string>::TypeError("description", "string");
    }
}

/*
    Set the Item weight to the weigh float value passed in
*/
void Item::setWeight(const float weight)
{
    // Is this a float?
    if (typeid(weight).name() == typeid(float).name())
    {
        // Is the value in range?
        if (weight >= WEIGHT_LOW and weight <= WEIGHT_HIGH)
        {
            this->weight = weight;
        }
        // Value is outside of range
        else
        {
            // Throw an error and print a message saying so
            throw Errors<float>::OutOfRange("weight", WEIGHT_LOW, 
                                                      WEIGHT_HIGH);
        }
    }
    // It is not a float
    else
    {
        // Throw an error and print a message saying so
        throw Errors<float>::TypeError("weight", "float");
    }
}

/*
    Returns the name string of the item
*/
std::string Item::getName() const
{
    return this->name;
}

/*
    Returns the calorie integer value of the item
*/
int Item::getCalories() const
{
    return this->calories;
}

/*
    Returns the description string of the item
*/
std::string Item::getDescription() const
{
    return this->description;
}

/*
    Returns the weight float value of the item
*/
float Item::getWeight() const
{
    return this->weight;
}

/*
    Overloaded comparison operator to compare Items
*/
bool Item::operator==(const Item item)
{
    bool match = false;

    if (this->name == item.getName())
    {
        match = true;
    }

    return match;
}

/*
    Overloaded outstream operator to print an Item
*/
std::ostream& operator<<(std::ostream& os, const Item item)
{
    std::ostringstream weightFloat;
    weightFloat << std::fixed << std::setprecision(2) << item.getWeight();
    std::string message = item.getName() + " (" + std::to_string(item.getCalories())
        + " calories) - " + weightFloat.str() + " lb - "
        + item.getDescription();

    os << message;

    return os;
}
