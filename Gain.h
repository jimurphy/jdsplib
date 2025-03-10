//
// Gain.h
// Gain Setter
//
// 

#ifndef Gain_h
#define Gain_h

class Gain {
public:
    Gain(){
    }
    
    ~Gain(){};
    
    inline void setGain(float gain){
        gainVal = gain;
    }

    inline void dsp(float input, float& output){
        output = input * gainVal;
    }
    
private:
    float       gainVal;
};

#endif /* Gain_h */