
//LFO - Low frequency oscillator
//bipolar output, [-1.0 - 1.0]
//jim murphy 2025

#ifndef LFO_H
#define LFO_H

#pragma once
#include "DSPMath.h"

class LFO {
public:
    LFO(){
    }
    
    ~LFO(){};
    
    inline void init(float samplerate, int wf, float ph, float freq){
        sr = samplerate;
        setWaveform(wf);
        setPhase(ph);
        setFreq(freq, sr);
    }
    
    //Set LFO phase (used for retriggering) (range: 0-1)
    inline void setPhase(float phase){
        modulo1 = phase; //TODO: limit range (clip minmax?)
        
        sinModulo = phase - 0.5f; //0 -> 1 to -0.5 - 0.5
        z = phase+0.5f; //for triOsc
    }
    
    inline float getPhase(){
        return modulo1;
    }
    
    inline void setFreq(float freq, float fs){
        sr = fs;
        inc = freq/sr;
    }

    inline void setWaveform(int waveform){
        waveformSelect = waveform; //1 = saw, 2 = sqr, 3 = tri, 4 = sin
    }
    
    inline void setPulsewidth(float pulsewidth){
        if(pulsewidth >= 100.0){
            pulsewidth = 99.9;
        }
        else if(pulsewidth <= 0.0){
            pulsewidth = 0.1;
        }
        pw = pulsewidth;
    }
    
    //Set inc directly (used in GUI to set per-pixel inc, etc)
    inline void setInc(float i){
        inc = i;
    }
    
    //sawtooth with no AA
    inline float sawDSP(){
        modulo1 += inc;

        if(modulo1 >= 1.0){
            modulo1 -= 1.0;
        }
        
        float sawtooth = 2.0*modulo1-1.0; //bipolar
        return sawtooth;
    }
    
    inline float sqrDSP(){
        modulo1 += inc;
        
        modulo2 = modulo1;

        //calculate first (normal) aa sawtooth
        if(modulo1 >= 1.0){
            modulo1 -= 1.0;
        }
        
        float square = 0.0;
        
        if(modulo1 > pw/100.0){
            square = 1.0;
        }
        else{
            square = 0.0;
        }
        
        square = 2.0*square-1.0; //bipolar

        return square;
    }
    
    inline float triDSP(){
        z += (inc*2.0);
        if (z > 1.0)
            z -= 2.0;
            
        triWave = ((2*abs(z))-1);
        return triWave;
    }
    
    //return triwave value when a phase (ph) from -1 to 1 is given
    inline float tapTri(float ph){
        float t = z + ph;
        if (t > 1.0)
            t -= 2.0;
            
        float triWaveTap = ((2*abs(t))-1);
        return triWaveTap;
    }
    
    //Parabolic sinewave approx (Martijn 2019)
    inline float sineDSP(){
        sinModulo += inc;
        if (sinModulo > 0.5)
            sinModulo -= 1.0f;
        return(sinModulo * (8 - (16 * abs(sinModulo))));
    }
    
    //return sin value when a phase (ph) from 0 to 1 is given
    inline float tapSine(float ph){
        float t = sinModulo + ph;
        if (t > 0.5)
            t -= 1.0f;
        float sinWaveTap = t * (8 - (16 * abs(t)));
        return(sinWaveTap);
    }
    
    inline void dsp(float& output){
        switch(waveformSelect){
            case 1:
                output = sawDSP();
                break;
            case 2:
                output = sqrDSP();
                break;
            case 3:
                output = triDSP();
                break;
            case 4:
                output = sineDSP();
                break;
            default:
                output = 0.0;
        }
    }
    
    inline float tapLFO(){
        return lfoValue;
    }
    
private:
    float       inc = 0.0f;
    int         sr = 44100;
        
    int         waveformSelect = 2;
    
    //saw stuff
    float       modulo1 = 0.0f;
    float       sat = 1.0f; //saw shaper
    
    //sqr stuff
    float       modulo2 = 0.0f;
    float       pw = 0.0f;

    //Sine stuff
    float       sinModulo = 0.0f;

    float       triWave = 0.0;
    float       freq = 220.0;
    float       z = 0.0;
    
    float lfoValue = 0.0f; //value for getter
};

#endif /*LFO_H*/