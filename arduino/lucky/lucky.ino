/*
 The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
 */
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

#define SELECT_PINS 50, 51, 52, 53, 28, 29, 30, 31, 32, 33, 34, 35
#define DIGITS 4
#define TOTAL_PINS 12

int selPins[] = {SELECT_PINS};
int ddel = 4;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // initialize the serial communications:
  Serial.begin(9600);

  for (int i = 0; i < 12; ++i) {
      pinMode(selPins[i], OUTPUT);
  }

  for (int i = 0; i < DIGITS; ++i) {
      // disable all digits initially
      digitalWrite(selPins[i], HIGH);
  }
}

void loop() {
  // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();

    lcd.write("hello,");
    lcd.setCursor(0, 1);
      
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      char in = Serial.read();

      if (in == '\n') break;  
      lcd.write(in);
    }

    int d1 = random(10);
    int d2 = random(10);
    int d3 = random(10);
    int d4 = random(10);

    coolAnim();

    while (!Serial.available()) {
      genLuckyNumber(d1, d2, d3, d4);
    }
  }
}

int numbers[10][8] = {
{1, 1, 1, 1, 1, 1, 0},
{0, 0, 0, 0, 1, 1, 0},
{1, 1, 0, 1, 1, 0, 1},
{1, 1, 1, 1, 0, 0, 1},
{0, 1, 1, 0, 0, 1, 1},
{1, 0, 1, 1, 0, 1, 1},
{1, 0, 1, 1, 1, 1, 1},
{1, 1, 1, 0, 0, 0, 0},
{1, 1, 1, 1, 1, 1, 1},
{1, 1, 1, 0, 0, 1, 1}
};

void writeDigit(int num) {
  for (int i = DIGITS; i < TOTAL_PINS; ++i) {
    if (numbers[num][i - DIGITS] == 1) {
      digitalWrite(selPins[i], HIGH);
    } else {
      digitalWrite(selPins[i], LOW);
    }
  }
}

void selectDigit(int digit) {
  for (int i = 0; i < DIGITS; ++i) {
      if (i == digit) { 
          digitalWrite(selPins[i], LOW);
      } else {
          digitalWrite(selPins[i], HIGH);
      }
  }
}

void coolAnim() {
  int animdelay = 70;
  
  for (int i = 0; i < DIGITS; ++i) {
      digitalWrite(selPins[i], LOW);
  }

  for (int i = DIGITS; i < TOTAL_PINS; ++i) {
    digitalWrite(selPins[i], HIGH);
    delay(animdelay);
    digitalWrite(selPins[i], LOW);
  }

  for (int i = TOTAL_PINS - 1; i > DIGITS; --i) {
    digitalWrite(selPins[i], HIGH);
    delay(animdelay);
    digitalWrite(selPins[i], LOW);
  }
}

void genLuckyNumber(int d1, int d2, int d3, int d4) {
  selectDigit(0); writeDigit(d1);
  delay(ddel);
  selectDigit(1); writeDigit(d2);
  delay(ddel);
  selectDigit(2); writeDigit(d3);
  delay(ddel);
  selectDigit(3); writeDigit(d4);
  delay(ddel);
}
