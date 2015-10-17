#include "ParseWebPages.h"



ParseWebPages::ParseWebPages()
{
}


ParseWebPages::~ParseWebPages()
{
}

void ParseWebPages::setup() {

}

void ParseWebPages::update() {

}

void ParseWebPages::draw() {

}

std::vector<std::string> ParseWebPages::getAhrefs(std::string responseStr) {
	
	responseStr = removeSubstring(responseStr, "<!DOCTYPE html>");
	responseStr = removeCommentTags(responseStr);

	xml.loadFromBuffer(responseStr);
	if (xml.doc.Error() == true) {
		std::cout << "[Error] "<< xml.doc.ErrorDesc() << " ID: " << xml.doc.ErrorId() << std::endl;
	}

	return links;
}

std::string ParseWebPages::removeSubstring(std::string str, std::string substr) {
	size_t pos;
	do {
		pos = str.find(substr);
		if (pos != std::string::npos)
			str.erase(pos, substr.length());
	} while (pos != std::string::npos);
	
	return str;
}

std::string ParseWebPages::removeCommentTags(std::string str) {
	size_t pos;
	do {
		pos = str.find("<!--");
		if (pos != std::string::npos) {
			size_t posEnd = str.find("-->");
			if (posEnd != std::string::npos) {
				str.erase(pos, posEnd - pos);
			}
			else {
				std::cout << "[Error] Not find close comment tag ( --> )!" << std::endl;
				break;
			}
		}
	} while (pos != std::string::npos);

	return str;
}