/*
	Declaration file for the Item Class
*/

#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <vector>
#include <iomanip>
#include <sstream>

#include "Errors.h"

extern const int WEIGHT_LOW;
extern const int WEIGHT_HIGH;
extern const int CALORIES_LOW;
extern const int CALORIES_HIGH;

class Item
{
private:
	std::string name;
	int calories;
	std::string description;
	float weight;
public:
	// Default constructor
	Item();

	// Constructor
	Item(std::string name, int calories, 
		std::string description, float weight);

	// Setters
	void setName(const std::string name);
	void setCalories(const int calories);
	void setDescription(const std::string description);
	void setWeight(const float weight);

	// Getters
	std::string getName() const;
	int getCalories() const;
	std::string getDescription() const;
	float getWeight() const;

	// Overloaded operators
	friend std::ostream& operator<< (std::ostream& os, const Item item);
	bool operator== (const Item item);
};

#endif