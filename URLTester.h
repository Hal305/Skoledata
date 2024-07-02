#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <curl/curl.h>
#include <Windows.h>

class URLTester
{
public:
	URLTester(std::string inputFile, std::string outputFile, int sleepTimer);
private:
	const std::string mInputFile;
	const std::string mOutputFile;
	int mSleepTimer;
	void readAndWriteURLFile();
};

