#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 28);

	for (int i = 0; i < 750; i++) {

		auto location = glm::vec3(ofRandom(-300, 300), ofRandom(-300, 300), ofRandom(-300, 300));
		location = glm::normalize(location) * ofRandom(200, 600);
		this->location_list.push_back(location);
	}

	this->target_index = ofRandom(this->location_list.size());
	this->prev_index = ofRandom(this->location_list.size());
	this->camera_index = ofRandom(this->location_list.size());
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	int param = ofGetFrameNum() % 120;
	if (param == 0) {
	
		this->camera_index = this->prev_index;
		this->prev_index = this->target_index;
		this->target_index = (int)(ofRandom(1000) + ofGetFrameNum()) % this->location_list.size();
	}

	if (param <= 60) {
	
		auto tmp = this->location_list[this->prev_index] - this->location_list[this->camera_index];
		this->camera_location = this->location_list[this->camera_index] + tmp * (param / 60.f);

		tmp = this->location_list[this->target_index] - this->location_list[this->prev_index];
		this->target_location = this->location_list[prev_index] + tmp * (param / 60.f);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.setPosition(this->camera_location);
	this->cam.lookAt(this->target_location);
	this->cam.begin();

	for (int i = 0; i < this->location_list.size(); i++) {

		i == this->target_index ? ofSetColor(239, 0, 0) : ofSetColor(39);

		ofPushMatrix();
		ofTranslate(this->location_list[i]);
		ofRotateX(ofMap(ofNoise(ofRandom(10000), ofGetFrameNum() * 0.005), 0, 1, -180, 180));
		ofRotateY(ofMap(ofNoise(ofRandom(10000), ofGetFrameNum() * 0.005), 0, 1, -180, 180));
		ofRotateZ(ofMap(ofNoise(ofRandom(10000), ofGetFrameNum() * 0.005), 0, 1, -180, 180));


		char noise_value = ofMap(ofNoise(this->location_list[i].x * 0.008, this->location_list[i].y * 0.008, this->location_list[i].z * 0.008, ofGetFrameNum() * 0.005), 0, 1, 'A', 'Z');
		this->font.drawString({ noise_value }, -14, -14);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}