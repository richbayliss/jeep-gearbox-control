#include <Arduino.h>

// The Jeep Transmission Range Sensor detects the selected gearstick position and directs outputs of 12Volts on four wires direct to the Transmission Control Module.
// There are 8 gearshift positions each having a Hall Effect sensor which can sink 20mA when in proximity of a magnet
// There MUST be ONE and only ONE input pulled LOW at any time to have valid data to the TCM.
// None or two will be an error and should leave the current outputs fixed until a valid input is recieved
//
//The outputs will be interfaced with NPN transistors to allow logic level 12V switching
// Define input pin applications

const int PIN_P = 4; //Park input
const int PIN_R = 5; //Reverse input
const int PIN_N = A5; //Neutral   (PINC)
const int PIN_D = A4; //Drive
const int PIN_D4 = A3; //D4
const int PIN_D3 = A2; //D3
const int PIN_D2 = A1; //D2
const int PIN_D1 = A0; //D1

void setup() {
  // 4 output for TRS matrix to TCM (PINB0-3)
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);

  // 8 inputs from hall effect sensors for gearshift position
  pinMode(PIN_P,INPUT);
  pinMode(PIN_R,INPUT);
  pinMode(PIN_N,INPUT);
  pinMode(PIN_D,INPUT);
  pinMode(PIN_D4,INPUT); 
  pinMode(PIN_D3,INPUT); 
  pinMode(PIN_D2,INPUT); 
  pinMode(PIN_D1,INPUT); 
}

void loop() {
  int forwardGear = PINC & 0B111111;
  int reverse = digitalRead(PIN_R) << 7;
  int park = digitalRead(PIN_P) << 8;

  int selectedGear = forwardGear + reverse + park;

  switch (selectedGear)
  {
    case 1:
      PINB |= 13;
      break;
    case 2:
      PINB |= 8;
      break;
    case 4:
      PINB |= 9;
      break;
    case 8:
      PINB |= 12;
      break;
    case 16:
      PINB |= 10;
      break;
    case 32:
      PINB |= 14;
      break;
    case 64:
      PINB |= 15;
      break;
    case 128:
      PINB |= 11;
      break;
    default: // this would indicate multiple/no gears selected
      break;
  }
}