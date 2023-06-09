# Audio Phase Scope Visualiser

## Functionality

This repo is for an openFrameworks sketch that takes an audio file and some images as an input, and plays a visual sketch that syncs to the audio in real-time. It can also render the output as a video, matching the duration of the source audio file, and with the source audio file as the audio track. 

Here is a full description of exactly what this sketch should do:

1. Take an audio file (which may vary in duration from 10 seconds to 10 minutes), a directory of png files, and an integer for tempo (in beats per minute) as an input
2. Before drawing anything, analyse the images for luminance and store a map of the luminance of the image
3. Create a 1920x1080 canvas for displaying anythign that is drawn
4. Draw an audio phase correlation meter [like this one](https://images.squarespace-cdn.com/content/v1/61362d681567f64bc6563ba1/e9b8e575-1264-41f4-92e7-71d2be395ba1/PCM-gif.gif?format=750w0), that displays a continuous line on a quadrilateral plot, illustrating the difference between the left and right channels
5. Redraw at 30fps, synchronised with the audio as it plays
6. Detect transient peaks in the audio signal between 100hz and 700hz
7. If a peak is detected, and there has not been a peak detected for a minimum of half a beat (based on the tempo/bpm provided), set a boolean called 'displayPeak' to 'true'
8. If 'displayPeak' is 'true', select one of the input image luminance maps at random and trace a vector line over the areas of the image that are above a threshold of luminance
9. If 'displayPeak' is 'true', instead of displaying a line that represents phase correlation, the phase scope should instead display the resulting vector line from tracing the luminant parts of the image in step 6
10. The line displayed in step 7 should be scaled to the maximum size it can be without exceeding the bounds of the scope
11. When the sketch is run, it should play in real-time
12. There must be a build option to render the full video as a single video file, including both the sketch visuals, and the original audio file playing in sync

## Additional information

This code is directly based on a previous sketch that was written in Processing. [Here is the code for the Processing sketch](https://github.com/ChewyJetpack/phasescope-ai-visualiser/raw/main/processing/sketch)

Here is the main.cpp file from the openFrameworks sketch: https://raw.githubusercontent.com/ChewyJetpack/phasescope-ai-visualiser/main/mySketch/src/main.cpp

Here is the ofApp.cpp file from the openFrameworks sketch: https://raw.githubusercontent.com/ChewyJetpack/phasescope-ai-visualiser/main/mySketch/src/ofApp.cpp

Here is the ofApp.h file from the openFrameworks sketch: https://raw.githubusercontent.com/ChewyJetpack/phasescope-ai-visualiser/main/mySketch/src/ofApp.h

While the openFrameworks sketch is based on the Processing sketch, it does not need to be a direct recreation. The most important aspect of the Processing sketch to be adhered to is the phase scope, in terms of its dimensions, appearance, and functionality, though enhancements and changes to this will be made throughout the process.

## System and performance requirements

All code should run on Visual Studio 2017 in Windows 11. Any libraries used should be compatible with this. The target platform is Windows.

The specific openFrameworks version used is 0.11.2 (of_v0.11.2_vs2017_release).

In terms of performance, the sketch should be able to run in realtime at a minimum of 30fps. It should be at least 3x more efficient on hardware resources than the Processing sketch.

## Coding style

The code should use clear and descriptive naming conventions, and should be thoroughly commented so that it is easily understandable to human engineers.
