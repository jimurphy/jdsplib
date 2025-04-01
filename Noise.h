//
// Noise.h
// White noise generator
// std lib PNRG using Mersenne Twister is default
// Also available is a fast XORShift-based approach
// jim murphy 2025 
// Thanks to https://github.com/Arifd/Noise-Algorithms
//

#include <random>

#ifndef Noise_h
#define Noise_h

class Noise{
    public:
        Noise(){
        }
        
        ~Noise(){};

        inline void setSR(int _sr){
            sr = _sr;
        }

	inline void setSeed(uint32_t _seed){
	    fastseed = (_seed == 0) ? 7 : _seed; //prevent a seed of 0
	    seedGen(); //generate a new seed for the MT
	}

        inline void setAmp(float _amp){
            amp = _amp;
        }
    
        inline void dsp(float& output){
            output = amp * (dist(gen)); //Uses Mersenne Twister
        }
        
	//Thanks to https://github.com/WebDrake/xorshift/tree/master
	inline void fastRandom(float& output){
	    seed ^= seed << 13;
            seed ^= seed >> 17;
            seed ^= seed << 15;

	    output = amp*((seed >> 8) * (1.0f / 16777216.0f) * 2.0f - 1.0f); //scale to [-1,1]
	}
	
    private:
        int       sr = 0;
	uint32_t  fastseed = 2463534242UL; //seed for fastRandom xorshift
        float     amp = 1.0f;

	std::random_device seedGen; //for mersenne twister
        std::mt19937 gen(seedGen()); //mersenne twister prng
	std::uniform_real_distribution<float> dist(-1.0f, 1.0f);
    };

#endif /* Noise_h */