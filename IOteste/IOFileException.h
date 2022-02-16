/**********************************************************************************
// Catalog (Header file)
//
// Created:		01 Feb 2022
//	Author:		Ulysses Gomes
// Update:		15 Feb 2022
//	Author:		Ulysses Gomes
// Compiler:	Studio Visual 19
//
// Description:	IOFileException implementation to handle exception in IODataFile.
//
**********************************************************************************/

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
