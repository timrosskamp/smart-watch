#include "config.h"
#include <WiFi.h>
// #include "BluetoothA2DPSource.h"

// BluetoothA2DPSource a2dp_source;

TTGOClass *ttgo;
TFT_eSPI *tft;

char buf[128];

void searchMusic() {
    File root = SD.open("/");
    if( !root ){
        Serial.println("- failed to open directory");
        return;
    }
    if( !root.isDirectory() ){
        Serial.println("- not a directory");
        return;
    }
    File file = root.openNextFile();
    while( file ){
        if( !file.isDirectory() ){
            String name = String(file.name());
            if( !name.startsWith(".") && (name.endsWith(".mp3") || name.endsWith(".MP3")) ){
                Serial.println(name);
            }
        }
        file = root.openNextFile();
    }
}

// #define c3_frequency  130.81

// // The supported audio codec in ESP32 A2DP is SBC. SBC audio stream is encoded
// // from PCM data normally formatted as 44.1kHz sampling rate, two-channel 16-bit sample data
// int32_t get_data_channels(Frame *frame, int32_t channel_len) {
//     static double m_time = 0.0;
//     double m_amplitude = 10000.0;  // -32,768 to 32,767
//     double m_deltaTime = 1.0 / 44100.0;
//     double m_phase = 0.0;
//     double double_Pi = PI * 2.0;
//     // fill the channel data
//     for (int sample = 0; sample < channel_len; ++sample) {
//         double angle = double_Pi * c3_frequency * m_time + m_phase;
//         frame[sample].channel1 = m_amplitude * sin(angle);
//         frame[sample].channel2 = frame[sample].channel1;
//         m_time += m_deltaTime;
//     }

//     return channel_len;
// }

void setup() {
    WiFi.mode(WIFI_OFF);
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

    while (1) {
        if( ttgo->sdcard_begin() ){
            Serial.println("sd begin pass");
            break;
        }
        Serial.println("sd begin fail, wait 1 sec");
        delay(1000);
    }

    searchMusic();

    // a2dp_source.start("Bose 700", get_data_channels);
    // a2dp_source.set_volume(30);

    // esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_DEFAULT, ESP_PWR_LVL_P9);
    // esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_ADV, ESP_PWR_LVL_P9);
    // esp_ble_tx_power_set(ESP_BLE_PWR_TYPE_SCAN ,ESP_PWR_LVL_P9); 
}

void loop() {
    int16_t x, y;

    if( ttgo->getTouch(x, y) ){
        sprintf(buf, "x:%03d  y:%03d", x, y);
        tft->drawString(buf, 80, 118);
        Serial.printf("x:%03d  y:%03d\n", x, y);
    }
    delay(5);
}