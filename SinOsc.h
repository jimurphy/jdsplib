//
// SinOsc.h
// Sinusoidal Oscillator
// jim murphy 2025 
//

#include <math.h>
constexpr float PI =  3.14159265358979;
constexpr float TWO_PI = 6.28318530718;

#ifndef SinOsc_h
#define SinOsc_h

class SinOsc {
    public:
        SinOsc(){
        }
        
        ~SinOsc(){};

        inline void setSR(int _sr){
            sr = _sr;
        }
        
        inline void setFreq(float _freq){
            freq = _freq;
        }

        inline void setPhase(float _phase){
            phase = _phase;
        }

        inline void setAmp(float _amp){
            amp = _amp;
        }
    
        inline void dsp(float& output){
            output = sin(phase) * amp;
            phase += (freq/sr)*TWO_PI;
        }
        
    private:
        int       sr = 0;
        float     freq = 0.0f;
        float     phase = 0.0f;
        float     amp = 1.0f;
    };

#endif /* SinOsc_h */