#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ContourWalker.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mousePressed(int x, int y, int button);
    ContourWalker * blob;
	        
};

#endif
