#ifndef _IOFILEEXCEPTION_H_
#define _IOFILEEXCEPTION_H_

#include <iostream>
#include <string>

using namespace std;

class IOFileException : public exception
{
private:
	string message;

public:
	IOFileException(string m) : exception(), message(m) {}
	const char* what() const throw();
};

// -------------------------------------------------------------------------------

inline const char* IOFileException::what() const throw()
{
	return message.c_str();
}

// -------------------------------------------------------------------------------

#endif
