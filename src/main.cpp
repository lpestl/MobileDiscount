#include "ofMain.h"
#include "ofApp.h"
#include <locale>

//========================================================================
int main( ){
	//setlocale(LC_ALL, "Russian");
	//setlocale(LC_CTYPE, "UTF-8");
	setlocale(LC_ALL, "");

	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
