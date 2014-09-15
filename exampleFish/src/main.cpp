#include "ofMain.h"
#include "ofApp.h"
#include "ofAppNoWindow.h"

//========================================================================
int main( ){
    ofAppNoWindow window;
    ofSetupOpenGL(&window, 1024,768,OF_FULLSCREEN);			// <-------- setup the GL context
    //ofSetupOpenGL(1024, 768, OF_WINDOW);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
