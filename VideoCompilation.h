#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <vector>		  // IWYU pragma: keep
//#include <unordered_set>  // IWYU pragma: keep
#include <iostream>       // IWYU pragma: keep


enum Nationality {
	US,
	CA,
	GB, 
	INTERNATIONAL,
	DEFAULT
};


struct Video {
	std::string title = "Free Robux";
	std::string channel = "JohnDoe";
	std::string trendingDate = "Eternally popular";
	std::string publishDate = "1919-01-15T12:27:19.000Z"; //Boston Great Molasses Flood
	std::string videoID = "dQw4w9WgXcQ"; //Guess
	int views = 420;
	int likes = 69;
	int dislikes = 67;
	int comments = 1999;
	int timesTrending = 1;
	

	bool operator<(const Video &other) { //sorts by viewcount to find duplicates
		return this->trendingDate < other.trendingDate;
	}

	Video(std::string newTitle, std::string newChannel, std::string newTrendingDate, std::string newPublishDate, std::string newVideoID, int newViews, int newLikes, int newDislikes, int newComments) {
		title = newTitle;
		channel = newChannel;
		trendingDate = newTrendingDate;
		publishDate = newPublishDate;
		videoID = newVideoID;
		likes = newLikes;
		dislikes = newDislikes;
		comments = newComments;
		timesTrending = 1;
	}

};

//TODO: create a way to sort the three way combined compilation 
//    Potential ideas:
//		1. rewrite combineTwo and combineThree to have combineThree add all 3 to a vector
//		2. Make sortable compilation class

struct Compilation {
	std::unordered_map<char, std::unordered_map<std::string, Video>> compilation = {};
	std::unordered_map<std::string, int> tags = {};

	enum Nationality compilationCountry = DEFAULT;

	Compilation(enum Nationality newCountry) : compilationCountry(newCountry) {}

	void insertVideo(Video newVideo, char letter, const std::string &newVidTitle, const std::vector<std::string> &newTags) {
		//check if already exists
		
		[[likely]]
		if (compilation.contains(letter)) {
			compilation.at(letter).insert_or_assign(newVidTitle, newVideo);
		}
		else {
			compilation.insert({letter,{}});
			compilation.at(letter).insert({newVidTitle, newVideo});
		}

		//add tags
		
		for (const std::string &tag : newTags) {
			if (tags.contains(tag)) {
				tags.at(tag)++;
			}
			else {
				tags.insert({tag, 1});
			}
		}

		return;
	}



	Compilation combineTwo(const Compilation& firstComp, const Compilation& secondComp) { //one of the last functions to implement
		if (firstComp.compilationCountry == secondComp.compilationCountry) {
			std::cout << "error: tried to combine two lists made from the same country list. Something definitely went wrong.\n";
			exit(1);
		}
		Compilation combinedComp = firstComp;
		combinedComp.compilationCountry = INTERNATIONAL;

		//videos
		for (const auto& [letter, letteredMap] : secondComp.compilation) {
			//[[unlikely]]
			if (!combinedComp.compilation.contains(letter)) {
				combinedComp.compilation.insert({letter, {}});
			}
			for (const auto& [title, video] : letteredMap) {
				if (combinedComp.compilation.at(letter).contains(title) && combinedComp.compilation.at(letter).at(title) < video) continue;
				else combinedComp.compilation.at(letter).insert_or_assign(title, video);
			}
		}

		//tags
		for (const auto& [tag, count] : secondComp.tags) {
				if (combinedComp.tags.contains(tag)) {
					combinedComp.tags.at(tag) += count;
				}
				else combinedComp.tags.insert({tag, count});
		}

		return combinedComp;
	}

	Compilation combineThree(const Compilation& firstComp, const Compilation& secondComp, const Compilation& thirdComp) { //might need to close the file stream to avoid stack overflow
		Compilation join = combineTwo(firstComp, secondComp);
		return combineTwo(join, thirdComp);
	}
};

