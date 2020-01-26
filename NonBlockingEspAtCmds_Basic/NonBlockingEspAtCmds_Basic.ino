#include "definitions.h"
#include "espAt.h"

void setup() {
  // put your setup code here, to run once:
  #ifdef DBG_ALL
  DBG_PORT.begin(DBG_BAUD);
  DBG_PORT.println(F("Non-blocking ESP8266 AT Commands Basic Test!"));
  #endif
  
  ESP_PORT.begin(ESP_BAUD);

  pinMode(PIN_OUT_LED_HB, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  static uint8_t st{};
  switch (st)
  {
  case 0: // Send command.
    espAt_commander("AT\r\n", 2000, "OK");
    st = 1;
    break;
  case 1: // Wait for the result.
  {
    // NB: Buffer the return value of espAt_getResult() since the internal variable is cleared after being read.
    EspAtResult espAtResult = espAt_getResult();
    if(espAtResult == EspAtResult::searchOk){
      st = 2;
      #ifdef DBG_ALL
      DBG_PORT.println(F("Reply rcvd!"));
      #endif
    }
    else if(espAtResult == EspAtResult::timeout){
      st = 2;
      #ifdef DBG_ALL
      DBG_PORT.println(F("Timeout!"));
      #endif
    }
    else if(espAtResult == EspAtResult::overflow){
      st = 2;
      #ifdef DBG_ALL
      DBG_PORT.println(F("Overflow!"));
      #endif
    }
    else if(espAtResult == EspAtResult::invalidCmd){
      st = 2;
      #ifdef DBG_ALL
      DBG_PORT.println(F("invalid cmd!"));
      #endif
    }
    else if(espAtResult == EspAtResult::none){
      #ifdef DBG_ALL
      DBG_PORT.println(F("Processing..."));
      #endif
    }
  }
  case 2: // Done.
    // Do nothing.
    break;
    break;
  default:
    break;
  }


  // ESP8266 AT routines start ====================
  espAt_loop();
  // ESP8266 AT routines end   ====================

  // Blink LED routine start ====================
  static uint32_t hb_tRef{};
  if(millis() - hb_tRef > 500){
    digitalWrite(PIN_OUT_LED_HB, !digitalRead(PIN_OUT_LED_HB));
    hb_tRef = millis();
  }
  // Blink LED routine end   ====================
}
