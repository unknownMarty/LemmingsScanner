//
//  Blob.cpp
//  emptyExample
//
//  Created by Martijn Mellema on 05-09-14.
//
//

#include "Blob.h"

#include "BlobInfo.h"


Blob::Blob(int maxCornerIndexes, int maxEdgeIndexes) {
    init(maxCornerIndexes, maxEdgeIndexes);
}



// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void Blob::init(int maxCornerIndexes, int maxEdgeIndexes) {
    
    // BlobBase::init(maxCornerIndexes, maxEdgeIndexes);
    
    cornerIndexes = new int[maxCornerIndexes];
    
    for (int i = 0; i < maxCornerIndexes; i++) {
        cornerVectors.push_back(ofVec3f());
    }
    
    if (maxEdgeIndexes >= 0) {
        edgeIndexes = new int[maxEdgeIndexes];
    }
    else {
        // this has to do with the try block
        // and the correct error
        // atm maxEdgeIndex can be set to -1
        // if we are not interested
        edgeIndexes = new int[0];
    }
    
    // for now we keep the parent NULL
    // atm we need to overwrite every method that needs a parent anyway
    //pb = this;
    
    normalized = new BlobBase;
    
    normalized->init(maxCornerIndexes, maxEdgeIndexes);
    
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


bool Blob::edgeHit(float x, float y, float edgeHitEpsilon) {
    
    // todo, check what is computed,
    // based on that call either normalized or not
    
    // return BlobBase::edgeHit(x, y, edgeHitEpsilon);
    return true;
}



// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


void Blob::reset() {
    
    reset();
    normalized->reset();
    
    
    containingBlobs.clear();
    enclosedBlobs.clear();
    
    blobInfo = NULL;
    
    containingBlobsComputed = false;
    enclosedBlobsComputed = false;
    
    enclosingParent = NULL;
    
    depth = -1;
}


// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void Blob::setImageSize(int width, int height) {
    setImageWidth(width);
    setImageHeight(height);
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void Blob::setImageWidth(int width) {
    imageWidth = width;
    normalized->imageWidth = width;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void Blob::setImageHeight(int height) {
    imageHeight = height;
    normalized->imageHeight = height;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .



// todo, still add this?
//    int nOfEdgeIndexes() {
//        return nOfEdgeIndexes;
//    }




// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

bool Blob::isOuterContour() {
    return mIsOuterContour;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

bool Blob::isInnerContour() {
    return !isOuterContour();
}


// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .



void Blob::addToCornerIndexes(int index) {
    try {
        cornerIndexes[nOfCornerIndexes++] = index;
        normalized->nOfCornerIndexes = nOfCornerIndexes;
    }
    catch (exception e) {
        // todo give error of how to prevent
        
    }
}


// . . . . . . . . . . . . . . . . . . . . . . .


void Blob::addToEdgeIndexes(int index) {
    try {
        edgeIndexes[nOfEdgeIndexes++] = index;
        normalized->nOfEdgeIndexes = nOfEdgeIndexes;
    }
    catch (exception e) {
        // todo give error of how to prevent
    }
}

// . . . . . . . . . . . . . . . . . . . . . . .



void Blob::cornerIndexesToVector() {
    
    if (cornerVectorsComputed) return;
    
    BlobBase::initCornerVectors();
    
    minX = cornerIndexes[0] % imageWidth;
    maxX = minX;
    minY = (cornerIndexes[0] - minX) / imageWidth;
    maxY = minY;
    
    minXCornerPixelIndex = minYCornerPixelIndex = maxXCornerPixelIndex = maxYCornerPixelIndex = cornerIndexes[0];
    
    
    for (int i = 0; i < nOfCornerIndexes; i++) {
        
        int x = cornerIndexes[i] % imageWidth;
        int y = (cornerIndexes[i] - x) / imageWidth;
        
        cornerVectors.at(i).x = x;
        cornerVectors.at(i).y = y;
        
        if (x < minX ) {
            minX = x;
            minXCornerPixelIndex = cornerIndexes[i];
        }
        else if (x > maxX ) {
            maxX = x;
            maxXCornerPixelIndex = cornerIndexes[i];
        }
        if (y < minY ) {
            minY = y;
            minYCornerPixelIndex = cornerIndexes[i];
        }
        else if (y > maxY ) {
            maxY = y;
            maxYCornerPixelIndex = cornerIndexes[i];
        }
        
    }
    
    cornerVectorsComputed = true;
    
}

// . . . . . . . . . . . . . . . . . . . . . . .

void Blob::setMinAndMax() {
    
    // first not normalized
    minX = minXCornerPixelIndex % imageWidth;
    
    float x = minYCornerPixelIndex % imageWidth;
    minY = (minYCornerPixelIndex - x) / imageWidth;
    
    maxX = maxXCornerPixelIndex % imageWidth;
    
    x = maxYCornerPixelIndex % imageWidth;
    maxY = (maxYCornerPixelIndex - x) / imageWidth;
    
    // now normalized
    normalized->minX = ofNormalize(minX, 0, imageWidth);
    normalized->maxX = ofNormalize(maxX, 0, imageWidth);
    normalized->minY = ofNormalize(minY, 0, imageHeight);
    normalized->maxY = ofNormalize(maxY, 0, imageHeight);
    
}


// . . . . . . . . . . . . . . . . . . . . . . .


void Blob::edgeIndexesToVector() {
    
    if (edgeVectorsComputed) return;
    
    BlobBase::initEdgeVectors();
    
    for (int i = 0; i < nOfEdgeIndexes; i++) {
        int x = edgeIndexes[i] % imageWidth;
        
        edgeVectors.at(i).y = (edgeIndexes[i] - x) / imageWidth;
        edgeVectors.at(i).x = x;
        
    }
    
    edgeVectorsComputed = true;
    
}

// . . . . . . . . . . . . . . . . . . . . . . .

vector<Blob*> Blob::getContainingBlobs() {
    checkForContainingBlobsComputed("getContainingBlobs");
    return containingBlobs;
}


// . . . . . . . . . . . . . . . . . . . . . . .

vector<Blob*> Blob::getEnclosedBlobs() {
    checkForEnclosedBlobsComputed("getEnclosedBlobs");
    return enclosedBlobs;
}




// . . . . . . . . . . . . . . . . . . . . . . .


/*
 It should already be sure that this blob really contains the blob to add.
 This method takes care of the hierarchy
 */
void Blob::addContainingBlob(Blob* blobToAdd, int debugDepth) {
    
    //PApplet.println(debugDepth);
    //todo how fix this?
    //        if (blobToAdd == this) {
    //            return;
    //        }
    
    if (containingBlobs.size() == 0) {
        containingBlobs.push_back(blobToAdd);
        return;
    }
    
    ofRectangle r1;
    
    r1 = ofRectangle(blobToAdd->getMinX(), blobToAdd->getMinY(), blobToAdd->getWidth(), blobToAdd->getHeight());
    
    ofRectangle r2;
    
    // first check if we already have a containing blob that
    // can hold the one we like to add
    // PApplet.println(containingBlobs.size());
    
    for (int x=0; x< containingBlobs.size(); x++) {
        Blob* b  = containingBlobs.at(x);
        
        r2 = ofRectangle(b->getMinX(), b->getMinY(), b->getWidth(), b->getHeight());
        
        //PApplet.println(r1.getMinX(), r1.getMinY(), r1.getWidth(), r1.getHeight());
        //PApplet.println(r2.getMinX(), r2.getMinY(), r2.getWidth(), r2.getHeight());
        
        if (r2.inside(r1)) {
            b->addContainingBlob(blobToAdd, debugDepth+1);
            return;
        }
        
    }
    
    // it can also be that one OR MORE of the containing blobs can fit in the blob we like to add
    for (int i = containingBlobs.size()-1; i >= 0; i--) {
        Blob* b = containingBlobs.at(i);
        
        r2 = ofRectangle(b->getMinX(), b->getMinY(), b->getWidth(), b->getHeight());
        
        if (r1.inside(r2)) {
            
            containingBlobs.erase(containingBlobs.begin()+i);

            // no need to do it recursive since we know
            // the rest will fits as well
            //blobToAdd->addContainingBlob(b);
            // so instead we use
            blobToAdd->containingBlobs.push_back(b);
        }
        
    }
    containingBlobs.push_back(blobToAdd);
    
}



// . . . . . . . . . . . . . . . . . . . . . . .


void Blob::checkForContainingBlobsComputed(string methodName) {
    if (!containingBlobsComputed) {
        cout<<"ERROR in "+methodName+", containing blobs blobs are not computed!"<<endl;
       
    }
}

// . . . . . . . . . . . . . . . . . . . . . . .


void Blob::checkForEnclosedBlobsComputed(string methodName) {
    if (!enclosedBlobsComputed) {
        cout<<"ERROR in "<<typeid(this).name()<<"."<<methodName<<", enclosed blobs blobs are not computed!"<<endl;
    }
}

// . . . . . . . . . . . . . . . . . . . . . . .

// we have this cause it requires
// EnclosedBlobsComputed
// which can only be done with the BlobFinder
void Blob::computeDepth(int depth) {
    
    this->depth = depth;
    
    for (Blob* b : enclosedBlobs) {
        b->computeDepth(depth+1);
    }
}


// . . . . . . . . . . . . . . . . . . . . . . .

int Blob::getDepth() {
    checkForEnclosedBlobsComputed("getDepth");
    return depth;
}

// . . . . . . . . . . . . . . . . . . . . . . .

bool Blob::hasParent() {
    
    //PApplet.println("hasParent", containingBlobsComputed, enclosedBlobsComputed);
    
    checkForEnclosedBlobsComputed("hasParent");
    
    return enclosingParent == NULL ? false : true;
}


// . . . . . . . . . . . . . . . . . . . . . . .

bool Blob::hasChildren() {
    
    checkForEnclosedBlobsComputed("hasChildren");
    
    return enclosedBlobs.size() > 0 ? true : false;
}

// . . . . . . . . . . . . . . . . . . . . . . .


void Blob::draw() {
    
    if (!cornerVectorsComputed && normalized->cornerVectorsComputed) {
        normalized->draw();
    }
    else {
        draw(0, 0, 1, 1);
    }
}


// . . . . . . . . . . . . . . . . . . . . . . .



void Blob::draw(float x, float y, float w, float h) {
    if (normalized->cornerVectorsComputed) {
        normalized->draw( x, y, w, h);
    }
    else {
        cout<<"ERROR in Blob: normalized vectors are not computed!\nCall either normalized->draw()"<<endl;
    }
}


// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .



void Blob::drawBounding () {
    
    if (!cornerVectorsComputed && normalized->cornerVectorsComputed) {
        normalized->drawBounding();
    }
    else {
        drawBounding( 0, 0, 1, 1);
    }
    
}



// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .


void Blob::drawBounding ( float x, float y, float w, float h) {
    if (normalized->cornerVectorsComputed) {
        normalized->drawBounding(x, y, w, h);
    }
    else {
        cout<<"ERROR in Blob: normalized vectors are not computed!\nCall either normalized->drawBounding()"<<endl;
    }
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

