#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);

	action_url = "http://skidkaonline.ru/";
	ofAddListener(httpUtils.newResponseEvent, this, &ofApp::newResponse);
	httpUtils.start();

	appStatus = RESPONSE_TRUE;

	parser.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	parser.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofBackgroundGradient(ofColor::white, ofColor::black, ofGradientMode::OF_GRADIENT_CIRCULAR);
	parser.draw();
	
	switch (appStatus)
	{
	case ERROR_CONNECTION:
		ofSetColor(255, 0, 0);
		ofDrawBitmapString("[WARNING] No reply. Check your Internet connection.", 20, 60);
		break;
	case RESPONSE_TRUE:
		ofSetColor(0, 255, 0);
		ofDrawBitmapString(responseStr, 20, 60);
		break;
	default:
		ofSetColor(255, 255, 0);
		ofDrawBitmapString("[WARNING] _appStatus_ is wrong!", 20, 60);
		break;
	}
}

//--------------------------------------------------------------
void ofApp::newResponse(ofxHttpResponse & response) {
	//responseStr = ofToString(response.status) + ": " + (string)response.responseBody;
	if (response.status != -1) {
		responseStr = response.responseBody;
		appStatus = RESPONSE_TRUE;
		getLinks();
	}
	else {
		appStatus = ERROR_CONNECTION;
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	ofxHttpForm form;
	form.action = action_url;
	form.method = OFX_HTTP_POST;
	httpUtils.addForm(form);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::getLinks() {
	std::vector<std::string> links = parser.getAhrefs(responseStr);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}