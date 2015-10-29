#pragma once

#include "ofxXmlSettings.h"
#include <vector>
#include <string.h>

struct cities {
	std::string city;
	std::string shortUrl;
};

class ParseWebPages
{
public:
	ParseWebPages();
	~ParseWebPages();

	void setup();
	void update();
	void draw();
	
	bool parseHtmlPage(std::string responseStr);
	void parseCities();
	std::vector<cities> getCities();
	std::string removeSubstring(std::string str, std::string substr);
	std::string removeCommentTags(std::string str);
	std::string removeMetaTags(std::string str);
	std::string removeHead(std::string str);
	std::string removeTagsWhithSubstring(std::string str, std::string substr);
	std::string removeScripts(std::string str);
	std::string UTF8_to_CP1251(std::string const & utf8);
	
private:
	ofxXmlSettings xml;
	std::vector<cities> citiesVector;
	
};

