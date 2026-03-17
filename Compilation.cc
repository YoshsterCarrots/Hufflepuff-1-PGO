#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <vector>		  // IWYU pragma: keep

#include "Compilation.h"  // IWYU pragma: keep

Compilation::Compilation(enum Nationality newCountry) : compilationCountry(newCountry) {}

void Compilation::insertVideo(Video newVideo, char letter, const std::string &newVidTitle, const std::vector<std::string> &newTags) {
	//check if already exists
	int newTrendingTimes = 1;
	bool repeat = false;
	[[likely]]
		if (compilation.contains(letter)) {
			if (compilation.at(letter).contains(newVidTitle)) {
				newTrendingTimes = compilation.at(letter).at(newVidTitle).timesTrending + 1;
				repeat = true;
			}
			compilation.at(letter).insert_or_assign(newVidTitle, newVideo);
			compilation.at(letter).at(newVidTitle).timesTrending = newTrendingTimes;

		}
		else {
			compilation.insert({letter,{}});
			compilation.at(letter).insert({newVidTitle, newVideo});
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

	//videos
	for (const auto& [letter, letteredMap] : compilation) {
		for (const auto& [title, video] : letteredMap) {
			if (videosFinal.contains(title)) {
				if (video.title < videosFinal.at(title).title)
					videosFinal.at(title).timesTrending++;
				else {
					int newTimesTrending = videosFinal.at(title).timesTrending + 1;
					videosFinal.insert_or_assign(title, video);
					videosFinal.at(title).timesTrending = newTimesTrending;
				}
			}
			else {
				videosFinal.insert_or_assign(title, video);
			}
		}
	}

	//tags
	for (const auto& [tag, count] : tags) {
		if (tagsFinal.contains(tag)) tagsFinal.at(tag) += count;
		else tagsFinal.insert({tag, count});
	}
}
