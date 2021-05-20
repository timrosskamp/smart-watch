#include <Arduino.h>
#include "config.h"

TTGOClass *ttgo;

void setup() {
    Serial.begin(115200);

    ttgo = TTGOClass::getWatch();

    ttgo->begin();
    ttgo->openBL();

    ttgo->tft->fillScreen(TFT_RED);
}

void loop() {
    
}