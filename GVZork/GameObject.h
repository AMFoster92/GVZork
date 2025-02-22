#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>
#include <string>

class GameObject
{
	private:
		int id;
		std::string name;

	public:
		//Default Constructor
		GameObject();

		//Constructor
		GameObject(std::string n);
		
		//Destructor
		~GameObject();

		int getID() const;
		void setName(const std::string n);
		std::string getName() const;
		void print();

		operator << (ostream& os, const GameObject obj);
};

#endif