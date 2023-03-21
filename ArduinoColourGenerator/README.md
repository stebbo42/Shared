# ArduinoColourGenerator
Make a call to a website that returns a colour code. Display this colour code using LEDs connected to the GPIO

Equipment Used:

ESP8266

RGB LED Breakout Board

160 Ohm Resistor per LED (3x)


Software Used:

Nodered

Arduino IDE

PWM for Digital Outputs - Information from:
https://randomnerdtutorials.com/esp8266-pwm-arduino-ide/

Colour Generator Code:
https://www.the-diy-life.com/arduino-rgb-colour-picker-pick-colours-from-real-life-objects/


Dataflow:

Initialise Outputs & Inputs on the ESP8266 (Done)

Initialise Wifi Connection (Done - But with hard coded credentials)

Define http endpoint that returns the colour (Done - But hardcoded)

Digest the colour and determine the correct PWM value for each RGB Channel (Done)

Write the output to the GPIO (Done)


Nice to have - Add a button to start the colour display on the leading edge of button press - Hold colour on for 30 seconds via countdown timer
