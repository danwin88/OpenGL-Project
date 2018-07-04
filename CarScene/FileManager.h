

#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdio.h>
#include <time.h>
#include "Singleton.h"

using namespace std;

// DTO class to pass argument to Write methods
class FileItem
{
public:
	FileItem(string dateTime, string playTimeInSeconds, string totalPlayTimeInSeconds)
	{
		this->DateTime = dateTime;
		this->PlayTimeInSeconds = playTimeInSeconds;
		this->TotalPlayTimeInSeconds = totalPlayTimeInSeconds;
	}

	string DateTime;
	string PlayTimeInSeconds;
	string TotalPlayTimeInSeconds;
};

// class to Read nad write playTime, totalPlayTime and date to file
class FileManager
{
public:
	void Init();
	void WriteCurrentPlayTime(string playTime, string totalPlayTime);
	void Write(string fileName, FileItem);
	// read total play time
	int Read(string fileName);
	const string GetCurrentDateTime();

	const string DefaultFileName = "PlayTime.txt";
	int TotalGamgeTimeInt;
	char TotalGamgeTime[10];
};

typedef Singleton<FileManager> TheFileManager;