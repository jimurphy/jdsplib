# jdsplib
A small, header-only C++ library full of audio DSP functions I find useful.

- **DSPMath.h**: Some functions useful in Audio DSP. Very non-exhaustive.
- **Gain.h**: A simple gain setter class.
- **Noise.h**: White noise generation in range -1,1. Two algorithms included.
- **SinOsc.h** A sine wave oscillator w/ phase, freq, amp settings.
- **SinOscNEON.h** Four sine wave oscillators processed (in part) with ARM SIMD.
- **ZDSVF.h** A zero-delay/trapezoidal integrating state variable filter.
