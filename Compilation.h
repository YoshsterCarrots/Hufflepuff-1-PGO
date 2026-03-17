#include <string>         // IWYU pragma: keep
#include <unordered_map>  // IWYU pragma: keep
#include <vector>		  // IWYU pragma: keep

#include "Video.h"		  // IWYU pragma: keep

enum Nationality {
	US,
	CA,
	GB,
	INTERNATIONAL,
	DEFAULT
};	

struct Compilation {
	std::unordered_map<char, std::unordered_map<std::string, Video>> compilation = {};
	std::unordered_map<std::string, int> tags = {};

	enum Nationality compilationCountry = DEFAULT;

	Compilation(enum Nationality newCountry);

	void insertVideo(Video newVideo, char letter, const std::string &newVidTitle, const std::vector<std::string> &newTags);

	void compile(std::unordered_map<std::string, Video> &videosFinal, std::unordered_map<std::string, int> &tagsFinal); 
};
