#ifndef MY_OTA_SERVICE_H
#define MY_OTA_SERVICE_H

#include <WiFi.h>
#include <AsyncTCP.h>

#include <ESPAsyncWebServer.h>
#include <ElegantOTA.h>


AsyncWebServer myOtaServer = AsyncWebServer(80);

void setupOTA() {
    /*
    // Connect Wifi
    WiFi.mode(WIFI_STA);
    WiFi.begin("TCEGO-PUBLIC", "");

    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    */

    // Setup server
    myOtaServer.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(200, "text/plain", "Pagina do Carrinho");
    });

    ElegantOTA.begin(&myOtaServer);    // Start ElegantOTA
                                       
    myOtaServer.begin();
}

void loopOTA() {
    ElegantOTA.loop();
}

#endif

