#include <AccelStepper.h>
#include <BluetoothSerial.h>
#include "Controlador.h"
#include "Carrinho.h"

/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif






BluetoothSerial SerialBT;

// Não funcionam
// 34, 35, 36, 39

// Original
#define pinPulL 23
#define pinDirL 27
//#define pinEnaL

// Original
#define pinPulR 26
#define pinDirR 22
//#define pinEnaR

// Original
#define pinPulE 32
#define pinDirE 12
//#define pinEnaE 15


Carrinho carrinho(pinPulL, pinDirL,     // Motor Left
                  pinPulR, pinDirR,     // Motor Right
                  pinPulE, pinDirE);    // Motor Esfregão

Controlador controlador(&carrinho);





void setup() {
  Serial.begin(9600);
  SerialBT.begin("ESP32");
  Serial.println("Bluetooth Started! Ready to pair...");
}




byte ordem;
void loop() {
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


