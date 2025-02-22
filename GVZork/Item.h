#ifndef ITEM_H
#define ITEM_H
#include <iostream>

#include "Errors.h"

const int WEIGHT_LOW = 0;
const int WEIGHT_HIGH = 500;
const int CALORIES_LOW = 0;
const int CALORIES_HIGH = 1000;

class Item
{
private:
	std::string name;
	int calories;
	std::string description;
	float weight;
public:
	Item();
	Item(std::string name, int calories, std::string description, float weight);

	void setName(std::string name);
	void setCalories(int calories);
	void setDescription(std::string description);
	void setWeight(float weight);

	std::string getName() const;
	int getCalories() const;
	std::string getDescription() const;
	float getWeight() const;

	friend std::ostream& operator<< (std::ostream& os, const Item item);
};

#endif