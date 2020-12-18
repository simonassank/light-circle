#include <magic.hpp>

#define SCL_INDEX 0x00
#define SCL_TIME 0x01
#define SCL_FREQUENCY 0x02
#define SCL_PLOT 0x03

void Magic::readAudioSamples() {
    unsigned long readStartAt;
    
    unsigned int samplingPeriod = round(1000000*(1.0/samplingFrequency));

    // Serial.println("wait for micros: ");
    // Serial.println(samplingPeriod);

    for (int i = 0; i < SAMPLE_COUNT; i++) {
        readStartAt = micros();
        vReal[i] = analogRead(analogPin);
        vImag[i] = 0.0;
        // Serial.print(vReal[i]);
        // Serial.print(" ");
        while (readStartAt + samplingPeriod > micros());
    }
    // Serial.print("\n");
}

void Magic::analyze() {
    FFT.Windowing(vReal, SAMPLE_COUNT, FFT_WIN_TYP_HAMMING, FFT_FORWARD);	/* Weigh data */
    FFT.Compute(vReal, vImag, SAMPLE_COUNT, FFT_FORWARD); /* Compute FFT */
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLE_COUNT); /* Compute magnitudes */
    double v;
    FFT.MajorPeak(vReal, SAMPLE_COUNT, samplingFrequency, &peakFrequency, &v);
    // Serial.println("Data:");
    // printVector(vReal, SAMPLE_COUNT, SCL_TIME);

    // Serial.println("Weighed data:");
    // printVector(vReal, SAMPLE_COUNT, SCL_TIME);

    // Serial.println("Computed Real values:");
    // printVector(vReal, SAMPLE_COUNT, SCL_INDEX);

    // Serial.println("Computed Imaginary values:");
    // printVector(vImag, SAMPLE_COUNT, SCL_INDEX);

    // Serial.println("Computed magnitudes:");
    // printVector(vReal, (SAMPLE_COUNT >> 1), SCL_FREQUENCY);
}

void Magic::printVector(double *vData, uint16_t bufferSize, uint8_t scaleType)
{
  for (uint16_t i = 0; i < bufferSize; i++)
  {
    double abscissa;
    /* Print abscissa value */
    switch (scaleType)
    {
      case SCL_INDEX:
        abscissa = (i * 1.0);
	break;
      case SCL_TIME:
        abscissa = ((i * 1.0) / samplingFrequency);
	break;
      case SCL_FREQUENCY:
        abscissa = ((i * 1.0 * samplingFrequency) / SAMPLE_COUNT);
	break;
    }
    Serial.print(abscissa, 6);
    if(scaleType==SCL_FREQUENCY)
      Serial.print("Hz");
    Serial.print(" ");
    Serial.println(vData[i], 4);
  }
  Serial.println();
}
