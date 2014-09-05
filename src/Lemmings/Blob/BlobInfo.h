//
//  BlobInfo.h
//  emptyExample
//
//  Created by Martijn Mellema on 02-09-14.
//
//

#ifndef emptyExample_BlobInfo_h
#define emptyExample_BlobInfo_h
#include "ofMain.h"

class Blob;

class BlobInfo {
    
    enum Status {
        FREE,
        NEW,
        UPDATE,
        LOST,
        BACK
    };
    
    
    
    // todo, do we need all public?
    
    int id;
    
    Status status;
    
    // every time we use the method
    // set we will set this id
    // to the current id value of
    // the blobManager
    // this way we can check if something is lost
    int updateCountNumber;
    
    // this link is valid
    // till reset() is called with the
    // blobScanner (it can also be auto called)
    void * blob;
    
    // since the link to the blob is temp we
    // need to store the coordinates
    float minX, minY, maxX, maxY;
    float centerX, centerY; // do we need it here?
    
    
    // do we need this? a blob with a longer lifetime could
    // have a longer time for delete on lost?
    //int lifeTime;
    
    long lostSince;
    
    
    BlobInfo(int id);
    // . . . . . . . . . . . . . . . . . . . . . .
    
    void set(Blob* b, int updateCountNumber);
    
    // . . . . . . . . . . . . . . . . . . . . . .
    
    float width();
    // . . . . . . . . . . . . . . . . . . . . . .
    
    float height();
    // . . . . . . . . . . . . . . . . . . . . . .
    
    string getStatus() ;
    // . . . . . . . . . . . . . . . . . . . . . .
    
    void drawBounding ();
    // . . . . . . . . . . . . . . . . . . . . . .
    
    
    /*
     Only works when normalize is used, see BlobFinder.
     */
    void drawBounding (float x, float y, float w, float h);
    // . . . . . . . . . . . . . . . . . . . . . .
    
    
};



#endif
