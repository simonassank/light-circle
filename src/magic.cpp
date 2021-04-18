#include <Arduino.h>
#include <magic.hpp>

void Magic::loop() {
    for (int i = 0; i < frameSize; i++) {
        readStartAt = micros();
        int read = analogRead(analogPin);
        float value;
        // # fuck negative vibes
        value = abs(read) / 385.0;
        // # with negatives
        // if (read > 385) {
        //     value = (read - 385) / 385.0;
        // } else if (read == 0) {
        //     value = 0.0;
        // } else {
        //     value = -1.0 + (read / 385.0);
        // }
        
        value *= 4.0;
        audioFrame[i] = value;
        while (readStartAt + samplingPeriod > micros()) {
            // int left = readStartAt + samplingPeriod - micros();
            // Serial.print("wait for:");
            // Serial.print(left);
            // Serial.print("μs");
            // Serial.println();
        }
    }
    // Serial.println();

    // for (int i = 0; i < frameSize; i++) {
    //     Serial.print(audioFrame[i]);
    //     Serial.print(" ");
    // }
    // Serial.println();
    analyze();
}

void Magic::analyze() {
    gist.processAudioFrame(audioFrame, frameSize);
    pitch = gist.pitch();

    std::vector<float> mels = gist.getMelFrequencyCepstralCoefficients();
    
    Serial.print("Pitch: ");
    Serial.print(pitch);
    Serial.println();

    Serial.print("Power: ");
    Serial.print(power);
    Serial.println();
}


