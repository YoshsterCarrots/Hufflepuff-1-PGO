#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <map>			  // IWYU pragma: keep
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


struct Compilation {
	std::unordered_map<char, std::unordered_map<std::string, Video>> compilation = {};
	std::unordered_map<std::string, int> tags = {};

	enum Nationality compilationCountry = DEFAULT;

	Compilation(enum Nationality newCountry) : compilationCountry(newCountry) {}

	void insertVideo(Video newVideo, char letter, const std::string &newVidTitle, const std::vector<std::string> &newTags) {
		//check if already exists
		int newTrendingTimes = 1;
		[[likely]]
		if (compilation.contains(letter)) {
			if (compilation.at(letter).contains(newVidTitle)) {
				newTrendingTimes = compilation.at(letter).at(newVidTitle).timesTrending + 1;
			}
			compilation.at(letter).insert_or_assign(newVidTitle, newVideo);
			compilation.at(letter).at(newVidTitle).timesTrending = newTrendingTimes;
			
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



	void compile(std::map<std::string,Video>& videosFinal, std::map<std::string, int>& tagsFinal) { //one of the last functions to implement

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
				if (tagsFinal.contains(tag)) {
					tagsFinal.at(tag) += count;
				}
				else tagsFinal.insert({tag, count});
		}
	}
};

