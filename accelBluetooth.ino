#include <AccelStepper.h>
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
byte command;
int velocidade = 0;

AccelStepper stepper(AccelStepper::DRIVER,26,22);
AccelStepper stepper2(AccelStepper::DRIVER,23,27);

/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif


void setup() {
  stepper.setMaxSpeed(100);
  //stepper.setAcceleration(20);
  stepper2.setMaxSpeed(100);
  //stepper2.setAcceleration(-20);

  Serial.begin(115200);
  SerialBT.begin("ESP32");
  Serial.println("Bluetooth Started! Ready to pair...");
 
}


typedef enum Estado {
    FRENTE,
    TRAS,
    PARADO,
    VIRAR_HORARIO
} Estado;

Estado estado = PARADO;

void loop() {
  if(SerialBT.available()){
    command = SerialBT.read();
    Serial.write(command);
  }
  //Andar para frente
  if(command=='1'){
    estado = FRENTE;
  }
  // Para Trás
  if(command == '2'){
      estado = TRAS;
  }

  // Parar
  if(command == '0'){
      estado = PARADO;
  }

  if(command == '3'){
      estado = VIRAR_HORARIO;
  }
  


  switch (estado) {
    case PARADO:
        stepper.setSpeed(0);
        stepper2.setSpeed(0);
        break;

    case FRENTE:
        stepper.setSpeed(velocidade);
        stepper2.setSpeed(velocidade);
        break;

    case TRAS:
        stepper.setSpeed(-velocidade);
        stepper2.setSpeed(-velocidade);
        break;
    case VIRAR_HORARIO:
        stepper.setSpeed(velocidade);
        stepper2.setSpeed(-velocidade);
        break;
  }

  stepper.run();
  stepper2.run();
}