#include <string>         // IWYU pragma: keep

struct Video {
	std::string title;
	std::string channel;
	std::string publishDate;
	std::string videoID;
	int trendingDate;
	int views;
	int likes;
	int dislikes;
	int comments;
	int timesTrending;	

	bool operator<(const Video &other);

	Video(const std::string &newTitle, const std::string &newChannel, const std::string &newPublishDate, const std::string &newVideoID, int newTrendingDate, int newViews, int newLikes, int newDislikes, int newComments);

};

