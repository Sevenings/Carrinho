#ifndef MY_OTA_SERVICE_H
#define MY_OTA_SERVICE_H

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>

#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>

#include "wifi-config.h"


class MyOtaService {

    private:
        AsyncWebServer myOtaServer = AsyncWebServer(80);

        void connectWifi(const char* ssid, const char* password) {
            WiFi.mode(WIFI_STA);
            WiFi.begin(ssid, password);

            // Wait for connection
            while (WiFi.status() != WL_CONNECTED) {
                delay(500);
                Serial.print(".");
            }
            Serial.println(ssid);
            Serial.println(WiFi.localIP());
        }


    public:
        void setupOTA() {
            if (!Serial) {
                Serial.begin(115200);
            }

            connectWifi(wifi_ssid, wifi_password);

            myOtaServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
                request->send(200, "text/plain", "Página do Carrinho");
            });

            ElegantOTA.begin(&myOtaServer);    // Start ElegantOTA
                                               
            myOtaServer.begin();
        }

        void loopOTA() {
            ElegantOTA.loop();
        }
};

#endif

