#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <vector>		  // IWYU pragma: keep

#include "Compilation.h"  // IWYU pragma: keep

Compilation::Compilation(enum Nationality newCountry) : compilationCountry(newCountry) {}

void Compilation::insertVideo(const Video &newVideo, const std::string &newVidTitle, const std::vector<std::string> &newTags) {
	//check if already exists
	int newTrendingTimes = 1;
	bool repeat = false;
	if (compilation.contains(newVidTitle)) {
		newTrendingTimes = compilation.at(newVidTitle).timesTrending + 1;
		repeat = true;
		if (newVideo.trendingDate > compilation.at(newVidTitle).trendingDate) {
			compilation.insert_or_assign(newVidTitle, newVideo);
			compilation.at(newVidTitle).timesTrending = newTrendingTimes;
		}
	}
	else {
		compilation.insert({newVidTitle, newVideo});
	}


	//add tags

	if (!repeat) {
		for (const std::string &tag : newTags) {
			if (tags.contains(tag)) tags.at(tag)++;
			else tags.insert({tag, 1});
		}
	}

	return;
}



void Compilation::compile(std::unordered_map<std::string, Video> &videosFinal, std::unordered_map<std::string, int> &tagsFinal) { //one of the last functions to implement
	bool repeat = false;
	//videos
	for (const auto& [title, video] : compilation) {
		if (videosFinal.contains(title)) {
			repeat = true;
			if (video.trendingDate < videosFinal.at(title).trendingDate) 
				videosFinal.at(title).timesTrending += video.timesTrending;
			else {
				int newTimesTrending = videosFinal.at(title).timesTrending += video.timesTrending;
				videosFinal.insert_or_assign(title, video);
				videosFinal.at(title).timesTrending = newTimesTrending;
			}
		}
		else {
			videosFinal.insert_or_assign(title, video);
		}
	}

	//tags
	if (!repeat) {
		for (const auto& [tag, count] : tags) {
			if (tagsFinal.contains(tag)) tagsFinal.at(tag) += count;
			else tagsFinal.insert({tag, count});
		}
	}
}
