#include "/public/read.h" // IWYU pragma: keep
#include <string>         // IWYU pragma: keep
#include <vector>         // IWYU pragma: keep
#include <iostream>       // IWYU pragma: keep
#include <fstream>        // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include "SortedCompilation.h" //IWYU pragma: keep
//#include <functional>     // IWYU pragma: keep
using namespace std;

void parseVideos(ifstream& videos, ofstream& outputFile, Compilation& comp);

string printVideoData(const Video& video);
//void printTop100(SortedCompilation& comp, ofstream& output, const function<bool(const Video&, const Video&)>& func);

int main() {
	ifstream videos("USvideos.csv");
	ofstream outputFile("compiledVideos.txt");

	//unordered_map<string, Video> allVideos;
	//unordered_map<string, int> allTags;

	Compilation INTL_Comp(INTERNATIONAL);
	
	parseVideos(videos, outputFile, INTL_Comp);
	INTL_Comp.compile(INTL_Comp.compilation, INTL_Comp.tags);
	cerr << "Video map size: " << INTL_Comp.compilation.size() << endl;
	cerr << "Tag map size: " << INTL_Comp.tags.size() << endl;

	videos = ifstream ("CAvideos.csv");
	parseVideos(videos, outputFile, INTL_Comp);
	INTL_Comp.compile(INTL_Comp.compilation, INTL_Comp.tags);
	cerr << "Video map size: " << INTL_Comp.compilation.size() << endl;
	cerr << "Tag map size: " << INTL_Comp.tags.size() << endl;

	videos = ifstream ("GBvideos.csv");
	parseVideos(videos, outputFile, INTL_Comp);
	INTL_Comp.compile(INTL_Comp.compilation, INTL_Comp.tags);
	cerr << "Video map size: " << INTL_Comp.compilation.size() << endl;
	cerr << "Tag map size: " << INTL_Comp.tags.size() << endl;
	
	SortedCompilation Full_Comp(INTL_Comp.compilation, INTL_Comp.tags);
	
	/*
	outputFile << "Most Views:" << endl << endl;
	printTop100(Full_Comp, outputFile, viewsCompare);
	outputFile << endl << "Most Likes:" << endl << endl;
	printTop100(Full_Comp, outputFile, likesCompare);
	outputFile << endl << "Most Dislikes:" << endl << endl;
	printTop100(Full_Comp, outputFile, dislikesCompare);
	*/
	
	sort(Full_Comp.sortedVideos.begin(), Full_Comp.sortedVideos.end(), viewsCompare);
	cerr << "Most Views:" << endl << endl;
	outputFile << "Most Views:" << endl << endl;
	for (int i = 0; i < 100 && i < Full_Comp.sortedVideos.size(); i++) {
		const Video& vid = Full_Comp.sortedVideos.at(i);
		cerr << i + 1 << ". " << vid.title << " | " << vid.channel << "\n      " << vid.views << " Views" << endl;
		outputFile << i + 1 << ". " << printVideoData(vid) << endl;
	}
	cerr << endl;
	outputFile << endl;

	sort(Full_Comp.sortedVideos.begin(), Full_Comp.sortedVideos.end(), likesCompare);
	cerr << "Most Likes:" << endl << endl;
	outputFile << "Most Likes:" << endl << endl;
	for (int i = 0; i < 100 && i < Full_Comp.sortedVideos.size(); i++) {
		const Video& vid = Full_Comp.sortedVideos.at(i);
		cerr << i + 1 << ". " << vid.title << " | " << vid.channel << "\n      " << vid.likes << " Likes" << endl;
		outputFile << i + 1 << ". " << printVideoData(vid) << endl;
	}
	cerr << endl;
	outputFile << endl;

	sort(Full_Comp.sortedVideos.begin(), Full_Comp.sortedVideos.end(), dislikesCompare);
	cerr << "Most Dislikes:" << endl << endl;
	outputFile << "Most Dislikes:" << endl << endl;
	for (int i = 0; i < 100 && i < Full_Comp.sortedVideos.size(); i++) {
		const Video& vid = Full_Comp.sortedVideos.at(i);
		cerr << i + 1 << ". " << vid.title << " | " << vid.channel << "\n      " << vid.dislikes << " Dislikes" << endl;
		outputFile << i + 1 << ". " << printVideoData(vid) << endl;
	}
	cerr << endl;
	outputFile << endl;

	cerr << "Top Tags: " << endl << endl;
	outputFile << "Top Tags: " << endl << endl;
	for (int i = 0; i < 100 && i < Full_Comp.sortedTags.size(); i++) {
		const pair<string, int>& tag = Full_Comp.sortedTags.at(i);
		cerr << i + 1 << ". " << tag.first << " | " << tag.second << " Appearances" << endl;
		outputFile << i + 1 << ". " << tag.first << " | " << tag.second << " Appearances" << endl;
	}

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


void parseVideos(ifstream& videos, ofstream& outputFile, Compilation& comp) {
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
		//char titleFirstLetter = tolower(currTitle.at(0));
		/*
		outputFile << titleFirstLetter << ' ' << currID << ' ' << currTrendDate << ' ' << currTitle << ' ' << currChannel << ' ' << currPubTime << ' ';
		for (const string& s : currTagList) {
			outputFile << s << '|' ;
		}
		outputFile << ' ' << stoi(currViews) << ' ' << stoi(currLikes) << ' ' << stoi(currDislikes) << ' ' << stoi(currCommCount);
		outputFile << '\n';
		*/
		Video tempVideo(currTitle, currChannel, currTrendDate, currPubTime, currID, stoi(currViews), stoi(currLikes), stoi(currDislikes), stoi(currCommCount));
		comp.insertVideo(tempVideo, currTitle, currTagList);
	}
}

string printVideoData(const Video& video) {
	return video.title + " | " + video.channel + "\n      Views: " + to_string(video.views) + " | Likes: " + to_string(video.likes) + " | Dislikes: " + to_string(video.dislikes) + " | Comments: " + to_string(video.comments) + "\n      Upload Date: " + video.publishDate +  + " | Most Recent Trending Date: " + video.trendingDate + " | Times Trending: " + to_string(video.timesTrending) + "\n      URL: https://www.youtube.com/watch?v=" + video.videoID;
}
/*
void printTop100(SortedCompilation& comp, ofstream& output, const function<bool(const Video&, const Video&)>& func) {	
	sort(comp.sortedVideos.begin(), comp.sortedVideos.end(), viewsCompare);
	for (int i = 0; i < 100 && i < comp.sortedVideos.size(); i++) {
		output << i + 1 << ". " << printVideoData(comp.sortedVideos.at(i)) << endl;
	}
}
*/
