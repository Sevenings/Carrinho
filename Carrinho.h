#ifndef CARRINHO_H
#define CARRINHO_H


#include <AccelStepper.h>

class Carrinho {
    private:
        // Variáveis Relacionadas aos Motores de Movimento
        // ------------------------------------------

        AccelStepper motorL;
        AccelStepper motorR;

        typedef enum {
            MOV_FRENTE,
            MOV_TRAS,
            MOV_PARADO,
            MOV_NEUTRO,
            MOV_VIRAR_HORARIO,
            MOV_VIRAR_ANTI_HORARIO
        } EstadoMovimento;

        EstadoMovimento estadoMovimento = MOV_PARADO;

        int maxSpeed = 400;
        int runningSpeed = 200;


        // Variáveis Relacionadas ao Motor do Esfregão
        // ------------------------------------------
        
        AccelStepper motorE;

        typedef enum { 
            ESF_PARADO,
            ESF_NEUTRO,
            ESF_HORARIO, 
            ESF_ANTI_HORARIO
        } EstadoEsfregao;

        EstadoEsfregao estadoEsfregao = ESF_PARADO;

        int maxSpeedEsfregao = 1600;
        int speedEsfregao = 1600;

        // Variáveis Relacionadas a torneira
        // ------------------------------------------

        bool torneiraTrancada = true;
        int pinEnaT;

    public:
        Carrinho(int pinPulL, int pinDirL, 
                 int pinPulR, int pinDirR,
                 int pinPulE, int pinDirE,
                 int pinEnaT) {
            motorL = AccelStepper(AccelStepper::DRIVER, pinPulL, pinDirL);            
            motorR = AccelStepper(AccelStepper::DRIVER, pinPulR, pinDirR);            
            motorE = AccelStepper(AccelStepper::DRIVER, pinPulE, pinDirE);            

            motorL.setMaxSpeed(maxSpeed);
            motorR.setMaxSpeed(maxSpeed);
            motorE.setMaxSpeed(maxSpeedEsfregao);

            this->pinEnaT = pinEnaT;
            pinMode(this->pinEnaT, OUTPUT);
        }

        Carrinho(int pinPulL, int pinDirL, int pinEnaL, 
                 int pinPulR, int pinDirR, int pinEnaR, 
                 int pinPulE, int pinDirE, int pinEnaE,
                 int pinEnaT)
        {
            Carrinho(pinPulL, pinDirL, pinPulR, pinDirR, pinPulE, pinDirE, pinEnaT);
            motorL.setEnablePin(pinEnaL);
            motorR.setEnablePin(pinEnaR);
            motorE.setEnablePin(pinEnaE);
        }

        // Controle Movimentos
        // -----------------------
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

        // Controles Esfregão
        // ----------------------

        void enableEsfregao() {
            estadoEsfregao = ESF_HORARIO;
        }

        void enableEsfregaoHorario() {
            estadoEsfregao = ESF_ANTI_HORARIO;
        }

        void disableEsfregao() {
            estadoEsfregao = ESF_PARADO;
        }
        // Controles Torneira
        // ----------------------

        void abrirTorneira(){
            digitalWrite(pinEnaT, HIGH);
            torneiraTrancada = false;
        }

        void fecharTorneira(){
            digitalWrite(pinEnaT, LOW);
            torneiraTrancada = true;
        }

        // Update
        // ----------

        void update() {

            // Mover Rodinhas
            switch (estadoMovimento) {
                case MOV_PARADO:
                    motorL.setSpeed(0);
                    motorR.setSpeed(0);
                    break;

                case MOV_NEUTRO:
                    motorL.setSpeed(0);
                    motorL.disableOutputs();
                    motorR.setSpeed(0);
                    motorR.disableOutputs();
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
            
            // Mover Esfregão
            switch (estadoEsfregao) {
                case ESF_PARADO:
                    motorE.setSpeed(0);
                    break;

                case ESF_NEUTRO:
                    motorE.setSpeed(0);
                    break;
                    
                case ESF_HORARIO:
                    motorE.setSpeed(speedEsfregao);
                    break;

                case ESF_ANTI_HORARIO:
                    motorE.setSpeed(-speedEsfregao);
                    break;
            }
                
            // Run padrão
            motorL.run();
            motorR.run();
            motorE.run();
        }
};

#endif
