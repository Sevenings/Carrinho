// Bibliotecas Controle via Wifi
#include <WiFi.h>
#include <NetworkClient.h>
#include <WiFiAP.h>

#include "Controlador.h"
#include "Carrinho.h"

#include "MyOtaService.h"




// Carrinho
// ------------

// Não funcionam
// 34, 35, 36, 39

#define pinPulL 23
#define pinDirL 27
//#define pinEnaL
#define pinPulR 26
#define pinDirR 22
//#define pinEnaR

#define pinPulE 32
#define pinDirE 12
//#define pinEnaE 15

// Rele Torneira
#define pinEnaT 21

                //pinPul   pinDir
Carrinho carrinho(pinPulL, pinDirL,     // Motor Left
                  pinPulR, pinDirR,     // Motor Right
                  pinPulE, pinDirE,     // Motor Esfregão
                  pinEnaT);             // Rele Torneira

Controlador controlador(&carrinho);


// Wifi
// -------------

#define CtrlServerPort 65432
NetworkServer controladorServer(CtrlServerPort);

char ordem;

// Arduino
// -----------

void setup() {
    Serial.begin(115200);

    char ssid[] = "Carrinho Net";
    char password[] = "Carrinho_Senha";

    // Wifi Access Point Start
    if (!WiFi.softAP(ssid, password)) {
        log_e("Soft AP creation failed.");
        while (1);
    }
    IPAddress myIP = WiFi.softAPIP();

    Serial.print("AP IP address: ");
    Serial.println(myIP);

    Serial.print("Control TCP Server on Port: ");
    Serial.println(CtrlServerPort);

    controladorServer.begin();

    Serial.println("Server started");

    setupOTA();
}




void loop() {
    loopOTA();
    NetworkClient client = controladorServer.accept();  

    if (client) {
        Serial.println("Novo cliente conectado!");
        ordem = ' ';

        while (client.connected()) {
            // Ler Entrada Wifi
            if (client.available()) {
                ordem = client.read();
                Serial.write(ordem);
            }

            // Interpretar Comando recebido
            controlador.interpretarOrdens(ordem);
         
            // Executar ações do carrinho
            carrinho.update();
            loopOTA();
        }
    }
}


