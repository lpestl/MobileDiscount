#pragma once

#include "ofxXmlSettings.h"
#include <vector>

class ParseWebPages
{
public:
	ParseWebPages();
	~ParseWebPages();

	void setup();
	void update();
	void draw();
	
	bool parseHtmlPage(std::string responseStr);
	std::string removeSubstring(std::string str, std::string substr);
	std::string removeCommentTags(std::string str);
	std::string removeMetaTags(std::string str);
	std::string removeHead(std::string str);
	std::string removeTagsWhithSubstring(std::string str, std::string substr);
	std::string removeScripts(std::string str);

private:
	ofxXmlSettings xml;
	std::vector<std::string> links;
};

