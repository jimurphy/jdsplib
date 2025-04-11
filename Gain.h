//
// Gain.h
// Gain Setter
//
// 

#ifndef Gain_h
#define Gain_h

#include "DSPMath.h"

class Gain {
public:
    Gain(){
    }
    
    ~Gain(){};

    inline void lfoInput(float lfoVal, float center, float modDepth){
        gainVal = center + (lfoVal * modDepth); //?? modDepth * 2 (since -1,1?)
        gainVal = min(gainVal, 1.0f); //gainVal < 1? gainval : 1
        gainVal = max(gainVal, 0.0f); //gainVal > 0? gainVal : 0
    }
    
    inline void setGain(float gain){
        gainVal = gain;
    }

    inline void dsp(float& output){
        output = output * gainVal;
    }
    
private:
    float       gainVal;
};

#endif /* Gain_h */