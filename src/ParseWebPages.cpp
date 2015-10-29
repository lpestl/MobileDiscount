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

bool ParseWebPages::parseHtmlPage(std::string responseStr) {
	bool status = true;

	//std::cout << responseStr << std::endl;

	//std::cout << responseStr.length() << std::endl;
	//responseStr = removeSubstring(responseStr, "<!DOCTYPE html>");
	//std::cout << responseStr.length() << std::endl;
	//responseStr = removeCommentTags(responseStr);
	//std::cout << responseStr.length() << std::endl;
	//responseStr = removeMetaTags(responseStr);
	//std::cout << responseStr.length() << std::endl;
	responseStr = removeHead(responseStr);
	//std::cout << responseStr.length() << std::endl;
	responseStr = removeTagsWhithSubstring(responseStr, "div");
	responseStr = removeTagsWhithSubstring(responseStr, "strong");
	//std::cout << responseStr.length() << std::endl;
	responseStr = removeScripts(responseStr);

	responseStr = UTF8_to_CP1251(responseStr);

	std::cout << "[INFO] Buffer length after conversion. " << responseStr.length() << std::endl;

	//std::cout << responseStr.c_str() << std::endl;
	
	FILE *out = fopen("data//parse.xml", "w");
	fprintf(out, "%s", responseStr.c_str());
	fclose(out);
	
	if (xml.loadFromBuffer(responseStr)) {
	//if (xml.loadFile("parse.xml")) {
		std::cout << "[INFO] Load xml from buffer is OK!" << std::endl;
	}
	else {
		std::cout << "[WARRNING] Problem loading XML file from bufer." << std::endl;
	}
	
	if (xml.doc.Error() == true) {
		std::cout << "[Error] "<< xml.doc.ErrorDesc() << " ID: " << xml.doc.ErrorId() << std::endl;
		status = false;
	}
	
	/*Города идут в тегах 
	<html lang="ru" xmlns:og="http://ogp.me/ns#">
	<body class="index-page">		
		<ul> 
			<li> 
				<a title="Архангельская область" href="/arkhangelsk/"> 
					<span class="text">Архангельск</span> 
				</a> 
			</li> 
			...

			где ul - столбец
			*/

	return status;
}

std::string ParseWebPages::UTF8_to_CP1251(std::string const & utf8)
{
	if (!utf8.empty())
	{
		int wchlen = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), NULL, 0);
		if (wchlen > 0 && wchlen != 0xFFFD)
		{
			std::vector<wchar_t> wbuf(wchlen);
			MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), utf8.size(), &wbuf[0], wchlen);
			std::vector<char> buf(wchlen);
			WideCharToMultiByte(1251, 0, &wbuf[0], wchlen, &buf[0], wchlen, 0, 0);

			return std::string(&buf[0], wchlen);
		}
	}
	return std::string();
}

void ParseWebPages::parseCities() {
	xml.pushTag("html");
	xml.pushTag("body");
	for (int i = 0; i < xml.getNumTags("ul"); i++) {
		std::string menuCheck = xml.getAttribute("ul", "class", "defaultAttribute", i);
 		if (menuCheck == "menu") 
			break;
		xml.pushTag("ul", i);
		for (int j = 0; j < xml.getNumTags("li"); j++) {
			xml.pushTag("li", j);
			cities tempCity;

			xml.pushTag("a");
			tempCity.city = xml.getValue("span", "defaultCity");
			//tempCity.city = UTF8_to_CP1251(tempCity.city);
			xml.popTag();

			tempCity.shortUrl = xml.getAttribute("a", "href", "#");
			citiesVector.push_back(tempCity);
			
			xml.popTag();
		}
		xml.popTag();
	}
	xml.popTag();
	xml.popTag();
}

std::vector<cities> ParseWebPages::getCities() {
	return citiesVector;
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
			std::string closeChars = "-->";
			size_t posEnd = str.find(closeChars);
			if (posEnd != std::string::npos) {
				str.erase(pos, posEnd + closeChars.length() - pos);
			}
			else {
				std::cout << "[Error] Not find close comment tag ( --> )!" << std::endl;
				break;
			}
		}
	} while (pos != std::string::npos);

	return str;
}

std::string ParseWebPages::removeMetaTags(std::string str) {
	size_t pos;
	size_t posEnd = 0;
	std::string substr;
	do {
		pos = str.find("<", posEnd);
		if (pos != std::string::npos) {
			std::string closeChars = ">";
			posEnd = str.find(">", pos);
			if (posEnd != std::string::npos) {
				size_t ep = posEnd - pos;
				//std::cout << str.substr(pos, ep) << std::endl;
				substr = str.substr(pos, ep);
				size_t ppp = substr.find("meta");//str.find("meta", pos, posEnd - pos);
				if (ppp != std::string::npos) {
					str.erase(pos, posEnd + closeChars.length() - pos);
					posEnd = pos;
				}
			}
		}
	} while (pos != std::string::npos);

	return str;
}

std::string ParseWebPages::removeHead(std::string str) {
	size_t pos = str.find("<head>");
	if (pos != std::string::npos) {
		std::string closeChars = "</head>";
		size_t posEnd = str.find(closeChars);
		if (posEnd != std::string::npos) {
			str.erase(pos, posEnd + closeChars.length() - pos);
		}
	}
	return str;
}

std::string ParseWebPages::removeTagsWhithSubstring(std::string str, std::string substr) {
	size_t pos;
	size_t posEnd = 0;
	std::string tag;
	do {
		pos = str.find("<", posEnd);
		if (pos != std::string::npos) {
			std::string closeChars = ">";
			posEnd = str.find(closeChars, pos);
			if (posEnd != std::string::npos) {
				size_t ep = posEnd - pos;
				tag = str.substr(pos, ep);
				size_t ppp = tag.find(substr);
				if (ppp != std::string::npos) {
					str.erase(pos, posEnd + closeChars.length() - pos);
					posEnd = pos;
				}
			}
		}
	} while (pos != std::string::npos);
	
	return str;
}

std::string ParseWebPages::removeScripts(std::string str) {
	size_t pos;
	size_t posEnd = 0;
	std::string tag;
	do {
		pos = str.find("<script", posEnd);
		if (pos != std::string::npos) {
			std::string closeChars = "</script>";
			posEnd = str.find(closeChars, pos);
			if (posEnd != std::string::npos) {
				str.erase(pos, posEnd + closeChars.length() - pos);
				posEnd = pos;				
			}
		}
	} while (pos != std::string::npos);
	
	return str;
}