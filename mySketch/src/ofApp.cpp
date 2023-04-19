
#include "ofApp.h"

#define PEAK_FREQUENCY 6

void ofApp::setup() {
	ofSetFrameRate(30);
	ofSetWindowTitle("Phasescope AI Visualiser");

	// Initialize audio input and analyzer
	bufferSize = 512;
	sampleRate = 44100;
	soundStream.setup(this, 0, 2, sampleRate, bufferSize, 4);
	audioAnalyzer.setup(sampleRate, bufferSize, 2);

	// Load images and analyze them
	loadImages("path/to/your/images");
	analyzeImages();

	// Initialize other variables
	tempo = 120; // Set the tempo in beats per minute
	timeBetweenPeaks = 60.0f / tempo / 2.0f;
	lastPeakTime = 0.0f;
	displayPeak = false;

	// Set up the FBO and recorder for video rendering
	fbo.allocate(1920, 1080, GL_RGBA);
	recorder.setVideoCodec("mpeg4");
	recorder.setVideoBitrate("8000k");
	renderingVideo = false;

	// Set up the scope rectangle
	scopeRect = ofRectangle(100, 100, 1720, 880);
}

void ofApp::loadImages(string dirPath) {
	ofDirectory dir(dirPath);
	if (dir.exists()) {
		dir.listDir();
		for (auto &file : dir.getFiles()) {
			ofImage img;
			img.load(file.getAbsolutePath());
			images.push_back(img);
		}
	}
	numImages = images.size();
}

void ofApp::analyzeImages() {
	for (auto &img : images) {
		vector<float> luminanceMap;
		for (int y = 0; y < img.getHeight(); y++) {
			for (int x = 0; x < img.getWidth(); x++) {
				ofColor c = img.getColor(x, y);
				float luminance = c.r * 0.2126 + c.g * 0.7152 + c.b * 0.0722;
				luminanceMap.push_back(luminance);
			}
		}
		imageLuminanceMaps.push_back(luminanceMap);
	}
}


void ofApp::audioIn(ofSoundBuffer &input) {
	// Analyze the input sound buffer
	audioAnalyzer.analyze(input);

	// Get the values we need for transient detection
	rms = audioAnalyzer.getValue(RMS, 0);
	peakFrequency = audioAnalyzer.getValue(static_cast<ofxAAAlgorithm>(PEAK_FREQUENCY), 0);

	// Check if a transient peak is detected
	if (peakFrequency > 100 && peakFrequency < 700 && ofGetElapsedTimef() - lastPeakTime > timeBetweenPeaks) {
		transientDetected = true;
		lastPeakTime = ofGetElapsedTimef();
	}
	else {
		transientDetected = false;
	}
}


void ofApp::update() {
	// If a transient peak is detected, set displayPeak to true
	if (transientDetected) {
		displayPeak = true;
		currentImageIndex = ofRandom(numImages);
	}
	else {
		displayPeak = false;
	}
}


void ofApp::drawPhaseScope() {
	// Draw the phase correlation meter based on the audio input
	// This is a placeholder implementation; you can replace it with your specific phase scope drawing code
	ofSetColor(255);
	ofDrawRectangle(scopeRect);
	ofSetColor(0);
	ofDrawCircle(scopeRect.getCenter(), rms * scopeRect.getWidth() / 2.0);
}

void ofApp::drawImageTrace() {
	// Draw the image trace based on the luminance map of the current image
	// This is a placeholder implementation; you can replace it with your specific image trace drawing code
	ofSetColor(255);
	ofDrawRectangle(scopeRect);
	ofSetColor(0);
	ofPushMatrix();
	ofTranslate(scopeRect.getTopLeft());
	vector<float> &luminanceMap = imageLuminanceMaps[currentImageIndex];
	for (int y = 0; y < images[currentImageIndex].getHeight(); y++) {
		for (int x = 0; x < images[currentImageIndex].getWidth(); x++) {
			float luminance = luminanceMap[y * images[currentImageIndex].getWidth() + x];
			if (luminance > imageThreshold) {
				ofDrawRectangle(x * scopeRect.getWidth() / images[currentImageIndex].getWidth(),
					y * scopeRect.getHeight() / images[currentImageIndex].getHeight(),
					scopeRect.getWidth() / images[currentImageIndex].getWidth(),
					scopeRect.getHeight() / images[currentImageIndex].getHeight());
			}
		}
	}
	ofPopMatrix();
}

void ofApp::draw() {
	fbo.begin();
	ofClear(0, 0, 0, 255);

	// Draw the phase scope or image trace depending on displayPeak
	if (displayPeak) {
		drawImageTrace();
	}
	else {
		drawPhaseScope();
	}

	fbo.end();

	// Draw the FBO to the screen
	fbo.draw(0, 0);

	// If rendering video, save the current frame
	if (renderingVideo) {
		fbo.readToPixels(pixels);
		recorder.addFrame(pixels);
	}
}

void ofApp::exit() {
	audioAnalyzer.exit();
	soundStream.stop();
	soundStream.close();
}
