//
//  ContourWalker.h
//  emptyExample
//
//  Created by Martijn Mellema on 02-09-14.
//
//

#ifndef __emptyExample__ContourWalker__
#define __emptyExample__ContourWalker__

#include <iostream>
#include "ofMain.h"
#include "ThresholdChecker.h"
#include "Blob.h"

#define LEFT -1
#define RIGHT 1
/**
 
 * Created by doekewartena on 4/30/14.
 */
class ContourWalker {
public:
    int moveDirection, checkDirection;
    
    

    // will be set in scan according to
    // the getWidth of the image
    int UP, DOWN;
    
    bool downIsFree, rightIsFree, upIsFree, leftIsFree;
    
    ThresholdChecker* thresholdChecker;
    
    bool addAllEdgesToContour;
    
    
   ContourWalker() {
    }

    
    ContourWalker setAddAllEdgesToContour(bool addAllEdgesToContour) {
        addAllEdgesToContour = addAllEdgesToContour;
        return *this;
    }

    
    bool isAddAllEdgesToContour() {
        return addAllEdgesToContour;
    }
    

    
    ContourWalker setThresholdTracker(ThresholdChecker thresholdChecker) {
        thresholdChecker = thresholdChecker;
        return *this;
    }

    
    
    ThresholdChecker* getThresholdChecker() {
        return thresholdChecker;
    }
    
    
    
    bool scan(int* pixels, int imageWidth, int imageHeight, int startX, int startY, Blob* blob, float threshold, bool normalizeCornerVectors) {
        
        int start = startY*imageWidth+startX;
        
        return scan(pixels, imageWidth, imageHeight, start, blob, threshold, normalizeCornerVectors);
    }
    
    
    /**
     *
     * @param pixels
     * @param imageWidth
     * @param start
     * @param blob
     * @param threshold
     * @return
     */
    bool scan(int* pixels, int imageWidth, int imageHeight, int start, Blob* blob, float threshold, bool normalizeCornerVectors) {
        
        blob->reset();
        
        blob->scanningStartIndex = start;
        blob->setImageSize(imageWidth, imageHeight);
        
        if (thresholdChecker == NULL) {
            // make one channel checker the default since it's the fastest
            thresholdChecker = new ThresholdCheckerOneChannel();
        }
        
         float t = threshold;
        float valueDown, valueUp, valueLeft, valueRight;
        
        UP = -imageWidth;
        DOWN = imageWidth;
        
        
        int current = start;
        
        valueDown = thresholdChecker->checkColor(pixels[current+DOWN]);
        valueRight = thresholdChecker->checkColor(pixels[current+RIGHT]);
        valueUp = thresholdChecker->checkColor(pixels[current+UP]);
        valueLeft = thresholdChecker->checkColor(pixels[current+LEFT]);
        
        
        // or we don't add it!
        downIsFree = valueDown >= t;
        rightIsFree = valueRight >= t;
        upIsFree =  valueUp >= t;
        leftIsFree = valueLeft >= t;
        
        // todo:
        // if we would check all surrounding pixels
        // from the start point then we could
        // figure out if the start is like a single line
        // if that is true then we have to scan in the other direction as well
        // maybe set a bool that the first cornerPixel is not a cornerPixel
        float valueDownLeft = thresholdChecker->checkColor(pixels[current+DOWN+LEFT]);
        float valueDownRight = thresholdChecker->checkColor(pixels[current+DOWN+RIGHT]);
        float valueUpLeft = thresholdChecker->checkColor(pixels[current+UP+LEFT]);
        float valueUpRight = thresholdChecker->checkColor(pixels[current+UP+RIGHT]);
        // todo see comment above
        
        // todo: onLine check, this should work
        // onLine = upIsFree && downIsFree ? true : leftIsFree && rightIsFree ? true : false;
        
        
        if(!setStartDirection()) return false;
        
        
        
        int c = 0;
        if (!leftIsFree) c++;
        if (!rightIsFree) c++;
        if (!upIsFree) c++;
        if (!downIsFree) c++;
        
        if (c >= 2) {  // it's a corner // todo, this is not correct?, could also be a single line
            blob->addToCornerIndexes(current);
        }
        
        float valueMoveDirection, valueCurrentDirection;
        
        while(true) {
            
            valueMoveDirection =  thresholdChecker->checkColor(pixels[current + moveDirection]);
            
            if (valueMoveDirection >= t) {
                
                if (addAllEdgesToContour)
                    blob->addToEdgeIndexes(current);
                
                current += moveDirection;
                
                if (current == start) {
                    break;
                }
                
                valueCurrentDirection =  thresholdChecker->checkColor(pixels[current + checkDirection]);
                
                if (valueCurrentDirection >= t) {
                    
                    blob->addToCornerIndexes(current);
                    
                    current += checkDirection;
                    
                    if (current == start) {
                        break;
                    }
                    
                    setDirection(checkDirection);
                }
                
                
            }
            else {
                // we hit a wall
                // so go right since we want to go clock wise
                blob->addToCornerIndexes(current);
                turnRight();
                
            }
            
        }
        
        // todo
        // do we want this here? maybe the user only needs
        // the pixels, this way we waste a lot of speed and
        // memory on this operation
        if (normalizeCornerVectors) {
            blob->normalized->cornerIndexesToVector();
        }
        else {
            blob->cornerIndexesToVector();
        }
        
        // check if it's an outerContour or not
        // we do this by checking pixels outside the contour
        // from the most left corner
        
        valueDown = thresholdChecker->checkColor(pixels[blob->minXCornerPixelIndex+DOWN]);
        valueUp = thresholdChecker->checkColor(pixels[blob->minXCornerPixelIndex+UP]);
        valueLeft = thresholdChecker->checkColor(pixels[blob->minXCornerPixelIndex+LEFT]);
        // we don't check for right!
        
        downIsFree = valueDown < threshold;
        upIsFree =  valueUp < threshold;
        leftIsFree = valueLeft < threshold;
        
        blob->mIsOuterContour = upIsFree || leftIsFree || downIsFree;
        
        return true;
    }
    
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    
    /*
     Make sure downIsFree, rightIsFree, upIsFree and leftIsFree is set
     */
    bool setStartDirection() {
        if (downIsFree && !rightIsFree) { // DOWN free
            moveDirection = DOWN;
            checkDirection = RIGHT;
        }
        else if (rightIsFree && !upIsFree) { // RIGHT free
            moveDirection = RIGHT;
            checkDirection = UP;
        }
        else if (upIsFree && !leftIsFree ) { // UP free
            moveDirection = UP;
            checkDirection = LEFT;
        }
        
        else if (leftIsFree && !downIsFree) { // LEFT free
            moveDirection = LEFT;
            checkDirection = DOWN;
        }
        else {
            // we have hit a isolated pixel
            /*
             PApplet.println("pixel index: "+current);
             
             String l =  leftIsFree ? " " : "X";
             String r =  rightIsFree ? " " : "X";
             String u =  upIsFree ? " " : "X";
             String d =  downIsFree ? " " : "X";
             
             PApplet.println("[ ][" + u + "][ ]");
             PApplet.println("["+l+"][C]["+r+"]");
             PApplet.println("[ ]["+d+"][ ]");
             */
            
            return false;
        }
        return true;
        
    }
    
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    void setDirection(int dir) {
        if (dir == RIGHT) {
            moveDirection = RIGHT;
            checkDirection = UP;
        }
        else if (dir == DOWN) {
            moveDirection = DOWN;
            checkDirection = RIGHT;
        }
        else if (dir == LEFT) {
            moveDirection = LEFT;
            checkDirection = DOWN;
        }
        else if (dir == UP) {
            moveDirection = UP;
            checkDirection = LEFT;
        }
    }
    
    
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    
    /*
     We want to check in a clockwise motion to get the contour.
     We could make a call to setDirection but this is faster.
     */
    void turnRight() {
        
        if (moveDirection == UP) {
            moveDirection = RIGHT;
            checkDirection = UP;
        }
        else if (moveDirection == RIGHT) {
            moveDirection = DOWN;
            checkDirection = RIGHT;
        }
        else if (moveDirection == DOWN) {
            moveDirection = LEFT;
            checkDirection = DOWN;
        }
        else if (moveDirection == LEFT) {
            moveDirection = UP;
            checkDirection = LEFT;
        }
        
        //PApplet.println("turnRight");
        //printDirection();
        
        
    }
    
    // . . . . . . . . . . . . . . . . . . . . . . .
    
    
    
    
};


#endif /* defined(__emptyExample__ContourWalker__) */
