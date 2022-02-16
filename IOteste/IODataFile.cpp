#include "IODataFile.h"

// ------------------------------------------------------------------------------

IODataFile::IODataFile()
{
	fileModeRead = 0;
	fileModeWrite = 0;
}

// ------------------------------------------------------------------------------

IODataFile::~IODataFile()
{
	associationValues.clear();
}

// ------------------------------------------------------------------------------

bool IODataFile::open2Read(string fileName, uint mode) throw(IOFileException)
{
	fileModeRead = ios::in | mode;
	if (mode == DEFAULT)
		fin.open(fileName);
	else
		fin.open(fileName, mode);

	if (!fin.is_open())
	{
		string message = "Error while open file " + fileName + " to read.";
		throw IOFileException(message);
	}
	
	return true;
}

// ------------------------------------------------------------------------------

bool IODataFile::open2Write(string fileName, uint mode) throw(IOFileException)
{
	fileModeWrite = ios::out | mode;
	if (mode == DEFAULT)
		fout.open(fileName, ios::out | ios::in);
	else
		fout.open(fileName, ios::out | ios::in | mode);		// To open and position cursor with seekp, you need to open with ios::out and ios::in

	if (!fout.is_open())
	{
		string message = "Error while open file " + fileName + " to write.";
		throw IOFileException(message);
	}

	return true;
}

// ------------------------------------------------------------------------------

void IODataFile::closeReadStream()
{
	fin.close();
	fileModeRead = 0;
}

// ------------------------------------------------------------------------------

void IODataFile::closeWriteStream()
{
	fout.close();
	fileModeWrite = 0;
}

// ------------------------------------------------------------------------------

