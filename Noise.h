// Noise.h
// White noise generator
// std lib PNRG using Mersenne Twister is default
// Also available is a fast XORShift-based approach
// jim murphy 2025 
// Thanks to https://github.com/Arifd/Noise-Algorithms
//
#ifndef Noise_h
#define Noise_h

#include <random>

class Noise{
    public:
    Noise(){
    }
        
    ~Noise(){};

    inline void setSR(int _sr){
        sr = _sr;
    }

    inline void noiseInit(){
        std::random_device rd;
        gen = std::mt19937(rd());
        dist = std::uniform_real_distribution<float>(-1.0f, 1.0f);
    }

	inline void setSeed(uint32_t _seed){
	    fastseed = (_seed == 0) ? 7 : _seed; //prevent a seed of 0
	}

    inline void setAmp(float _amp){
        amp = _amp;
    }

    inline void dsp(float& output){
        output = dist(gen); //Uses Mersenne Twister
    }
        
	//Thanks to https://github.com/WebDrake/xorshift/tree/master
	inline void fastRandom(float& output){
	    fastseed ^= fastseed << 13;
        fastseed ^= fastseed >> 17;
        fastseed ^= fastseed << 15;

	    output = amp*((fastseed >> 8) * (1.0f / 16777216.0f) * 2.0f - 1.0f); //scale to [-1,1]
	}
	
    private:
        int       sr = 0;
	    uint32_t  fastseed = 2463534242UL; //seed for fastRandom xorshift
        float     amp = 1.0f;

        std::mt19937 gen; //mersenne twister prng
	    std::uniform_real_distribution<float> dist;
    };

#endif /* Noise_h */