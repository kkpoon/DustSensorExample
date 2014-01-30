#include "RunningMedian.h"

#define PM25_LED_PIN 8
#define PM25_OUT_PIN A7

RunningMedian ppmsamples = RunningMedian(50);
float pm_mgpm3 = 0;

void setup()
{
    pinMode(PM25_LED_PIN, OUTPUT);
}

void loop()
{
    digitalWrite(PM25_LED_PIN, LOW);
    delayMicroseconds(280);
    int ppm = analogRead(PM25_OUT_PIN);
    delayMicroseconds(40);
    digitalWrite(PM25_LED_PIN, HIGH);
    delayMicroseconds(9680);
    
    ppmsamples.add(ppm);

    float voltage = ppmsamples.getAverage(10) * 0.0049;
    pm_mgpm3 = map(voltage*1000, 0.1*1000, 3.5*1000, 0, 0.5*1000) / 1000.0 - 0.1;
    pm_mgpm3 = constrain(pm_mgpm3, 0.0, 0.5);
    Serial.println(pm_mgpm3);
}


