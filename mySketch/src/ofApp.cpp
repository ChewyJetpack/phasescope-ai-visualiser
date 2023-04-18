
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	ofBackground(15, 12, 17);
	ofSetCircleResolution(100);

	loadImages();

	audioFile.load("your_audio_file.wav");
	audioFile.play();


	bufferSize = 512;
	fftSize = bufferSize / 2;
	fftBins.resize(fftSize);

	audioFile.setLoop(true);
	soundStream.setup(this, 0, 2, 44100, bufferSize, 4);

	backgroundFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);
	shapeFbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);

	threshold = 0.95;
}

//--------------------------------------------------------------
void ofApp::update() {
	audioFile.update();
	soundBuffer = audioFile.getSoundBuffer();
	soundBuffer.getFFT(fftBins.data(), fftSize);
}

//--------------------------------------------------------------
void ofApp::draw() {
	// Draw background and shapes in separate Fbo objects
	backgroundFbo.begin();
	ofClear(15, 12, 17);

	// drawBackground function contents here
	// ...

	backgroundFbo.end();

	shapeFbo.begin();
	ofClear(0, 0, 0, 0);

	// drawShapes function contents 
	for (int i = 0; i < fftSize; i++) {
		float binWidth = (float)ofGetWidth() / (float)fftSize;
		float binHeight = fftBins[i] * ofGetHeight();
		ofSetColor(255);
		ofDrawRectangle(i * binWidth, ofGetHeight() - binHeight, binWidth, binHeight);
	}
	// ...

	shapeFbo.end();

	// Combine background and shapes with blendMode
	backgroundFbo.draw(0, 0);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	shapeFbo.draw(0, 0);
	ofDisableBlendMode();
}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer &input) {
	input.getFFT(fftBins.data(), fftSize);
}

//--------------------------------------------------------------
void ofApp::exit() {
	audioFile.stop();
}

//--------------------------------------------------------------
void ofApp::loadImages() {
	ofDirectory dir("images/");
	dir.allowExt("png");
	dir.listDir();

	for (int i = 0; i < dir.size(); i++) {
		ofImage img;
		img.load(dir.getPath(i));
		images.push_back(img);
		paths.push_back(imageToPath(img, 40));
	}
}

//--------------------------------------------------------------
ofPath ofApp::imageToPath(ofImage img, float threshold) {
	ofPath path;
	img.setImageType(OF_IMAGE_GRAYSCALE);
	img.update();

	int centerX = img.getWidth() / 2;
	int centerY = img.getHeight() / 2;

	for (int y = 0; y < img.getHeight(); y++) {
		for (int x = 0; x < img.getWidth(); x++) {
			ofColor c = img.getColor(x, y);
			float val = c.getBrightness();

			if (val > threshold) {
				path.lineTo(x - centerX, y - centerY);
			}
		}
	}
	return path;
}