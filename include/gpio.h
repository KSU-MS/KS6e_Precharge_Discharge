// Pin definitions for the project

#ifndef PINDEFS_H
#define PINDEFS_H
#include "Arduino.h"
#include <stdint.h>

class StatusLight
{
  public:
    StatusLight(int pin);
    void update();
    void update(long on, long off);
    void on();
    void off();
  private:
    int ledPin;
    long OnTime;
    long OffTime;
    int ledState;
    unsigned long previousMillis;
};

// Configuration solder-jumpers
const int CONFIG_PIN[] = {4,5,6};
// Status LEDs
const int STATUS_LED[] = {0,1,2,3};

// Relays
const int SHUTDOWN_CTRL_PIN = 13; // 20 in Alt.
const int PRECHARGE_CTRL_PIN = 19; // 26 in Alt.

// Frequency measurements (from Voltage-to-Frequency converters)
const int FREQ_ACCU_PIN = 14; // 22 in Alt.
const int FREQ_TS_PIN = 15; // 21 in Alt.

// Status inputs
const int PDOC_PIN = A7; // NOTUSED in Alt. Active-high when PDOC is OK
const int PWR_OK_PIN = 18; // 25 in Alt. Active-high when power-supply (shutdown circuit) is OK

// Function prototypes
void setupGPIO(void);
float getShutdownCircuitVoltage(void);


#endif
