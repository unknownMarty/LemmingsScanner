//
//  BlobBase.cpp
//  emptyExample
//
//  Created by Martijn Mellema on 04-09-14.
//
//

#include "BlobBase.h"
#include "Blob.h"


BlobBase::BlobBase() {
    
}


//    BlobBase(Blob pb) {
//        pb = pb;
//    }


// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void BlobBase::init(int maxCornerIndexes, int maxEdgeIndexes) {
    
    maxCornerIndexes = maxCornerIndexes;
    maxEdgeIndexes = maxEdgeIndexes;
    
    cornerVectors.resize(0) ;
    edgeVectors.resize(0);
    // we don't call
    // initCornerVectors()
    // or
    // initEdgeVectors()
    // cause we can't tell if the user wants them
}


// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

/**
 * This method gets only called when needed atm.
 * If memory is no problem then you could call this for every blob.
 */
void BlobBase::initCornerVectors() {
    
    if (didInitCornerVectors) return;
    
    for (int i = 0; i < maxCornerIndexes; i++) {
        cornerVectors.push_back(ofVec3f());
    }
    
    didInitCornerVectors = true;
    
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void BlobBase::initEdgeVectors() {
    
    if (didInitEdgeVectors) return;
    
    edgeVectors.resize(0);
    
    for (int i = 0; i < maxEdgeIndexes; i++) {
        edgeVectors.push_back(ofVec3f());
    }
    
    didInitEdgeVectors = true;
    
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void BlobBase::reset() {
    
    edgeVectorsComputed = false;
    cornerVectorsComputed = false;
    
    imageWidth = -1;
    imageHeight = -1;
    
    nOfCornerIndexes = 0;
    nOfEdgeIndexes = 0;
    
    // we don't clear the ArrayLists
    // since we will return a subList
    
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

// todo move to blobBase
bool BlobBase::onLine(ofVec3f a, ofVec3f b, float x, float y, float epsilon) {
    return abs(ofDist(a.x, a.y, x, y) + ofDist(x, y, b.x, b.y) - ofDist(a.x, a.y, b.x, b.y)) < epsilon;
}


// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

float BlobBase::getMinX() {
    cornerIndexesToVector();
    return minX;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

float BlobBase::getMaxX() {
    cornerIndexesToVector();
    return maxX;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

float BlobBase::getMinY() {
    cornerIndexesToVector();
    return minY;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

float BlobBase::getMaxY() {
    cornerIndexesToVector();
    return maxY;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

float BlobBase::getWidth() {
    return getMaxX() - getMinX();
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

float BlobBase::getHeight() {
    return getMaxY() - getMinY();
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

float BlobBase::getCenterX() {
    return 0.5f  * getWidth() + getMinX() ;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

float BlobBase::getCenterY() {
    return 0.5f * getHeight() + getMinY();
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

ofVec3f BlobBase::lastCorner() {
    
    cornerIndexesToVector();
    
    return cornerVectors.at(maxCornerIndexes -1);
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void BlobBase::cornerIndexesToVector() {
    
    if (cornerVectorsComputed) return;
    
    initCornerVectors();
    
    // we can only use else if
    // in the loop if we start with correct values
    // that is because at index 0 it could
    // be both minX and maxX where one stays that
    // way if there was only one pixel
    // at the min/max coordinate
    // (change is really really small but it could still cause a bug
    // if we didn't set actual values here)
    //minX = ofNormalize(pb->cornerIndexes[0] % imageWidth, 0, imageWidth);
    //maxX = minX;
    
    //cornerIndexes[0] - minX) / imageWidth;
    //todo bugged, fix and use else if again
    //minY = ofNormalize(((float)pb->cornerIndexes[0] - minX) / imageWidth, 0, imageHeight);
    //PApplet.println(minY);
    //maxY = minY;
    
    minX = FLT_MAX;
    minY = FLT_MAX;
    maxX = FLT_MIN ;
    maxY = FLT_MIN ;
    
    pb->minXCornerPixelIndex = pb->minYCornerPixelIndex = pb->maxXCornerPixelIndex = pb->maxYCornerPixelIndex = pb->cornerIndexes[0];
    
    for (int i = 0; i < pb->nOfCornerIndexes; i++) {
        
        int x = pb->cornerIndexes[i] % imageWidth;
        int y = (pb->cornerIndexes[i] - x) / imageWidth;
        
        float nx = ofNormalize(x, 0, imageWidth);
        float ny = ofNormalize(y, 0, imageHeight);
        
        cornerVectors.at(i).x = nx;
        cornerVectors.at(i).y = ny;
        
        if (x < minX ) {
            minX = x;
            pb->minXCornerPixelIndex = pb->cornerIndexes[i];
        }
        if (x > maxX ) {
            maxX = x;
            pb->maxXCornerPixelIndex = pb->cornerIndexes[i];
        }
        if (y < minY ) {
            minY = y;
            pb->minYCornerPixelIndex = pb->cornerIndexes[i];
        }
        if (y > maxY ) {
            maxY = y;
            pb->maxYCornerPixelIndex = pb->cornerIndexes[i];
        }
        
    }
    
    pb->setMinAndMax();
    
    cornerVectorsComputed = true;
    
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

bool BlobBase::isCornerVectorsComputed() {
    return cornerVectorsComputed;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


vector<ofVec3f> BlobBase::getCornerVectors() {
    
    cornerIndexesToVector();
    
    return vector<ofVec3f>(cornerVectors.begin(),cornerVectors.begin()+ nOfCornerIndexes);
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


void BlobBase::edgeIndexesToVector() {
    
    if (edgeVectorsComputed) return;
    
    initEdgeVectors();
    
    for (int i = 0; i < nOfEdgeIndexes; i++) {
        int x = pb->edgeIndexes[i] % imageWidth;
        
        edgeVectors.at(i).y = ofNormalize((pb->edgeIndexes[i] - x) / imageWidth, 0, imageHeight);
        edgeVectors.at(i).x = ofNormalize(x, 0, imageWidth);
    }
    
    edgeVectorsComputed = true;
    
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

bool BlobBase::isEdgeVectorsComputed() {
    return edgeVectorsComputed;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


vector<ofVec3f> BlobBase::getEdgeVectors() {
    
    edgeIndexesToVector();
    
    return vector<ofVec3f>(edgeVectors.begin(), edgeVectors.begin()+nOfEdgeIndexes);
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

/**
 *
 * @param x
 * @param y
 * @param edgeHitEpsilon  small number, should depend on normalized or not
 * @return
 */
bool BlobBase::edgeHit(float x, float y, float edgeHitEpsilon) {
    
    // quick test if it's worth it
    if (x < getMinX()-edgeHitEpsilon || x > getMaxX()+edgeHitEpsilon || y < getMinY()-edgeHitEpsilon || y > getMaxY()+edgeHitEpsilon) {
        return false;
    }
    
    // todo !!! check if cornerVectors etc. is computed
    
    // getMinX etc. calls this now:
    //cornerIndexesToVector();
    
    // the last one should be connected to the first
    ofVec3f pre = cornerVectors.at(nOfCornerIndexes -1);
    ofVec3f cur;
    
    for (int i = 0; i < nOfCornerIndexes; i++) {
        
        cur = cornerVectors.at(i);
        
        if(onLine(pre, cur, x, y, edgeHitEpsilon)) {
            return true;
        }
        
        pre = cur;
        
    }
    
    return false;
}



// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .



void BlobBase::draw() {
    
    cornerIndexesToVector();
    
    ofVec3f cur;
    ofBeginShape();
    
    for (int k = 0; k < nOfCornerIndexes; k++) {
        cur = cornerVectors.at(k);
        ofVertex(cur.x* imageWidth, cur.y* imageHeight);
    }
    ofEndShape();
}


// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


void BlobBase::draw(float x, float y, float w, float h) {
    
    cornerIndexesToVector();
    
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofVec3f cur;
    
    ofBeginShape();
    
    for (int k = 0; k < nOfCornerIndexes; k++) {
        cur = cornerVectors.at(k);
        ofVertex(cur.x*w, cur.y*h);
    }
    
    ofEndShape();
    
    ofPopMatrix();
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void BlobBase::drawBounding () {
    
    cornerIndexesToVector();
    
    ofPushStyle();
    ofRectMode(CORNERS);
    ofRect(getMinX()* imageWidth, getMinY()* imageHeight, getMaxX()* imageWidth, getMaxY()* imageHeight);
    ofPopStyle();
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void BlobBase::drawBounding ( float x, float y, float w, float h) {
    
    cornerIndexesToVector();
    
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofPushStyle();
    ofRectMode(CORNERS);
    ofRect(getMinX()*w, getMinY()*h, getMaxX()*w, getMaxY()*h);
    ofPopStyle();
    
    ofPopMatrix();
}


