#include <Arduino.h>

/*
I, Mychaylo Tatarynov, student number 000800271, certify that all code submitted is my own work; 
that I have not copied it from any other source. 
I also certify that I have not allowed my work to be copied by others.

2022/09/26
*/

//Whether or not the LED should be on.
bool LEDState = 0;
//Stores the button's state last iteration.
int LastButtonState = 1;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  Serial.println("\n\nName: Mychaylo Tatarynov (000800271)");
  Serial.println("ESP8266 Chip Id: " + String(ESP.getChipId()));
  Serial.println("Flash Chip Id: " + String(ESP.getFlashChipId()) + "\n");

  //Button as digital input.
  pinMode(D5, INPUT_PULLUP);
  //LED as the PWM output.
  pinMode(D4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  bool buttonState = digitalRead(D5);
  //We want to toggle the LED only once while the button is pressed.
  bool buttonPressed = buttonState && buttonState != LastButtonState;
  
  //If the button was pressed, reverse the LED's state.
  if (buttonPressed) {
    LEDState = LEDState == 0 ? 1 : 0;
  }

  //Get the input from the potentiometer.
  int pot = analogRead(A0);
  //The analog output is within 1-256 rather than 1-1024, so the pot input must be quartered.
  int brightness = (LEDState * pot) / 4;
  
  //The LED is wired in reverse so the opposite of the brightness value is necessary.
  analogWrite(D4, 256 - brightness);

  LastButtonState = buttonState;
}