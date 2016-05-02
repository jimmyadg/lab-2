#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#define _USE_LIVE_VIDEO	


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        int checkCollision(int px, int py, int psize, float obx, float oby, float obxs, float obys);
    
    
        ofImage face;
        ofImage niko;
        ofImage jen;
        ofImage food;
		ofSoundPlayer sound;
        ofSoundPlayer cat1;
        ofSoundPlayer cat2;
        ofSoundPlayer eat;
        ofVideoPlayer video;
        ofTrueTypeFont myFont;
    
        #ifdef _USE_LIVE_VIDEO
		  ofVideoGrabber 		vidGrabber;
        #else
		  ofVideoPlayer 		vidPlayer;
        #endif
    
        ofxCvColorImage			colorImg;
    
        ofxCvGrayscaleImage 	grayImage;
        ofxCvGrayscaleImage 	grayBg;
        ofxCvGrayscaleImage 	grayDiff;
    
        ofxCvContourFinder 	contourFinder;
    
        int 				threshold;
        bool				bLearnBakground;
};


