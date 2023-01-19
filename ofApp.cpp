#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetLineWidth(1.5);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->font_size = 80;
	this->font.loadFont("fonts/Kazesawa-Bold.ttf", this->font_size, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	string word = "01234567890123456789";
	int sample_count = 180;

	vector<ofColor> color_list = { ofColor(255, 0, 0), ofColor(0, 255, 0), ofColor(0, 0, 255), };

	for (int x = -200; x <= 200; x += 100) {

		for (int y = -200; y <= 200; y += 100) {

			auto noise_seed = ofRandom(1000);
			for (int i = 0; i < color_list.size() * 2; i++) {

				int word_index = ofMap(ofNoise(noise_seed, i * 0.01 + ofGetFrameNum() * 0.004), 0, 1, 0, word.size());
				ofPath chara_path = this->font.getCharacterAsPoints(word[word_index], true, false);
				vector<ofPolyline> outline = chara_path.getOutline();

				ofFill();
				ofSetColor(ofColor(color_list[i % color_list.size()], 64));
				ofBeginShape();
				for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

					if (outline_index != 0) { ofNextContour(true); }

					auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
					for (auto& vertex : vertices) {

						auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, 0);
						location = location + glm::vec3(x, y, 0);
						ofVertex(location);
					}
				}
				ofEndShape();

				ofNoFill();
				ofSetColor(ofColor(color_list[i % color_list.size()]));
				ofBeginShape();
				for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

					if (outline_index != 0) { ofNextContour(true); }

					auto vertices = outline[outline_index].getResampledByCount(sample_count).getVertices();
					for (auto& vertex : vertices) {

						auto location = vertex - glm::vec3(this->font_size * 0.5, this->font_size * -0.5, 0);
						location = location + glm::vec3(x, y, 0);
						ofVertex(location);
					}
				}
				ofEndShape();
			}
		}
	}


	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}