//
//  BlobInfo.cpp
//  emptyExample
//
//  Created by Martijn Mellema on 05-09-14.
//
//

#include "BlobInfo.h"

#include "Blob.h"


BlobInfo::BlobInfo(int id) {
    id = id;
    status = FREE;
}

// . . . . . . . . . . . . . . . . . . . . . .

void BlobInfo::set(Blob* b, int updateCountNumber) {
    blob = b;
    updateCountNumber = updateCountNumber;
    minX = b->getMinX();
    minY = b->getMinY();
    maxX = b->getMaxX();
    maxY = b->getMaxY();
    centerX = b->getCenterX();
    centerY = b->getCenterY();
    
    b->blobInfo = this;
}


// . . . . . . . . . . . . . . . . . . . . . .

float BlobInfo::width() {
    return maxX - minX;
}

// . . . . . . . . . . . . . . . . . . . . . .

float BlobInfo::height() {
    return maxY - minY;
}

// . . . . . . . . . . . . . . . . . . . . . .

string BlobInfo::getStatus() {
    return ofToString(BlobInfo::status);
}

// . . . . . . . . . . . . . . . . . . . . . .

void BlobInfo::drawBounding () {
    ofPushStyle();
    ofRectMode(CORNERS);
    ofRect(minX, minY, maxX, maxY);
    ofPopStyle();
}

// . . . . . . . . . . . . . . . . . . . . . .


/*
 Only works when normalize is used, see BlobFinder.
 */
void BlobInfo::drawBounding (float x, float y, float w, float h) {
    
    ofPushMatrix();
    ofTranslate(x, y);
    
    ofPushStyle();
    ofRectMode(CORNERS);
    ofRect(minX * w, minY * h, maxX * w, maxY * h);
    ofPopStyle();
    
    ofPopMatrix();
}

// . . . . . . . . . . . . . . . . . . . . . .

