#include "/public/read.h" // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep
#include <iostream>       // IWYU pragma: keep
#include <fstream>        // IWYU pragma: keep
#include <unordered_map>
using namespace std;

void parseVideos(ifstream& videos, ofstream& outputFile);

int main() {
	ifstream videos("USvideos.csv");
	ofstream outputFile("compiledVideos.txt");
	
	parseVideos(videos, outputFile);

	outputFile.close();
}



//TODO: 
// - accomodate for all things we will record:
//   - 1. title, 2. trend date, 3. channel, 4. publish date/time, 5. views,
//     6. likes, 7. dislikes, 8. comment count, 9. tags
//
//     and most importantly 10. availability - if the video's unavailable, don't log it.
//   - tags will take some extra parsing because of the intermittent "|" characters; they can also be within a tag itself,
//   so be sure to account for that with isInQuote.


void parseVideos(ifstream& videos, ofstream& outputFile) {
	string currLine;

	getline(videos, currLine);
	while (getline(videos, currLine)) {
		int commaCount = 0;
		bool isInQuote = false;
		bool isAvailable = true;
		for (char c : currLine) {
			if (commaCount == 14) {
				if (c == 'T') {
					isAvailable = false;
				}
				break;
			}
			else if (c == '"') {
				isInQuote = !isInQuote;
			}
			else if (!isInQuote && c == ',') {
				commaCount++;
			}
		}
		if (!isAvailable) {
			continue;
		}
		commaCount = 0;
		isInQuote = false;
		string currID = "";
		string currTrendDate = "";
		string currTitle = "";
		string currChannel = "";
		string currPubTime = "";
		vector<string> currTagList = {};
		string currTag = "";
		string currViews = "";
		string currLikes = "";
		string currDislikes = "";
		string currCommCount = "";
		for (char c : currLine) {
			if (c == '"') {
				isInQuote = !isInQuote;
			}
			else if (!isInQuote && c == ',') {
				if (currTag != "") {
					currTagList.push_back(currTag);
					currTag = "";
				}
				commaCount++;
			}
			else if (commaCount == 0) {
				currID += c;
			}
			else if (commaCount == 1) {
				currTrendDate += c;
			}
			else if (commaCount == 2) {
				currTitle += c;
			}
			else if (commaCount == 3) {
				currChannel += c;
			}
			else if (commaCount == 5) {
				currPubTime += c;
			}
			else if (commaCount == 6) {
				if (!isInQuote && c == '|') {
					currTagList.push_back(currTag);
					currTag = "";
				}
				else {
					currTag += c;
				}
			}
			else if (commaCount == 7) {
				currViews += c;
			}
			else if (commaCount == 8) {
				currLikes += c;
			}
			else if (commaCount == 9) {
				currDislikes += c;
			}
			else if (commaCount == 10) {
				currCommCount += c;
			}
		}
		outputFile << currID << ' ' << currTrendDate << ' ' << currTitle << ' ' << currChannel << ' ' << currPubTime << ' ';
		for (string s : currTagList) {
			outputFile << s << '|' ;
		}
		outputFile << ' ' << stoi(currViews) << ' ' << stoi(currLikes) << ' ' << stoi(currDislikes) << ' ' << stoi(currCommCount);
		outputFile << '\n';
		//Video tempVideo(currTitle, currChannel, currTrendDate, currPubTime, currID, stoi(currViews), stoi(currLikes), stoi(currDislikes), stoi(currCommCount), 0);
	}
}
