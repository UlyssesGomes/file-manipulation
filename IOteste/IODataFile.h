/**********************************************************************************
// Catalog (Header File)
//
// Created:		31 Jan 2022
//	Author:		Ulysses Gomes
// Updated:		31 Jan 2022
//	Author:		Ulysses Gomes
// Compiler:	Visual C++ 19
//
// Description:	Write and read files class abstraction to manipulate text
//				and binary files
//
**********************************************************************************/

#ifndef _IODATAFILE_H_
#define _IODATAFILE_H_

#include <fstream>											// leitura e escrita em arquivos
#include <iostream>
#include <string>											// tipo string da STL
#include <map>
#include <cstring>

#include "IOFileException.h"

#define DEFAULT 1

typedef unsigned int uint;
typedef long long llong;

using namespace std;
using std::map;
using std::string;

class IODataFile
{
private:
	ofstream fout;															// stream de saída de arquivo
	ifstream fin;															// stream de entrada de arquivo
	int fileModeRead;														// modo no qual o arquivo foi aberto para leitura
	int fileModeWrite;														// modo no qual o arquivo foi aberto para escrita

	const uint lineLength = 1024;											// tamanho de uma linha para leitura em arquivo

	map<uint, uint> associationValues;										// associação da redefinição dos tipos de abertura de arquivo

public:
	IODataFile();
	~IODataFile();

	// abre o arquivo para leitura, com padrão de abertura em texto
	bool open2Read(string fileName, uint mode = DEFAULT) throw(IOFileException);
	// abre o arquivo para escrita, com padrão de abertura em texto
	bool open2Write(string fileName, uint mode = DEFAULT) throw(IOFileException);

	void closeReadStream();													// fecha stream de leitura
	void closeWriteStream();												// fecha stream de escrita
	
	bool readLine(char* line) throw(IOFileException);						// ler uma linha do arquivo do tamanho lineLength
	template<class T>
	bool readObject(T* object) throw(IOFileException);						// ler um objeto binário salvo em arquivo
	template<class T>
	bool readObject(T* object, llong position) throw(IOFileException);		// ler um objeto binário salvo em arquivo na posição position

	bool writeLine(const char* line) throw(IOFileException);				// escreve uma linha incluindo automaticamente o \n ao final
	template<class T>
	bool writeObject(T* object) throw(IOFileException);						// escreve um objeto em arquivo
	template<class T>
	bool writeObject(T* object, llong position) throw(IOFileException);		// escreve um objeto em arquivo na posição "position"

	llong getCurrentReadPosition() throw(IOFileException);					// retorna a posição atual de leitura
	llong getCurrentWritePosition() throw(IOFileException);					// retorna a posição atual de escrita

};

// ------------------------------------------------------------------------------

inline llong IODataFile::getCurrentReadPosition() throw(IOFileException)
{
	if (fileModeRead >= DEFAULT)
	{
		return fin.tellg();
	}
	else
	{
		throw IOFileException("Error getting read position from file.");
	}

	return -1;
}

// ------------------------------------------------------------------------------

inline llong IODataFile::getCurrentWritePosition() throw(IOFileException)
{
	if (fileModeWrite >= DEFAULT)
	{
		return fout.tellp();
	}
	else
	{
		throw IOFileException("Error getting write position from file.");
	}

	return -1;
}

// ------------------------------------------------------------------------------

inline bool IODataFile::readLine(char* line) throw(IOFileException)
{
	if (fin.good() && ((fileModeRead ^ ios::binary) > fileModeRead) && fileModeRead >= DEFAULT)
	{
		return fin.getline(line, lineLength) ? true : false;
	}
	else if (fileModeRead < DEFAULT)
	{
		throw IOFileException("Error, the file was not opened.");
	}
	else if ((fileModeRead ^ ios::binary) < fileModeRead)
	{
		throw IOFileException("Error, the file was not opened in text mode.");
	}

	return false;
}

// ------------------------------------------------------------------------------

inline bool IODataFile::writeLine(const char* line) throw(IOFileException)
{
	if (fileModeWrite >= DEFAULT && (fileModeWrite ^ ios::binary) > fileModeWrite)
	{
		fout << line << endl;
		return fout.good() ? true : false;
	}
	else if (fileModeWrite < DEFAULT)
	{
		throw IOFileException("Error, the file was not opened.");
	}
	else if ((fileModeWrite ^ ios::binary) < fileModeWrite)
	{
		throw IOFileException("Error, the file was not opened in text mode.");
	}

	return false;
}

// ------------------------------------------------------------------------------

template<class T>
bool IODataFile::readObject(T* object) throw(IOFileException)
{
	if ((fileModeRead ^ ios::binary) < fileModeRead && fin.good())
	{
		return fin.read(reinterpret_cast<char*>(object), sizeof(*object)) ? true : false;
	}
	else if ((fileModeWrite ^ ios::binary) > fileModeWrite)
	{
		throw IOFileException("Error, the file was not opened in binary mode.");
	}
	else
	{
		throw IOFileException("Error, the file is not readable.");
	}

	return false;
}

// ------------------------------------------------------------------------------

template<class T>
bool IODataFile::readObject(T* object, llong position) throw(IOFileException)
{
	if (position >= 0 && ((fileModeRead ^ ios::binary) < fileModeRead))
	{
		fin.seekg(position * sizeof(*object));
		if (fin.good())
		{
			return fin.read(reinterpret_cast<char*>(object), sizeof(*object))? true : false;
		}
		else
		{
			return false;
		}
	}
	else if ((fileModeWrite ^ ios::binary) > fileModeWrite)
	{
		throw IOFileException("Error, the file was not opened in binary mode.");
	}
	else
	{
		throw IOFileException("Error, the file is not readable.");
	}

	return false;
}

// ------------------------------------------------------------------------------

template<class T>
bool IODataFile::writeObject(T* object) throw(IOFileException)
{
	if (fileModeWrite >= DEFAULT && (fileModeWrite ^ ios::binary) < fileModeWrite)
	{
		fout.write(reinterpret_cast<char*>(object), sizeof(*object));
		return true;
	}
	else if ((fileModeWrite ^ ios::binary) > fileModeWrite)
	{
		throw IOFileException("Error, the file was not opened in binary mode.");
	}
	else
	{
		throw IOFileException("Error, the file is not writable.");
	}

	return false;
}

// ------------------------------------------------------------------------------

template<class T>
bool IODataFile::writeObject(T* object, llong position) throw(IOFileException)
{
	if (position >= 0 && ((fileModeWrite ^ ios::binary) < fileModeWrite) && ((fileModeWrite ^ ios::app) > fileModeWrite))
	{
		fout.seekp(position * sizeof(*object), ios::beg);
		if (fout.good())
		{
			if (fileModeWrite >= DEFAULT && (fileModeWrite ^ ios::binary) < fileModeWrite)
			{
				fout.write(reinterpret_cast<char*>(object), sizeof(*object));
				return true;
			}
			else if (fileModeWrite < DEFAULT)
			{
				throw IOFileException("Error, the file was not opened.");
			}
			else if ((fileModeWrite ^ ios::binary) > fileModeWrite)
			{
				throw IOFileException("Error, the file was not opened in binary mode.");
			}

			return true;
		}
		else
		{
			throw IOFileException("Error, the file is not writable.");
		}
	}
	else if ((fileModeWrite ^ ios::app) < fileModeWrite)
	{
		throw IOFileException("Error, seekp cannot be aplied with ios::app mode.");
	}

	return false;
}

// ------------------------------------------------------------------------------



#endif
