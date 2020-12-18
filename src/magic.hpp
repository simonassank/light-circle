#include <Arduino.h>
#include <arduinoFFT.h>

const static int SAMPLE_COUNT = 64*4;

class Magic {

    int samplingFrequency;
    unsigned long readStartAt = 0;
    unsigned int samplingPeriod = 1000000 * (1.0 / samplingFrequency);
    arduinoFFT FFT = arduinoFFT();
    int analogPin;
    double vReal[SAMPLE_COUNT];
    double vImag[SAMPLE_COUNT];
    void printVector(
        double *vData,
        uint16_t bufferSize,
        uint8_t scaleType
    );
    void readAudioSamples();
    void analyze();
public:
    Magic(int _analogPin, int _samplingFrequency) {
        analogPin = _analogPin;
        samplingFrequency = _samplingFrequency;
    }

    void loop();
    double peakFrequency;
};
