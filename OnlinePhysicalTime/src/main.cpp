#include <Arduino.h>

// Pin Definitions         {A, B, C, D};
const int IC74154_PINS[] =  {2, 3, 4, 5};
const int IC7447_PINS[] = {6, 7, 8, 9};
#define GateEnable  10
#define LED_PWM_PIN A0
#define RED_LED     2
#define BLUE_LED    1
#define GREEN_LED   0

// Define the BCD digit to 4-digit binary code mapping


// 0 - 15 array which stores the 4-digit binary code for each position
int positionToPinMapping[18] = {0, 1, 2, 3, 4, 5, 6, 7, 8,  13,  14,  15,  12,  9,  10, 11};
                          //   {G, B, R, B, R, G, G, G, :,  VI, VII,  IV,   I, II, III, V }

int PWMVAL[10] = {1, 1, 1, 0, 0, 0, 0, 0, 0};
//               {G, B, R, B, R, G, G, G, :}

// Shift Register Pins
int HexToBin[16][4] = {
  {0, 0, 0, 0}, // 0
  {0, 0, 0, 1}, // 1
  {0, 0, 1, 0}, // 2
  {0, 0, 1, 1}, // 3
  {0, 1, 0, 0}, // 4
  {0, 1, 0, 1}, // 5
  {0, 1, 1, 0}, // 6
  {0, 1, 1, 1}, // 7
  {1, 0, 0, 0}, // 8 
  {1, 0, 0, 1}, // 9
  {1, 0, 1, 0}, // 10
  {1, 0, 1, 1}, // 11
  {1, 1, 0, 0}, // 12
  {1, 1, 0, 1}, // 13
  {1, 1, 1, 0}, // 14
  {1, 1, 1, 1}  // 15
};
void setup() {
  // Pin Mode Setup
  pinMode(GateEnable, OUTPUT);
  pinMode(LED_PWM_PIN, OUTPUT);
  Serial.begin(9600);
  for(int i=0; i<4; i++) {
    pinMode(IC7447_PINS[i], OUTPUT);
    pinMode(IC74154_PINS[i], OUTPUT);
  }
}


void disp(int position, int digit) {
  for(int j=0; j<4; j++)
      digitalWrite(IC74154_PINS[j], HexToBin[positionToPinMapping[position]][j]);
    
    digitalWrite(GateEnable, HIGH);
    for(int j=0; j<4; j++)
    {
      digitalWrite(IC74154_PINS[j], HexToBin[positionToPinMapping[(position) + 9]][j]);
      digitalWrite(IC7447_PINS [j], HexToBin[digit][j]);
    }
      delayMicroseconds(100);
    digitalWrite(GateEnable, LOW);
}
// breaks number using stirngs
void numbreaker(long int num) {
  // reverse the digits
  num = num + 10000000; 
  long int reversedNum = 0;
  while (num != 0) {
    int digit = num % 10;
    reversedNum = reversedNum * 10 + digit;
    num /= 10;
  }
  num = reversedNum;
  num /= 10; // Discard the first digit
  for(int i=0; i<15 ; i++)
  {
    int digit = num % 10;    // Get the digit
    disp(i, digit);   // Display the digit at the position
    num /= 10;        // Remove the last digit
  }
}
void loop() {
  numbreaker(1234567)
}