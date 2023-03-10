/*
  Voltage to Frequency: linear fit parameters
  Perform a Voltage to Frequency experiment (Precharge/code/v-f-experiment/)
  Record frequency output for several samples
  calculate linear fits
  define the necessary constants in this file, such that
  freq = f(Vin) = V2F_slope * Vin + V2F_ofs
*/

#include "measurements.h"
#include "gpio.h"

// Accumulator V-F converter - Schematic REF : U8
const double V2F_slope_accu = 556.19;   // Gradient constant
const double V2F_ofs_accu = -6.2818;     // offset / y-intercept consant

// Tractive System V-F converter - Schematic REF: U7
const double V2F_slope_ts = 557.22;     // Gradient constant
const double V2F_ofs_ts = -8.7202;      // offset / y-intercept consant

// Voltage dividers upstream of V-F converters:
// R31+R32+R36+R37 = 2.55M, R39 = 39k, Rtotal = 2.55M+39k
// gain = R39/(Rtotal)
// Our values:
// 66500/(2550000+66500)
const double gainVoltageDivider = 0.02541563156;

const float MIN_VOLTAGE_THRESHOLD = 5.0;  // Clip voltages below this level
const int MAX_FREQ_ATTEMPTS = 10;         // Attempts at measuring frequency before accepting an out-of-bounds result

// Calculate the HIGH voltage at Accumulator or TS
// convert frequency to voltage: inverse of the linear characteristic
// y = mx+b becomes x = (y-b)/m
// scale voltage by voltage-divider
double getTsVoltage() {
  double f = getFrequency(FREQ_TS_PIN);
  int attempts = 0;
  while (!isInBounds(f) && attempts++ < MAX_FREQ_ATTEMPTS){
    f = getFrequency(FREQ_TS_PIN);
  }
  // use last f when out-of-bounds but maxAttempts made
  double v = (f - V2F_ofs_ts) / V2F_slope_ts / gainVoltageDivider;
  return (v > MIN_VOLTAGE_THRESHOLD) ? v : 0; // Filter out very small voltage
}
// TODO: Refactor
double getAccuVoltage() {
  double f = getFrequency(FREQ_ACCU_PIN);
  int attempts = 0;
  while (!isInBounds(f) && attempts++ < MAX_FREQ_ATTEMPTS){
    f = getFrequency(FREQ_ACCU_PIN);
  }
  // use last f when out-of-bounds but maxAttempts made
  double v = (f - V2F_ofs_accu) / V2F_slope_accu / gainVoltageDivider;
  return (v > MIN_VOLTAGE_THRESHOLD) ? v : 0;

}

// check if a sensible frequency was returned
// this is an attempt to eliminate the outliers
bool isInBounds(double f) {
  const float MIN_FREQ = 10.0;  // Dependent on the TIMEOUT value used in getFrequency
  const float MAX_FREQ = 800.0; // Clips the occasional spurious measurement
  return (f >= MIN_FREQ && f <= MAX_FREQ);
}


// Calculate frequency from signal period. Signal not 50% duty cycle:
// measure separate high-pulse and a low-pulse, sum to get period.
double getFrequency(int pin) {
  const unsigned int TIMEOUT = 10000;
  unsigned int tHigh = pulseIn(pin, HIGH, TIMEOUT);  // microseconds
  unsigned int tLow = pulseIn(pin,LOW, TIMEOUT);
  if (tHigh == 0 || tLow == 0){
    return 0; // timed out
  }
  return ( 1000000.0 / (double)(tHigh + tLow) );    // f = 1/T
}


// DEPRECATED: here we could just use the map function if we have collected
// min/max voltage and min/max frequency
double getVoltage(int pin) {
  double freq = getFrequency(pin);
  return (double)map(freq,0,10000,0,610); // TODO: use sensible values. SYSID
}
