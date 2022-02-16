#include "pch.h"
#include "IODataFileTest.h"

#include <sstream>
#include <string>

using std::string;
using std::stringstream;

TEST_F(IODataFileTest, OpenTextFileToReadAndWorks)
{
	EXPECT_TRUE(io.open2Read(TEXT_FILE_NAME));
}

TEST_F(IODataFileTest, ThrowExceptionWhileOpenInexistentFile)
{
	EXPECT_THROW(io.open2Read("text-no-exist.txt"), IOFileException);
}

TEST_F(IODataFileTest, OpenBinaryFileToReadAndWorks)
{
	EXPECT_TRUE(io.open2Read(BINARY_FILE_NAME, ios::binary));
	User u;
	u.clearUser();
	io.readObject<User>(&u);

	EXPECT_STREQ(u.getName(), "Dummy User");
	io.closeReadStream();
}

TEST_F(IODataFileTest, OpenTextFileToReadBinaryObjectAndThrowException)
{
	io.open2Read(BINARY_FILE_NAME);
	User u;
	u.clearUser();
	EXPECT_THROW(io.readObject<User>(&u), IOFileException);
}

TEST_F(IODataFileTest, ReadTextFileWithoutOpenAndThrowException)
{
	char line[1024];
	EXPECT_THROW(io.readLine(line), IOFileException);
}

TEST_F(IODataFileTest, ReadBinaryFileWithoutOpenAndThrowException)
{
	User u;
	u.clearUser();
	EXPECT_THROW(io.readObject<User>(&u), IOFileException);
}

TEST_F(IODataFileTest, WriteTextFileWithoutOpenAndThrowException)
{
	char text[1024] = "Lorem ipsum dolor sit amet";
	EXPECT_THROW(io.writeLine(text), IOFileException);
}

TEST_F(IODataFileTest, WriteBinaryFileWithoutOpenAndThrowException)
{
	User u;
	u.setDefaultDummyUser();
	EXPECT_THROW(io.writeObject<User>(&u), IOFileException);
}

TEST_F(IODataFileTest, WriteBinaryObjectAndExpectToWorks)
{
	User u;
	u.setDefaultDummyUser(1000);
	io.open2Write(BINARY_FILE_NAME, ios::binary | ios::app);
	EXPECT_TRUE(io.writeObject<User>(&u));
	io.closeWriteStream();

	io.open2Read(BINARY_FILE_NAME, ios::binary);
	u.setDefaultDummyUser(9);
	u.clearUser();
	io.readObject<User>(&u, 3);
	io.closeReadStream();

	EXPECT_TRUE(u.getName(), "Dummy User 1000");
}

TEST_F(IODataFileTest, WriteBinaryObjectAtPositionXAndExpectToWorks)
{
	User u;
	u.setDefaultDummyUser(199);
	io.open2Write(BINARY_FILE_NAME, ios::binary);
	EXPECT_TRUE(io.writeObject<User>(&u, 1));
	io.closeWriteStream();

	io.open2Read(BINARY_FILE_NAME, ios::binary);
	u.setDefaultDummyUser(9);
	u.clearUser();
	io.readObject<User>(&u, 1);
	io.closeReadStream();

	EXPECT_TRUE(u.getName(), "Dummy User 199");
}

TEST_F(IODataFileTest, OpenFileToWriteAtPositionWithAppModeAndThrowException)
{
	User u;
	u.setDefaultDummyUser(199);
	io.open2Write(BINARY_FILE_NAME, ios::binary | ios::app);
	EXPECT_THROW(io.writeObject<User>(&u, 1), IOFileException);
}

TEST_F(IODataFileTest, LargeReadAndWriteWorks)
{
	User user;
	char fileName[30] = "large.bin";
	io.open2Write(fileName, ios::binary | ios::app);
	for (int u = 0; u < 1000; u++)
	{
		user.setDefaultDummyUser(u);
		EXPECT_TRUE(io.writeObject<User>(&user));
	}
	io.closeWriteStream();

	stringstream streamMessage;
	string stringMessage;
	io.open2Read(fileName, ios::binary);
	for (int u = 0; u < 1000; u++)
	{
		streamMessage.str("");
		user.clearUser();
		io.readObject(&user, u);
		streamMessage << "Dummy User";
		if (u != 0)
			streamMessage << " " << u;
		stringMessage = streamMessage.str();
		EXPECT_EQ(strcmp(user.getName(), stringMessage.c_str()), 0);
	}
	io.closeReadStream();

	streamMessage.str("");
	streamMessage << "del " << fileName;
	stringMessage = streamMessage.str();
	system(stringMessage.c_str());
}

TEST_F(IODataFileTest, OpenWriteAndReadTextWorks)
{
	char outputFile[2048] = "Lorem ipsum dolor sit amet.";
	char outputOne[512] = "Donec vehicula pretium massa eget volutpat.";
	char outputTwo[512] = "Aenean pellentesque odio ut nulla blandit porta. Suspendisse dignissim feugiat dui non pellentesque.";
	io.open2Write(TEXT_FILE_NAME, ios::app);

	io.writeLine(outputOne);
	io.writeLine(outputTwo);

	io.closeWriteStream();
	strcat(outputFile, outputOne);
	strcat(outputFile, outputTwo);
	
	char inputFile[2048] = "\0";
	char inputPart[512];

	io.open2Read(TEXT_FILE_NAME);
	while (io.readLine(inputPart))
	{
		strcat(inputFile, inputPart);
	}

	io.closeReadStream();

	EXPECT_STREQ(outputFile, inputFile);
}

TEST_F(IODataFileTest, OpenToReadTextWithBinaryModeAndThrowException)
{
	io.open2Read(TEXT_FILE_NAME, ios::binary);
	char textline[1024];
	EXPECT_THROW(io.readLine(textline), IOFileException);
}

TEST_F(IODataFileTest, OpenToWriteTextWithBinaryModeAndThrowException)
{
	io.open2Write(TEXT_FILE_NAME, ios::binary);
	char textline[1024] = "test";
	EXPECT_THROW(io.writeLine(textline), IOFileException);
}