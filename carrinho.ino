#include <AccelStepper.h>
#include <BluetoothSerial.h>
#include "Controlador.h"
#include "Carrinho.h"

/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif






BluetoothSerial SerialBT;
Carrinho carrinho(23, 27, 26, 22);
//Controlador controlador(&carrinho);





void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32");
  Serial.println("Bluetooth Started! Ready to pair...");
}




byte command;
void loop() {
    // Ler Entrada bluetooth
    if (SerialBT.available()) {
        command = SerialBT.read();
        Serial.write(command);
    }

    // Interpretar Comando recebido
 
    carrinho.update();
}
