#ifndef ERRORS_H
#define ERRORS_H

#include <string> 

template<class T>
class Errors
{
public:
	class EmptyString
	{
	public:
		EmptyString(std::string stringName);
	private:
		std::string invStr;
	};
	
	class OutOfRange
	{
	public:
		OutOfRange(std::string valName, int low, int high);
	private:
		T invalidVal;
		std::string expectedType;
	};

	class TypeError
	{
	public:
		TypeError(std::string valName, std::string type);
	private:

	};

private:
	std::string invStr;
	T invVal;
};

template<class T>
Errors<T>::EmptyString::EmptyString(std::string invStr)
{
	cout << "EmptyString ERROR: " <<  stringName << " cannot be an empty string." << endl;
}

template<class T>
Errors<T>::OutOfRange::OutOfRange(std::string valName, int low, int high)
{
	cout << "OutOfRange ERROR: " << valName << " must be between " << low << " and " << high << "." << endl
}

template<class T>
Errors<T>::TypeError::TypeError(std::string valName, std::string type)
{
	cout << "TypeError ERROR: " << valName << " must be of type " << type << "." << endl;
}
#endif


