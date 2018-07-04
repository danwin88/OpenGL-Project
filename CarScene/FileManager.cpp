#include "FileManager.h"

void FileManager::Init()
{
	this->TotalGamgeTimeInt = Read(DefaultFileName);
	itoa(this->TotalGamgeTimeInt, this->TotalGamgeTime, 10);
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const string FileManager::GetCurrentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	// Visit http://en.cppreference.com/w/cpp/chrono/c/strftime for more information about date/time format
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

	return buf;
}

// write formated data to file - setw(6) set, that numbers will have always the same lenght of 6 characters - thanks to it Read method does not need to searchdata but "knows" it by offset from begining of the row
void FileManager::Write(string fileName, FileItem item)
{
	ofstream myfile;
	myfile.open(fileName, ios::app);
	myfile << item.DateTime << " " << setw(6) << setfill('0') << item.PlayTimeInSeconds << " " << setw(6) << setfill('0') << item.TotalPlayTimeInSeconds << endl;
	myfile.close();
}

// read total play time
int FileManager::Read(string fileName)
{
	int totalPlayTime = 0;
	string totalPlayTimeStr = "";
	string line;
	ifstream myfile(fileName);

	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (line.length() > 27)
			{
				totalPlayTimeStr = line.substr(27);
			}
		}
		totalPlayTime = atoi((char*)totalPlayTimeStr.c_str());
		myfile.close();
	}
	else
	{
		cout << "Unable to open file";
	}

	return totalPlayTime;
}

void FileManager::WriteCurrentPlayTime(string playTime, string totalPlayTime)
{
	Write(DefaultFileName, FileItem(GetCurrentDateTime(), playTime, totalPlayTime));
}