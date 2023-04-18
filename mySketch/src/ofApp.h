
#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void audioIn(ofSoundBuffer &input);
	void exit();
	void loadImages();
	ofPath imageToPath(ofImage image, float threshold);

	ofSoundPlayer audioFile;
	ofSoundStream soundStream;
	ofSoundBuffer soundBuffer;
	vector<float> fftBins;
	int fftSize;
	int bufferSize;

	float threshold;
	ofImage currentFrame;
	bool isPeakFrame;
	vector<ofVec2f> curvePoints;
	bool isFirstFrame;
	int fadeStartTime;
	ofImage lastMaskedImage;
	int fadeOutDuration;
	int remainingFadeOutTime;
	ofPath displayedPath;
	float pathAlpha;
	vector<ofImage> images;
	vector<ofPath> paths;

	ofFbo backgroundFbo;
	ofFbo shapeFbo;

};