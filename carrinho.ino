#include <AccelStepper.h>
#include <MultiStepper.h>

class Carrinho {
    private:

    AccelStepper* motorR;
    AccelStepper* motorL;


    public:

    Carrinho(int pinDirL, int pinPulL, int pinDirR, int pinPulR) {
        this->motorR = new AccelStepper(AccelStepper::DRIVER, pinPulR, pinDirR);
        this->motorL = new AccelStepper(AccelStepper::DRIVER, pinPulL, pinDirL);
    }

    void forward(int pos) {
        motorR->
    }
}



void setup() {
}

void loop() {
}
