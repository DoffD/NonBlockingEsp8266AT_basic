#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "Arduino.h"

#define ESP_PORT Serial1 // For espAt.h.
#define ESP_BAUD 115200 // For espAt.h.
// #define ESP_PORT Serial // For espAt.h.

#define DBG_ALL
#ifdef DBG_ALL
#define DBG_PORT Serial
#define DBG_BAUD 9600
#endif

const uint8_t PIN_OUT_LED_HB = 13;

#endif