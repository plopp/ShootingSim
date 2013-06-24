#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){

	camWidth 		= 320;	// try to grab at this size.
	camHeight 		= 240;

	vidGrabber.setVerbose(true);
	vidGrabber.initGrabber(camWidth,camHeight);

	videoInverted 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);

    threshold = 150;
    myfont.loadFont("arial.ttf",12);

    areaX = 0;
    areaY = 0;
    screenX = 1024;
    screenY = 768;
    areaH = screenY-areaY; //360
    areaW = screenX-areaX;
    kalibCircOffs = 50;
}


//--------------------------------------------------------------
void testApp::update(){

	ofBackground(255,255,255);

	vidGrabber.grabFrame();

	if (vidGrabber.isFrameNew()){
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = vidGrabber.getPixels();

		for (int i = 0; i < totalPixels; i+=3){
			//videoInverted[i] = 255 - pixels[i]
			rp = pixels[i];
			gp = pixels[i+1];
			bp = pixels[i+2];
			if(rp > threshold || gp > threshold || bp > threshold){


                videoInverted[i] = rp;
                videoInverted[i+1] = gp;
                videoInverted[i+2] =  bp;
                curX = (i/3)%camWidth;
                curY = (i/3)/camWidth;
                sprintf(fpsStr, "x: %d\ny: %d", curX, curY);

			}
            else
            {
                videoInverted[i] = 0;
                videoInverted[i+1] = 0;
                videoInverted[i+2] = 0;
                //sprintf(fpsStr, "x: %d\ny: %d", 0, 0);
            }
		}


		videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
    if(testApp::kalib1[0] != 0 &&
       testApp::kalib1[1] != 0 &&
       testApp::kalib2[0] != 0 &&
       testApp::kalib2[1] != 0 &&
       testApp::kalib3[0] != 0 &&
       testApp::kalib3[1] != 0 &&
       testApp::kalib4[0] != 0 &&
       testApp::kalib4[1] != 0 &&
	   testApp::kalib5[0] != 0 &&
       testApp::kalib5[1] != 0)
       {
            testApp::mappingX = 1.0/(((float)kalib2[0]-(float)kalib1[0])/((float)kalibCirc2X - (float)kalibCirc1X)); //Mapping x = skärmpixel / kamerapixel
            testApp::mappingY = 1.0/(((float)kalib3[1]-(float)kalib1[1])/((float)kalibCirc3Y - (float)kalibCirc1Y)); //Mapping x = skärmpixel / kamerapixel
			offsX = kalib5[0]-curX;
			offsY = kalib5[1]-curY;
            float pi = 3.1415;
            sprintf(testApp::strMapping, "Mapping: x=%.2f  y=%.2f  PI=%.2f", mappingX, mappingY, pi);
       }

	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetHexColor(0xffffff);
	vidGrabber.draw(20,20);
	videoTexture.draw(20+camWidth,20,camWidth,camHeight);
	ofSetColor(0, 0, 0);
	myfont.drawString(testApp::fpsStr, 100,100);

	testApp::kalibCirc1X = areaX+kalibCircOffs;
	testApp::kalibCirc1Y = areaY+kalibCircOffs;

	testApp::kalibCirc2X = screenX-kalibCircOffs;
	testApp::kalibCirc2Y = areaY+kalibCircOffs;

	testApp::kalibCirc3X = areaX+kalibCircOffs;
	testApp::kalibCirc3Y = screenY-kalibCircOffs;

	testApp::kalibCirc4X = screenX-kalibCircOffs;
	testApp::kalibCirc4Y = screenY-kalibCircOffs;

	testApp::kalibCirc5X = (screenX+screenW)/2;
	testApp::kalibCirc5Y = (screenY+screenH)/2;

	ofCircle(testApp::kalibCirc1X, testApp::kalibCirc1Y, 20);
	ofCircle(testApp::kalibCirc2X, testApp::kalibCirc2Y, 20);
	ofCircle(testApp::kalibCirc3X, testApp::kalibCirc3Y, 20);
	ofCircle(testApp::kalibCirc4X, testApp::kalibCirc4Y, 20);
	ofCircle(testApp::kalibCirc5X, testApp::kalibCirc5Y, 20);
        myfont.drawString(testApp::strKalib1, 900,100);
        myfont.drawString(testApp::strKalib2, 900,130);
        myfont.drawString(testApp::strKalib3, 900,160);
        myfont.drawString(testApp::strKalib4, 900,190);

    myfont.drawString(testApp::strMapping, 900,250);
    resCoord[0] = testApp::areaX+((int)(testApp::mappingX * (float)testApp::curX));
    resCoord[1] = testApp::areaY+((int)(testApp::mappingY * (float)testApp::curY));
    ofCircle(testApp::resCoord[0]+offsX,testApp::resCoord[1]+offsY,10);
	//ofRect(20, 20+camHeight+20, 800,400);
}


//--------------------------------------------------------------
void testApp::keyPressed  (int key){

	// in fullscreen mode, on a pc at least, the
	// first time video settings the come up
	// they come up *under* the fullscreen window
	// use alt-tab to navigate to the settings
	// window. we are working on a fix for this...

	if (key == 's' || key == 'S'){
		vidGrabber.videoSettings();
	}
    if (key == 'a' || key == 'A'){
        threshold+=1;
	}
	if (key == 'z' || key == 'Z'){
        threshold-=1;
	}
	if (key == 'q' || key == 'Q'){
        kalib1[0] = curX;
        kalib1[1] = curY;
        sprintf(testApp::strKalib1, "x: %d  y: %d", curX, curY);
	}
	if (key == 'w' || key == 'W'){
        kalib2[0] = curX;
        kalib2[1] = curY;
        sprintf(testApp::strKalib2, "x: %d  y: %d", curX, curY);

	}
	if (key == 'e' || key == 'E'){
        kalib3[0] = curX;
        kalib3[1] = curY;
        sprintf(testApp::strKalib3, "x: %d  y: %d", curX, curY);
	}
	if (key == 'r' || key == 'R'){
        kalib4[0] = curX;
        kalib4[1] = curY;
        sprintf(testApp::strKalib4, "x: %d  y: %d", curX, curY);
	}
	if (key == 't' || key == 'T'){
        kalib5[0] = curX;
        kalib5[1] = curY;
        sprintf(testApp::strKalib5, "x: %d  y: %d", curX, curY);
	}

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}
