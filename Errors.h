#ifndef ERRORS_H
#define ERRORS_H

#include <iostream>
#include <string> 

template<class T>
class Errors
{
public:
	//Critical Errors
	class EmptyString
	{
	public:
		EmptyString(std::string stringName);
	private:
	};
	
	class OutOfRange
	{
	public:
		OutOfRange(std::string valName, int low, int high);
	private:
	};

	class TypeError
	{
	public:
		TypeError(std::string valName, std::string type);
	private:

	};

	//Non-Critical Errors
	class NoMatch
	{
	public:
		NoMatch(std::string matchType);
	private:
	};
	
	class Encumbered
	{
	public:
		Encumbered();
	private:
	};

	class InvalidCommand
	{
	public:
		InvalidCommand();
	private:
	};

private:
	std::string invStr;
	T invVal;
};

template<class T>
Errors<T>::EmptyString::EmptyString(std::string stringName)
{
	std::cout << "EmptyString ERROR: " <<  stringName \
			  << " cannot be an empty string." << std::endl;
}

template<class T>
Errors<T>::OutOfRange::OutOfRange(std::string valName, int low, int high)
{
	std::cout << "OutOfRange ERROR: " << valName << " must be between " \
		<< low << " and " << high << "." << std::endl;
}

template<class T>
Errors<T>::TypeError::TypeError(std::string valName, std::string type)
{
	std::cout << "TypeError ERROR: " << valName << " must be of type " \
		      << type << "." << std::endl;
}

template<class T>
Errors<T>::NoMatch::NoMatch(std::string matchType)
{
	std::cout << "No matching " << matchType << " was found." << std::endl;
}

template<class T>
Errors<T>::Encumbered::Encumbered()
{
	std::cout << "You are carrying too much to travel." << std::endl;
}

template <class T>
Errors<T>::InvalidCommand::InvalidCommand()
{
	std::cout << "You can't do that! Have you lost your mind?" << std::endl;
}
#endif


