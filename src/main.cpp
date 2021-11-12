#include <Arduino.h>
#include "config.h"

TTGOClass *ttgo;

TFT_eSPI *tft;

char buf[128];

void setup() {
    Serial.begin(115200);

    ttgo = TTGOClass::getWatch();

    ttgo->begin();
    ttgo->setBrightness(120);
    ttgo->openBL();

    tft = ttgo->tft;

    tft->fillScreen(TFT_BLACK);
    tft->setTextFont(2);
    tft->setTextColor(TFT_WHITE, TFT_BLACK);
    tft->drawString("T-Watch Touch Test", 62, 90);
}

void loop() {
    int16_t x, y;

    if( ttgo->getTouch(x, y) ){
        sprintf(buf, "x:%03d  y:%03d", x, y);
        tft->drawString(buf, 80, 118);
    }
    delay(5);
}