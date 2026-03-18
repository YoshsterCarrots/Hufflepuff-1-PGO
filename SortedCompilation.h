#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <map>			  // IWYU pragma: keep
#include <vector>		  // IWYU pragma: keep
#include <algorithm>	  // IWYU pragma: keep

#include "Compilation.h"  // IWYU pragma: keep


bool viewsCompare(const Video &left, const Video &right);

bool likesCompare(const Video &left, const Video &right);

bool dislikesCompare(const Video &left, const Video &right);

bool trendingCompare(const Video &left, const Video &right);

bool tagsCompare(const std::pair<std::string, int> &left, const std::pair<std::string, int> &right);

class SortedCompilation {
public:
	std::vector<Video> sortedVideos = {};
	std::vector<std::pair<std::string, int>> sortedTags = {};

	SortedCompilation(const std::unordered_map<std::string, Video> &newVideos, const std::unordered_map<std::string, int> &newTags); 
};
