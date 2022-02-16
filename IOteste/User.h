#ifndef _USER_H_
#define _USER_H_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;
using std::string;
using std::stringstream;

class User {
private: 
	char name[100];
	int age;

public:
	void getNewUser() 
	{
		cout << "Informe o nome: ";
		cin.getline(name, 100);
		cout << "Informe a idade: ";
		cin >> age;
		cout << endl;
	}

	void setDefaultDummyUser(int id = 0)
	{
		stringstream tempText;
		string s;
		tempText << "Dummy User";
		if (id > 0)
			tempText << " " << id;
		s = tempText.str();
		strcpy_s(name, s.c_str());		
		age = 100 + id;
	}

	void clearUser()
	{
		memset(name, '\0', sizeof(char) * 100);
	}

	void print()
	{
		cout << "=====================================" << endl;
		cout << "Name: " << name << endl;
		cout << "Age: " << age << endl;
		cout << "=====================================" << endl;
	}

	char* getName()
	{
		return name;
	}

	int getAge()
	{
		return age;
	}
};

#endif