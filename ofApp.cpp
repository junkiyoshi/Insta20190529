#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int n = 0; n < 2; n++) {

		auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
		auto radius = 50;
		auto len = 15;
		auto noise_step = 0.005;
		auto frame_scale = 3;
		auto base = glm::vec3(ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + len * frame_scale) * noise_step), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + len * frame_scale) * noise_step), 0, 1, n * 360, (n + 1) * 360), 0);

		ofFill();
		ofSetColor(139);
		ofDrawSphere(base, radius);

		for (int i = 0; i < len; i++) {

			base = glm::vec3(ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + i * frame_scale) * noise_step), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + i * frame_scale) * noise_step), 0, 1, n * 360, (n + 1) * 360), 0);
			auto prev_base = glm::vec3(ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + i * frame_scale - 1) * noise_step), 0, 1, 0, ofGetWidth()), ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + i * frame_scale - 1) * noise_step), 0, 1, n * 360, (n + 1) * 360), 0);
			auto direction = base - prev_base;
			auto theta = atan2(direction.y, direction.x);

			ofNoFill();
			ofSetColor(39, ofMap(i, 0, len, 32, 255));
			ofBeginShape();
			for (int deg = 0; deg < 360; deg += 3) {

				auto point = glm::vec3(radius * 1.2 * cos(deg * DEG_TO_RAD), radius * 1.2 * sin(deg * DEG_TO_RAD), 0);
				auto rotation_x = glm::rotate(glm::mat4(), (float)(PI * 0.5), glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), (float)(theta + PI * 0.5), glm::vec3(0, 1, 0));
				point = base + glm::vec4(point, 0) * rotation_y * rotation_x;

				ofVertex(point);
			}
			ofEndShape(true);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}