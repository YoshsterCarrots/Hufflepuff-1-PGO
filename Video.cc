#include <string>         // IWYU pragma: keep

#include "Video.h"		  // IWYU pragma: keep


bool Video::operator<(const Video &other) { //sorts by viewcount to find duplicates
	return this->trendingDate < other.trendingDate;
}

Video::Video(const std::string &newTitle, const std::string &newChannel, const std::string &newTrendingDate, const std::string &newPublishDate, const std::string &newVideoID, int newViews, int newLikes, int newDislikes, int newComments) {
	title = newTitle;
	channel = newChannel;
	trendingDate = newTrendingDate;
	publishDate = newPublishDate;
	videoID = newVideoID;
	views = newViews;
	likes = newLikes;
	dislikes = newDislikes;
	comments = newComments;
	timesTrending = 1;
}

