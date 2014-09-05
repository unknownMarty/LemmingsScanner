//
//  Blob.h
//  emptyExample
//
//  Created by Martijn Mellema on 02-09-14.
//
//

#ifndef emptyExample_Blob_h
#define emptyExample_Blob_h
#include "ofMain.h"
#include "BlobBase.h"

class BlobInfo;

/**
 * Created by doekewartena on 4/30/14.
 */
class Blob  : public BlobBase {
    
private:
    
    
    
public:
    
    int* cornerIndexes;
    
    int scanningStartIndex;
    
    // optional the user can choose to
    // add all edge pixels of the contour
    // this will take a lot more
    // memory but can be very useful in
    // some cases
    // todo is set temp to public
    int* edgeIndexes;
    // nOfEdgeIndexes is in BlobBase
    
    
    bool containingBlobsComputed;
    bool enclosedBlobsComputed;
    
    // this is used by the blobManager
    // we create a 2 way link
    // to make certain things easier
    BlobInfo * blobInfo;
    
    // a containing blob is within the bounds of this blob
    vector<Blob*> containingBlobs;
    // a enclosed blob will be encapsulated by this shape
    vector<Blob*> enclosedBlobs;
    // the depth for the enclosed blobs hierarchy
    int depth;
    
    // a blob has a enclosingParent if it's enclosed by another blob
    // so to have this set computeEnclosedBlobsStep1 has to
    // be called
    void* enclosingParent;

    
    int minXCornerPixelIndex, minYCornerPixelIndex, maxXCornerPixelIndex, maxYCornerPixelIndex;
    
    bool mIsOuterContour;
    

    BlobBase * normalized;

    
    Blob(int maxCornerIndexes, int maxEdgeIndexes);
   
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    
    bool edgeHit(float x, float y, float edgeHitEpsilon) ;
    
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    void init(int maxCornerIndexes, int maxEdgeIndexes) ;
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    
    void reset() ;
    
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    void setImageSize(int width, int height) ;
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    void setImageWidth(int width) ;
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    void setImageHeight(int height);
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    
    
    // todo, still add this?
    //    int nOfEdgeIndexes() {
    //        return nOfEdgeIndexes;
    //    }
    
    
    
    
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    bool isOuterContour();
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    bool isInnerContour() ;
    
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    
    
    void addToCornerIndexes(int index);
    
    
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    
    void addToEdgeIndexes(int index) ;
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    
    
    void cornerIndexesToVector() ;
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    void setMinAndMax() ;
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    
    void edgeIndexesToVector();
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    vector<Blob*> getContainingBlobs() ;
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    vector<Blob*> getEnclosedBlobs() ;
    
    
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    
    /*
     It should already be sure that this blob really contains the blob to add.
     This method takes care of the hierarchy
     */
    void addContainingBlob(Blob* blobToAdd, int debugDepth) ;
    
    
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    
    void checkForContainingBlobsComputed(string methodName) ;
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    
    void checkForEnclosedBlobsComputed(string methodName) ;
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    // we have this cause it requires
    // EnclosedBlobsComputed
    // which can only be done with the BlobFinder
    void computeDepth(int depth) ;
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    int getDepth();
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    bool hasParent() ;
    
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    bool hasChildren() ;
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    
    void draw() ;
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    
    
    void draw(float x, float y, float w, float h) ;
    
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    
    
    void drawBounding () ;
    
    
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    
    void drawBounding ( float x, float y, float w, float h) ;
    // . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    
    
};



#endif
