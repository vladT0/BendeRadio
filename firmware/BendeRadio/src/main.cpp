#include <Arduino.h>
#include <WiFi.h>

#include "config.h"
#include "core0.h"
#include "core1.h"

//specify here number of your WIFI networks
#define NET_NUM 2

//specify here SSID for each WIFI network
const char* ap_ssid[NET_NUM] = {
    "xxx",
    "xxx",
};

//specify here passphrase for each WIFI network
const char* ap_pass[NET_NUM] = {
    "xxx",
    "xxx",
};

TaskHandle_t Task0,Task1;
SemaphoreHandle_t  xMutex;

const uint32_t connectTimeoutMs = 10000;

uint8_t wifi_connect(uint32_t connectTimeout)
{
    int8_t scanResult;
    uint8_t status = WiFi.status();
    if(status == WL_CONNECTED) {
        for(uint32_t x = 0; x < NET_NUM; x++) {
            if(WiFi.SSID()==ap_ssid[x]) {
                return status;
            }
        }
        WiFi.disconnect(false,false);
        delay(10);
        status = WiFi.status();
    }

    scanResult = WiFi.scanNetworks();
    if(scanResult >= 0)
    {
        int32_t bestChannel = 0;
        int bestNetworkDb = INT_MIN;
        int bestNetNum = -1;
        for(int8_t i = 0; i < scanResult; ++i) {
            String ssid_scan;
            int32_t rssi_scan;
            uint8_t sec_scan;
            uint8_t* BSSID_scan;
            int32_t chan_scan;
            int bestNetworkDb = INT_MIN;
            WiFi.getNetworkInfo(i, ssid_scan, sec_scan, rssi_scan, BSSID_scan, chan_scan);
            bool known = false;
            for(uint32_t x = 0; x < NET_NUM; x++) {
                if(ssid_scan == ap_ssid[x]) { // SSID match
                    known = true;
                    if(rssi_scan >= bestNetworkDb) { // best network
                        bestNetworkDb = rssi_scan;
                        bestChannel = chan_scan;
                        bestNetNum = x;
                    }
                    break;
                }
            }
        }
        WiFi.scanDelete();
        if(bestNetNum != -1) {
            WiFi.begin(ap_ssid[bestNetNum], ap_pass[bestNetNum]);
            status = WiFi.status();

            auto startTime = millis();
            // wait for connection, fail, or timeout
            while(status != WL_CONNECTED && status != WL_NO_SSID_AVAIL && status != WL_CONNECT_FAILED && (millis() - startTime) <= connectTimeout) {
		        delay(10);
                status = WiFi.status();
            }

            switch(status) {
            case WL_CONNECTED:
                Serial.println("[WIFI] Connecting done.");
                Serial.print("[WIFI] SSID:");    Serial.println(WiFi.SSID());
                Serial.print("[WIFI] IP:");      Serial.println(WiFi.localIP());
                Serial.print("[WIFI] MAC:");     Serial.println(WiFi.BSSIDstr());
                Serial.print("[WIFI] Channel:"); Serial.println(WiFi.channel());
                break;
            case WL_NO_SSID_AVAIL:
                Serial.println("[WIFI] Connecting Failed AP not found.");
                break;
            case WL_CONNECT_FAILED:
                Serial.println("[WIFI] Connecting Failed.");
                break;
            default:
                Serial.println("[WIFI] Connecting Failed.");
                break;
            }
        } else {
            Serial.println("[WIFI] no matching wifi found!");
        }
    }
    else {
      if(scanResult == WIFI_SCAN_FAILED || scanResult == WIFI_SCAN_RUNNING ) 
        return WL_NO_SSID_AVAIL;
    }
    return status;
}

void setup() {
    Serial.begin(115200);
    delay(500);
    xMutex = xSemaphoreCreateMutex();
    if (xMutex != NULL) {
        xTaskCreatePinnedToCore(core0, "Task0", 10000, NULL, 1, &Task0, 1);
        while (wifi_connect(connectTimeoutMs) != WL_CONNECTED) {
            delay(250);
        }
        change_state();
        xTaskCreatePinnedToCore(core1, "Task1", 10000, NULL, 1, &Task1, 0);
    }
    else {
        Serial.println("Mutex creation failed! Check available heap memory.");
    }

}

void loop() {
    // Empty loop because tasks are running in the FreeRTOS scheduler
}