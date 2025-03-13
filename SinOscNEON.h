//
// SinOscNEON.h
// Sinusoidal Oscillator using ARM NEON SIMD 
// jim murphy 2025 
//

#include <math.h>
#include <arm_neon.h>

//constexpr float PI =  3.14159265358979;
//constexpr float TWO_PI = 6.28318530718;

#ifndef SinOscNEON_h
#define SinOscNEON_h

class SinOscNEON {
    public:
        SinOscNEON(){
        }
        
        ~SinOscNEON(){};

        inline void setSR(int _sr){
            sr = _sr;
        }
        
        inline void setFreq(int index, float _freq){
            freqs[index] = _freq;
        }

        inline void init(){
            //calculate 4x phase increments
            for(int i = 0; i < 4; ++i){
                phaseStep[i] = (2.0f * PI * freqs[i])/sr;
            }

            two_pi = vdupq_n_f32(2.0f * PI);
            phaseVector = vld1q_f32(phase); //load up phases
            phaseStepVector = vld1q_f32(phaseStep); //load up phase steps
        }

        inline void setAmp(float _amp){
            amp = _amp;
        }
    
        inline void dsp(float (&output)[4]){
            float32x4_t sinVector = vdupq_n_f32(0.0f);
            float phaseArray[4];

            vst1q_f32(phaseArray, phaseVector);

            for(int i = 0; i < 4; i++){
              phaseArray[i] = sinf(phaseArray[i]);  
            }
            
            sinVector = vld1q_f32(phaseArray);
            vst1q_f32(output, sinVector);

            phaseVector = vaddq_f32(phaseVector, phaseStepVector);

            //use modulo to keep phase 0-2pi range
            //this is a vectorized phase = phase - (2.0*PI) * floor(phase[i]/(2.0*PI))
            //Keeps all phase values within one sine cycle
            phaseVector = vsubq_f32(phaseVector,vmulq_f32(two_pi, vcvtq_f32_s32(vcvtq_s32_f32(vdivq_f32(phaseVector, two_pi)))));
        }
        
    private:
        float32x4_t phaseVector;
        float32x4_t phaseStepVector;
        float32x4_t two_pi;

        int       sr = 0;

        float     freqs[4] = {0};

        float     phase[4] = {0}; //phase accumulators
        float     phaseStep[4];

        float     amp = 1.0f;
    };

#endif /* SinOscNEON_h */