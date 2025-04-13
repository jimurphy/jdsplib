# jdsplib
A small, header-only C++ library full of audio DSP functions I find useful.

- **ADSR.h**: Envelope generator with time-stretching. Linear attack, nonlinear D & R.
- **DSPMath.h**: Some functions useful in Audio DSP. Very non-exhaustive.
- **Gain.h**: A simple gain setter class.
- **LFO.h**: A multimode low frequency oscillator with tappable waveforms.
- **Noise.h**: White noise generation in range -1,1. Two algorithms included.
- **OSCmm.h**: Multimode audio oscillator with polyblep interpolation.
- **SinOsc.h** A sine wave oscillator w/ phase, freq, amp settings.
- **SinOscNEON.h** Four sine wave oscillators processed (in part) with ARM SIMD.
- **ZDSVF.h** A zero-delay/trapezoidal integrating state variable filter.
