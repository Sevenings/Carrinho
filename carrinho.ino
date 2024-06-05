#include <AccelStepper.h>
#include <BluetoothSerial.h>

/* Check if Bluetooth configurations are enabled in the SDK */
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run make menuconfig to and enable it
#endif


typedef enum EstadoMovimento {
    FRENTE,
    TRAS,
    PARADO,
    VIRAR_HORARIO,
    VIRAR_ANTI_HORARIO
} EstadoMovimento;


class Carrinho {
    private:
        AccelStepper motorL;
        AccelStepper motorR;

        EstadoMovimento estadoMovimento = PARADO;

        int maxSpeed = 400;
        int runningSpeed = 400;

    public:
        Carrinho(int pinPulL, int pinDirL, int pinPulR, int pinDirR) {
            motorL = AccelStepper(AccelStepper::DRIVER, pinPulL, pinDirL);            
            motorR = AccelStepper(AccelStepper::DRIVER, pinPulR, pinDirR);            

            motorL.setMaxSpeed(maxSpeed);
            motorR.setMaxSpeed(maxSpeed);
        }

        void setFrente() {
            estadoMovimento = FRENTE;
        }

        void setTras() {
            estadoMovimento = TRAS;
        }

        void setParado() {
            estadoMovimento = PARADO;
        }

        void setVirarHorario() {
            estadoMovimento = VIRAR_HORARIO;
        }

        void setVirarAntiHorario() {
            estadoMovimento = VIRAR_ANTI_HORARIO;
        }

        void update() {
            switch (estadoMovimento) {
                case PARADO:
                    motorL.setSpeed(0);
                    motorR.setSpeed(0);
                    break;

                case FRENTE:
                    motorL.setSpeed(runningSpeed);
                    motorR.setSpeed(runningSpeed);
                    break;

                case TRAS:
                    motorL.setSpeed(-runningSpeed);
                    motorR.setSpeed(-runningSpeed);
                    break;

                case VIRAR_HORARIO:
                    motorL.setSpeed(runningSpeed);
                    motorR.setSpeed(-runningSpeed);
                    break;
                }
                
            motorL.run();
            motorR.run();
        }
};



BluetoothSerial SerialBT;
Carrinho carrinho(23, 27, 26, 22);


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

    //Andar para Frente
    if (command=='1') {
        carrinho.setFrente();
    }

    // Andar para Trás
    if (command == '2') {
        carrinho.setTras();
    }

    // Parar
    if (command == '0') {
        carrinho.setParado();
    }

    // Virar Horario
    if (command == '3') {
        carrinho.setVirarHorario();
    }

    // Virar Anti Horario
    if(command == '4'){
        carrinho.setVirarAntiHorario();
    }
  
    carrinho.update();
}
