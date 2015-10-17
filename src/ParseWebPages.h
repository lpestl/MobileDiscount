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
	
	std::vector<std::string> getAhrefs(std::string responseStr);
	std::string removeSubstring(std::string str, std::string substr);
	std::string removeCommentTags(std::string str);

private:
	ofxXmlSettings xml;
	std::vector<std::string> links;
};

