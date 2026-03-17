#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <map>			  // IWYU pragma: keep
#include <vector>		  // IWYU pragma: keep
#include <unordered_set>  // IWYU pragma: keep
#include <set>			  // IWYU pragma: keep
#include <iostream>       // IWYU pragma: keep
#include <algorithm>	  // IWYU pragma: keep

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

	Video(const std::string &newTitle, const std::string &newChannel, const std::string &newTrendingDate, const std::string &newPublishDate, const std::string &newVideoID, int newViews, int newLikes, int newDislikes, int newComments) {
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
			if (tags.contains(tag)) tags.at(tag)++;
			else tags.insert({tag, 1});
		}

		return;
	}



	void compile(std::unordered_map<std::string, Video> &videosFinal, std::unordered_map<std::string, int> &tagsFinal) { //one of the last functions to implement

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
};

bool viewsCompare(const Video &left, const Video &right) {
	return left.views < right.views;
}

bool likesCompare(const Video &left, const Video &right) {
	return left.likes < right.likes;
}

bool dislikesCompare(const Video &left, const Video &right) {
	return left.dislikes < right.dislikes;
}

bool trendingCompare(const Video &left, const Video &right) {
	return left.timesTrending < right.timesTrending;
}

bool tagsCompare(const std::pair<std::string, int> &left, const std::pair<std::string, int> &right) {
	return left.second > right.second;
}

struct SortedCompilation {
	std::vector<Video> sortedVideos = {};
	std::vector<std::pair<std::string, int>> sortedTags = {};

	SortedCompilation(const std::unordered_map<std::string, Video> &newVideos, const std::unordered_map<std::string, int> &newTags) {
		sortedVideos.reserve(newVideos.size());
		for (const auto& [title, vid] : newVideos) {
			sortedVideos.emplace_back(vid);
		}
		std::sort(sortedVideos.begin(), sortedVideos.end(), viewsCompare);
		//tags
		sortedVideos.reserve(newTags.size());
		for (const auto& [tag, count] : newTags) {
			sortedTags.emplace_back(tag, count);
		}
		std::sort(sortedTags.begin(), sortedTags.end(), tagsCompare);

	}

	
	

};
