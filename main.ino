#include <LiquidCrystal.h>
#include <string.h>
 
// CONSTANTS
int RS = 4;
int EN = 6;
int D4 = 10;
int D5 = 11;
int D6 = 12;
int D7 = 13;
int SPEAKER_PIN = 9;
 
 
// Function prototypes 
void start();
int checkPressed();
void optionOne();
void enc(int algo);
void xorEnc();
void caeserCipher();
 
// Global variables
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
int buttons[] = {2, 3, 5}; // Pins that buttons are attached to. Button corresponding to 1st choice is
int algorithmSelection = 3; // The algorithm the user has selected 
 
 
 
// Function definitions
 
// Displays main menu
 
void xorEnc(char *message, int key) {
  while (*message) {
    *message = *message ^ key;
    message++;
  }
}
 
void caeserCipher(char *message, int shift) {
  while (*message) {
    // apply some sort of shift
    *message = *message + shift;  
    if (*message > 90)
      *message = *message - 26;
    message++;
  }
}
 
  
 
 
void start() {
  int selection = 0;
  short counter = 0;
  char *options[] = {"1. XOR", "2. Caesar Cipher"};
 
  while (algorithmSelection == 3) {
    algorithmSelection = checkPressed();
    lcd.setCursor(0, 0);
    lcd.print("Select Algorithm");
    lcd.setCursor(0, 1);
    lcd.print(options[counter]);
    if (counter == 1) {
      counter = 0;
    } else {
      counter++;
    }
    delay(500);
 
    lcd.clear();
  }
}
 
// Checks if a button is pressed
int checkPressed() {
  if (algorithmSelection != 3)
    return algorithmSelection;
  for (int i = 0; i < 3; i++) {
    if (digitalRead(buttons[i]) == LOW)
      return i;
  }
  return 3;
}
 
// Runs if the user selects option one.
void optionOne() {
  delay(500);
  int choice;
  int counter = 0;
  while (1) {
    lcd.setCursor(0, 0);
    lcd.print("Selected - XOR");
    lcd.setCursor(0, 1);
    lcd.print("Ready to encrypt?");
    if (checkPressed() == 0) {
      enc(0);
      break;
    }
    delay(700);
    lcd.clear();
  }
    
}
 
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600);
  for (int i = 0; i < 3; i++)
    pinMode(buttons[i], INPUT_PULLUP);
 
  //start();
 
}
 
void enc(int algo) {
  int key = 0;
  char plaintext[17];
  for (int i = 0; i < 16; i++)
    plaintext[i] == ' ';
  Serial.println("Plaintext cleared.");
  plaintext[16] = '\0';
  int counter = 0;
  char letter = 'A';
  int encryptNow = 0;
  int gettingKey = 0;
  int gettingPlaintext = 0;
  int displayingCiphertext = 0;
  switch (algo) {
    case 0:
      gettingKey = 1;
      while (gettingKey) {
        lcd.setCursor(0, 0);
        lcd.print("SELECT KEY - XOR");
        lcd.setCursor(0, 1);
        lcd.print(key);
 
        if (checkPressed() == 0)
          key = (key > 0 ? key - 1: key);
        else if (checkPressed() == 1)
          key = (key < 255 ? key + 1: key);
        else if (checkPressed() == 2) {
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("KEY SELECTED");
          lcd.setCursor(0, 1);
          lcd.print("ENTER PLAINTEXT!");
          delay(1000);
          lcd.clear();
 
          gettingPlaintext = 1;
          gettingKey = 0;
          while (gettingPlaintext) {
            //plaintext[0] = ' ';
            lcd.setCursor(0, 0);
            //plaintext[counter + 1] = '\0';
            lcd.print(plaintext);
            Serial.println(plaintext);
            lcd.setCursor(0, 1);
            lcd.print(letter);
            Serial.println(letter);
 
            // CHECK IF COUNTER > 16 OR the done button is pressed
            if (checkPressed() == 0) {
              letter = (letter > 33 ? letter - 1: letter);
            }
            else if (checkPressed() == 1) {
              letter = (letter < 126 ? letter + 1: letter);
            }
            else if (checkPressed() == 2) {
              lcd.clear();
              lcd.setCursor(0, 0);
              plaintext[counter] = letter;
              Serial.println(plaintext); // This seems to have made it work...
              counter += 1;
              if (counter > 15) {
                encryptNow = 1;
                plaintext[16] = '\0';
              }
              // Ask if done?
              delay(800);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.clear();
              lcd.print("Are you done?");
              while (1) {
                lcd.clear();
                lcd.print("Are you done?");
                if (checkPressed() == 0) {
                  encryptNow = 1;
                  break;
                }
                else if (checkPressed() == 1) {
                  lcd.clear();
                  break;
                }
                delay(300);
              }
 
              delay(1000);
              if (encryptNow) {
                plaintext[16] = '\0';
                xorEnc(plaintext, key);
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Ciphertext:");
                lcd.setCursor(0, 1);
                lcd.print(plaintext);
 
                gettingPlaintext = 0;
                displayingCiphertext = 1;
                while (displayingCiphertext){
                  if (checkPressed() != 3)
                    displayingCiphertext = 0;
                }
              }
               
            }
            
            delay(300);
          }
        }
        delay(150);
        lcd.clear();
      }
      break;
 
  case 2:
    plaintext[0] == ' ';
    Serial.println("Caeser case");
    gettingKey = 1;
    while (gettingKey) {
      lcd.setCursor(0, 0);
      lcd.print("SELECT SHIFT - CC");
      lcd.setCursor(0, 1);
      lcd.print(key);
 
      if (checkPressed() == 0)
        key = (key > 0 ? key - 1: key);
      else if (checkPressed() == 1)
        key = (key < 25 ? key + 1: key);
      else if (checkPressed() == 2) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("SHIFT SELECTED");
        lcd.setCursor(0, 1);
        lcd.print("ENTER PLAINTEXT!");
        delay(1000);
        lcd.clear();
 
        gettingPlaintext = 1;
        gettingKey = 0;
        while (gettingPlaintext) {
        //plaintext[0] = ' ';
        lcd.setCursor(0, 0);
        plaintext[counter + 1] = '\0';
        lcd.print(plaintext);
        Serial.println(plaintext);
        lcd.setCursor(0, 1);
        lcd.print(letter);
        Serial.println(letter);
 
        // CHECK IF COUNTER > 16 OR the done button is pressed
        if (checkPressed() == 0) {
          letter = (letter > 'A' ? letter - 1: letter);
        }
        else if (checkPressed() == 1) {
          letter = (letter < 'Z' ? letter + 1: letter);
        }
        else if (checkPressed() == 2) {
          lcd.clear();
          lcd.setCursor(0, 0);
          plaintext[counter] = letter;
            Serial.println(plaintext);
            counter += 1;
            if (counter > 15) {
              encryptNow = 1;
              plaintext[16] = '\0';
            }
            // Ask if done?
            delay(800);
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.clear();
            lcd.print("Are you done?");
            while (1) {
              lcd.clear();
              lcd.print("Are you done?");
              if (checkPressed() == 0) {
                encryptNow = 1;
                break;
              }
              else if (checkPressed() == 1) {
                lcd.clear();
                break;
              }
              delay(300);
            }
 
            delay(1000);
            if (encryptNow) {
              plaintext[16] = '\0';
              caeserCipher(plaintext, key);
              lcd.clear();
              lcd.setCursor(0, 0);
              lcd.print("Ciphertext:");
              lcd.setCursor(0, 1);
              lcd.print(plaintext);
 
              gettingPlaintext = 0;
              displayingCiphertext = 1;
              while (displayingCiphertext){
                if (checkPressed() != 3)
                  displayingCiphertext = 0;
              }
            }
             
          }
          
          delay(300);
        }
      }
      delay(150);
      lcd.clear();
    }       
  }
}
 
void optionTwo() {
  delay(500);
  int choice;
  int counter = 0;
  while (1) {
    lcd.setCursor(0, 0);
    lcd.print("Selected - CC");
    lcd.setCursor(0, 1);
    lcd.print("Ready to encrypt?");
    if (checkPressed() == 0) {
      enc(2);
      break;
    }
    delay(700);
    lcd.clear();
  }
    
}
 
void loop() { // Bug is that morse code case cannot detect pushes
    start();
    switch(algorithmSelection) {
      case 0:
        algorithmSelection = 3;
        optionOne();
        break;
      case 1:
        algorithmSelection = 3;
        optionTwo();
        break;
    }
}
 
