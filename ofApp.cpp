#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 30, true, true, true);

	for (int i = 0; i < 300; i++) {

		auto location = glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
		location = glm::normalize(location) * ofRandom(150, 200);
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

		ofPushMatrix();
		ofTranslate(this->location_list[i]);
		ofRotateX(ofMap(ofNoise(ofRandom(10000), ofGetFrameNum() * 0.005), 0, 1, -180, 180));
		ofRotateY(ofMap(ofNoise(ofRandom(10000), ofGetFrameNum() * 0.005), 0, 1, -180, 180));
		ofRotateZ(ofMap(ofNoise(ofRandom(10000), ofGetFrameNum() * 0.005), 0, 1, -180, 180));

		
		char noise_value = ofMap(ofNoise(this->location_list[i].x * 0.008, this->location_list[i].y * 0.008, this->location_list[i].z * 0.008, ofGetFrameNum() * 0.01), 0, 1, '0', 'Z');
		auto path = font.getCharacterAsPoints(noise_value, true, false);
		auto outline = path.getOutline();

		ofFill();
		i == this->target_index ? ofSetColor(239, 0, 0) : ofSetColor(239);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			auto vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				auto location = glm::vec2(vertices[vertices_index].x - this->font.stringWidth(string{ noise_value }) * 0.5, vertices[vertices_index].y + this->font.stringHeight(string{ noise_value }) * 0.5);
				ofVertex(location);
			}
		}
		ofEndShape(true);

		ofNoFill();
		ofSetColor(39);
		ofBeginShape();
		for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

			if (outline_index != 0) { ofNextContour(true); }

			auto vertices = outline[outline_index].getVertices();
			for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

				auto location = glm::vec2(vertices[vertices_index].x - this->font.stringWidth(string{ noise_value }) * 0.5, vertices[vertices_index].y + this->font.stringHeight(string{ noise_value }) * 0.5);
				ofVertex(location);
			}
		}
		ofEndShape(true);

		ofPopMatrix();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}