#ifndef CARRINHO_H
#define CARRINHO_H

#include <AccelStepper.h>

class Carrinho {
    private:
        AccelStepper motorL;
        AccelStepper motorR;

        typedef enum {
            MOV_FRENTE,
            MOV_TRAS,
            MOV_PARADO,
            MOV_VIRAR_HORARIO,
            MOV_VIRAR_ANTI_HORARIO
        } EstadoMovimento;

        EstadoMovimento estadoMovimento = MOV_PARADO;


        int maxSpeed = 400;
        int runningSpeed = 200;



    public:
        Carrinho(int pinPulL, int pinDirL, int pinPulR, int pinDirR) {
            motorL = AccelStepper(AccelStepper::DRIVER, pinPulL, pinDirL);            
            motorR = AccelStepper(AccelStepper::DRIVER, pinPulR, pinDirR);            

            motorL.setMaxSpeed(maxSpeed);
            motorR.setMaxSpeed(maxSpeed);
        }

        void setFrente() {
            estadoMovimento = MOV_FRENTE;
        }

        void setTras() {
            estadoMovimento = MOV_TRAS;
        }

        void setParado() {
            estadoMovimento = MOV_PARADO;
        }

        void setVirarHorario() {
            estadoMovimento = MOV_VIRAR_HORARIO;
        }

        void setVirarAntiHorario() {
            estadoMovimento = MOV_VIRAR_ANTI_HORARIO;
        }

        void setVelocidade(int velocidade) {
            runningSpeed = velocidade;
        }

        void update() {
            switch (estadoMovimento) {
                case MOV_PARADO:
                    motorL.setSpeed(0);
                    motorR.setSpeed(0);
                    break;

                case MOV_FRENTE:
                    motorL.setSpeed(runningSpeed);
                    motorR.setSpeed(runningSpeed);
                    break;

                case MOV_TRAS:
                    motorL.setSpeed(-runningSpeed);
                    motorR.setSpeed(-runningSpeed);
                    break;

                case MOV_VIRAR_HORARIO:
                    motorL.setSpeed(runningSpeed);
                    motorR.setSpeed(-runningSpeed);
                    break;

                case MOV_VIRAR_ANTI_HORARIO:
                    motorL.setSpeed(-runningSpeed);
                    motorR.setSpeed(runningSpeed);
                    break;
                }
                
            motorL.run();
            motorR.run();
        }
};

#endif
