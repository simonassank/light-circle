#include <Arduino.h>
#include <arduinoFFT.h>

const static int SAMPLE_COUNT = 64*4;

class Magic {
    arduinoFFT FFT = arduinoFFT();
    int analogPin;
    double vReal[SAMPLE_COUNT];
    double vImag[SAMPLE_COUNT];
    int samplingFrequency;
    void printVector(double *vData, uint16_t bufferSize, uint8_t scaleType);
public:

    Magic(
        int _analogPin,
        int _samplingFrequency
    ) {
        analogPin = _analogPin;
        samplingFrequency = _samplingFrequency;
    }

    double peakFrequency;

    void readAudioSamples();

    void analyze();
};
