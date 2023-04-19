
#pragma once

#include "ofMain.h"
#include "ofxAudioAnalyzer.h"
#include "ofxVideoRecorder.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void audioIn(ofSoundBuffer &input);
	void exit();

	ofSoundStream soundStream;
	ofxAudioAnalyzer audioAnalyzer;
	ofSoundBuffer soundBuffer;

	float rms, pitch, peakFrequency;
	bool transientDetected;
	float transientThreshold;

	int bufferSize;
	int sampleRate;

	vector<ofImage> images;
	int currentImageIndex;
	int numImages;
	float imageThreshold;

	ofFbo fbo;
	ofPixels pixels;
	ofxVideoRecorder recorder;

	float tempo;
	float timeBetweenPeaks;
	float lastPeakTime;

	bool displayPeak;

	void loadImages(string dirPath);
	void analyzeImages();
	vector<vector<float>> imageLuminanceMaps;

	void drawPhaseScope();
	void drawImageTrace();

	ofRectangle scopeRect;

	bool renderingVideo;
};
