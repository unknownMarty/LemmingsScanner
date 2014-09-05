//
//  BlobBase.h
//  emptyExample
//
//  Created by Martijn Mellema on 02-09-14.
//
//

#ifndef emptyExample_BlobBase_h
#define emptyExample_BlobBase_h
#pragma once
#include "ofMain.h"

/**
 * Created by doekewartena on 6/17/14.
 */

class Blob;


class BlobBase {
private:
   
 

public:
    // parent blob
    Blob * pb;
    
    // we store this also in the base so it's
    // more easy to init stuff
    int maxCornerIndexes;
    
    
    
    float minX, minY, maxX, maxY;
    
    
    int nOfCornerIndexes;
    // for when the ofVec3fs are created (0, 0, 0)
    bool didInitCornerVectors = false;
    bool cornerVectorsComputed;
    
    // we store this also in the base so it's
    // more easy to init stuff
    int maxEdgeIndexes;
    // we will only create this when the user
    // chooses to add all edge pixels of the contour
    // also he has to do this manually
    // we needed to do it for the cornerIndexes
    // to get the blob size
    vector<ofVec3f> edgeVectors;
    int nOfEdgeIndexes;
    // for when the ofVec3fs are set (someX, someY, 0)
    bool didInitEdgeVectors = false;
    bool edgeVectorsComputed;
    
    vector<ofVec3f> cornerVectors;
    
    int imageWidth;
    int imageHeight;
    
    
    BlobBase() ;
    
//    BlobBase(Blob pb) {
//        pb = pb;
//    }
    
    
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    void init(int maxCornerIndexes, int maxEdgeIndexes);
    
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    /**
     * This method gets only called when needed atm.
     * If memory is no problem then you could call this for every blob.
     */
    void initCornerVectors();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    void initEdgeVectors() ;
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    void reset();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    // todo move to blobBase
    bool onLine(ofVec3f a, ofVec3f b, float x, float y, float epsilon);
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    float getMinX();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    float getMaxX();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    float getMinY();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    float getMaxY();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    float getWidth();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    float getHeight();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    float getCenterX();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    float getCenterY();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    ofVec3f lastCorner();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    void cornerIndexesToVector();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    bool isCornerVectorsComputed();
    
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    
    vector<ofVec3f> getCornerVectors();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    
    void edgeIndexesToVector();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    bool isEdgeVectorsComputed();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    
    vector<ofVec3f> getEdgeVectors();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    /**
     *
     * @param x
     * @param y
     * @param edgeHitEpsilon  small number, should depend on normalized or not
     * @return
     */
    bool edgeHit(float x, float y, float edgeHitEpsilon);
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    
    
    void draw();
    
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    
    void draw(float x, float y, float w, float h);
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    void drawBounding ();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    void drawBounding ( float x, float y, float w, float h);    
    
    
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    
};



#endif
