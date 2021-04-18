#include <Gist.h>

class Magic {

    const static 
    int samplingFrequency = 22050*4;
    const static int frameSize = 512;

    Gist<float> gist = Gist<float>(frameSize, samplingFrequency);

    float audioFrame[frameSize];
    int samplingPeriod;
    int analogPin;
    unsigned long readStartAt;

    void printVector(
        double *vData,      

        uint16_t bufferSize,
        uint8_t scaleType
    );
    void analyze();
public:
    Magic(int _analogPin) {
        analogPin = _analogPin;
        samplingPeriod = 1000000 * (1.0 / samplingFrequency);
        readStartAt = 0;
    }

    void loop();
    float pitch;
    float power;
};
