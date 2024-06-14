#include <AccelStepper.h>
#include <BluetoothSerial.h>
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


// Bluetooth
// -------------

/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif

BluetoothSerial SerialBT;
byte ordem;


MyOtaService myOtaService;


void setup() {
    Serial.begin(9600);
    SerialBT.begin("ESP32");

    myOtaService.setupOTA();
}




void loop() {
    myOtaService.loopOTA();

    // Ler Entrada bluetooth
    if (SerialBT.available()) {
        ordem = SerialBT.read();
        Serial.write(ordem);
    }

    // Interpretar Comando recebido
    controlador.interpretarOrdens(ordem);

 
    // Executar ações do carrinho
    carrinho.update();
}


