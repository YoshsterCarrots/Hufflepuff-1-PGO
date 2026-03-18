#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <map>			  // IWYU pragma: keep
#include <vector>		  // IWYU pragma: keep
#include <algorithm>	  // IWYU pragma: keep

#include "SortedCompilation.h"  // IWYU pragma: keep

bool viewsCompare(const Video &left, const Video &right) {
	return left.views > right.views;
}

bool likesCompare(const Video &left, const Video &right) {
	return left.likes > right.likes;
}

bool dislikesCompare(const Video &left, const Video &right) {
	return left.dislikes > right.dislikes;
}

bool trendingCompare(const Video &left, const Video &right) {
	return left.timesTrending > right.timesTrending;
}

bool tagsCompare(const std::pair<std::string, int> &left, const std::pair<std::string, int> &right) {
	return left.second > right.second;
}

SortedCompilation::SortedCompilation(const std::unordered_map<std::string, Video> &newVideos, const std::unordered_map<std::string, int> &newTags) {
	sortedVideos.reserve(newVideos.size());
	for (const auto& [title, vid] : newVideos) {
		sortedVideos.emplace_back(vid);
	}

	//tags
	sortedVideos.reserve(newTags.size());
	for (const auto& [tag, count] : newTags) {
		sortedTags.emplace_back(tag, count);
	}
	std::sort(sortedTags.begin(), sortedTags.end(), tagsCompare);
}
