#pragma once

#include "ofMain.h"

class testApp : public ofBaseApp{

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
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofVideoGrabber 		vidGrabber;
		unsigned char * 	videoInverted;
		ofTexture			videoTexture;
		int 				camWidth;
		int 				camHeight;
		unsigned char              rp;
		unsigned char              gp;
        unsigned char              bp;
        unsigned char       threshold;
        ofTrueTypeFont              myfont;
        char fpsStr[255];
        int kalib1[2];
        int kalib2[2];
        int kalib3[2];
        int kalib4[2];
		int kalib5[2];
        int curX;
        int curY;
        int areaX;
        int areaY;
        int areaW;
        int areaH;
        int screenX;
        int screenY;
        int kalibCircOffs;
        char strKalib1[255];
        char strKalib2[255];
        char strKalib3[255];
        char strKalib4[255];
        char strMapping[255];
        float mappingX;
        float mappingY;
        int kalibCirc1X,
            kalibCirc1Y,
            kalibCirc2X,
            kalibCirc2Y,
            kalibCirc3X,
            kalibCirc3Y,
            kalibCirc4X,
            kalibCirc4Y;
			kalibCirc5X,
            kalibCirc5Y;
		int offsX,offsY;
        int resCoord[2]; //Resulting circle coordinate
        bool kalibDone;
        //ofRect              activeArea;

};
