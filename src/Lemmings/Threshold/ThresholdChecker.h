//
//  Header.h
//  emptyExample
//
//  Created by Martijn Mellema on 02-09-14.
//
//

#ifndef emptyExample_Header_h
#define emptyExample_Header_h
#include "ofMain.h"
/**
 * Created by doekewartena on 6/9/14.
 */
class ThresholdChecker {
public:

    float checkColor(int color);
};

/**
 * Created by doekewartena on 6/9/14.
 */
class ThresholdCheckerMultipleChannels :  ThresholdChecker {
public:
    bool mCheckRed = false;
    bool mCheckGreen = false;
    bool mCheckBlue = true;
    bool mCheckAlpha = false;
    
    float sum;
    float div;
    
    float checkColor(int color) {
        sum = 0;
        div = 0;
        
        if (mCheckRed) {
            div++;
            sum += (color >> 16) & 0xFF;
        }
        if (mCheckGreen) {
            div++;
            sum += (color >> 8) & 0xFF;
        }
        if (mCheckBlue) {
            div++;
            sum += color & 0xFF;
        }
        if (mCheckAlpha) {
            div++;
            sum += (color >> 24) & 0xFF;
        }
        
        return (sum/div);
        
    };
    
    ThresholdCheckerMultipleChannels checkRed(bool b) {
        mCheckRed = b;
        return *this;
    }
    
    ThresholdCheckerMultipleChannels checkGreen(bool b) {
        mCheckGreen = b;
        return *this;
    }
    
    ThresholdCheckerMultipleChannels checkBlue(bool b) {
        mCheckBlue = b;
        return *this;
    }
    
    ThresholdCheckerMultipleChannels checkAlpha(bool b) {
        mCheckAlpha = b;
        return *this;
    }
    
};


class ThresholdCheckerMultipleChannelsInverse : public ThresholdCheckerMultipleChannels {
public:
    
    float checkColor(int color) {
        return 255 - checkColor(color);
    }
    
};


class ThresholdCheckerOneChannel : public ThresholdChecker {
public:
    int rightShiftOffset = 0;
    
    float checkColor(int color) {
        return (color >> rightShiftOffset) & 0xFF;
    }
    
    ThresholdCheckerOneChannel  checkRed() {
        rightShiftOffset = 16;
        return *this;
    }
    
    ThresholdCheckerOneChannel  checkGreen() {
        rightShiftOffset = 8;
        return *this;
    }
    
    ThresholdCheckerOneChannel  checkBlue() {
        rightShiftOffset = 0;
        return *this;
    }
    
    ThresholdCheckerOneChannel  checkAlpha() {
        rightShiftOffset = 24;
        return *this;
    }
};

class ThresholdCheckerOneChannelInverse : public ThresholdCheckerOneChannel {
public:
    float checkColor(int color) {
        return 255 - ThresholdChecker::checkColor(color);
    }
    
};




#endif
