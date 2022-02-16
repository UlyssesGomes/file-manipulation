#ifndef _IODATAFILETEST_H_
#define _IODATAFILETEST_H_

#include <string>

#include "pch.h"
#include "../IOteste/IODataFile.h"
#include "../IOteste/IODataFile.cpp"
#include "../IOteste/User.h"

using std::string;

class IODataFileTest : public ::testing::Test
{
protected:

    void SetUp() override
    {
        // Code here will be called immediately after the constructor (right
        // before each test).
       
        // Create txt file
        command = "echo Lorem ipsum dolor sit amet.> ";
        command += TEXT_FILE_NAME;
        system(command.c_str());

        // Create bin file
        io.open2Write(BINARY_FILE_NAME, ios::binary | ios::trunc);
        User user;
        for (int u = 0; u < 3; u++)
        {
            user.setDefaultDummyUser(u);
            io.writeObject<User>(&user);
        }
        io.closeWriteStream();
    }

    void TearDown() override
    {
        // Code here will be called immediately after each test (right
        // before the destructor).

        // close all srteam
        io.closeReadStream();
        io.closeWriteStream();
        
        // Destroy txt file
        command = "del ";
        command += TEXT_FILE_NAME;
        system(command.c_str());
        
        // Destroy bin file
        command = "del ";
        command += BINARY_FILE_NAME;
        system(command.c_str());
    }

    string command;
    const char TEXT_FILE_NAME[40] = "text.txt";
    const char BINARY_FILE_NAME[40] = "obj.bin";

    IODataFile io;
    User user;
};

#endif