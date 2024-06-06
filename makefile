SKETCH=carrinho.ino
FQBN=esp32:esp32:esp32
PORT=/dev/ttyACM0

# https://arduino.github.io/arduino-cli/0.35/getting-started/

build:
	arduino-cli compile --fqbn $(FQBN) 

run:
	arduino-cli upload -p $(PORT) --fqbn $(FQBN)

monitor:
	arduino-cli monitor -p $(PORT)

all: build run monitor
