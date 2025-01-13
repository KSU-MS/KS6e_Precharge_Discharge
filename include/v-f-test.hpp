/*
  V-F Experiment
  This program simply logs the frequencies measured from the
  V-F converters.
  Use this program to measure their V-F responses


  Michael Ruppe Apr 2020
*/

// Modified by Chance for Kennesaw Motorsports

#include "gpio.h"
#include "measurements.h"
#include <Arduino.h>

unsigned long startTime;

void init_test() {
  Serial.begin(9600);

  Serial.print("F_CPU_ACTUAL=");
  Serial.println(F_CPU_ACTUAL);

  // Startup animation
  digitalWrite(13, HIGH);
  delay(150);
  digitalWrite(13, LOW);
  delay(150);
  digitalWrite(13, HIGH);
  delay(50);
  digitalWrite(13, LOW);
  delay(50);
  digitalWrite(13, HIGH);
}

void run_test() {

  int num_samples = 20; // Take the average of many samples

  // ACCUMULATOR VOLTAGE-FREQUENCY
  double sum = 0;
  for (int i = 0; i < num_samples; i++) {
    sum += getFrequency(FREQ_ACCU_PIN);
  }
  Serial.print(sum / (double)num_samples);
  Serial.print(",");

  // TRACTIVE SYSTEM VOLTAGE-FREQUENCY
  sum = 0;
  for (int i = 0; i < num_samples; i++) {
    sum += getFrequency(FREQ_TS_PIN);
  }
  Serial.print(sum / (double)num_samples);
  Serial.println();

  delay(5000);
}
