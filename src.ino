// © Mark Steffes, inspired by https://www.instructables.com/Audio-Treasure-Hunt/ and https://www.youtube.com/watch?v=CC1LJgOTENY
// my Proect uses the newer Mp3-Shield by Adafruit.

// Don't forget to customize at least the check_buttons() function since you probably won't use the same Pins as me
// Look up the documentation for the Adafruit MusicMaker Mp3 Shield to learn more about how to name the mp3-files on the sd-card, otherwise they can't be played!

// include SPI, Adafruit Mp3-Shield and SD libraries
#include <SPI.h>
#include <Adafruit_VS1053.h>  // VS1053 Library is compatible with Mp3-Shield
#include <SD.h>

#define DEBOUNCE 100  // what is this?

// Defining pins for Mp3-Shield (preset from example project)
#define BREAKOUT_RESET 9  // VS1053 reset pin (output)
#define BREAKOUT_CS 10    // VS1053 chip select pin (output)
#define BREAKOUT_DCS 8    // VS1053 Data/command select pin (output)
// These are the pins used for the music maker shield
#define SHIELD_RESET -1  // VS1053 reset pin (unused!)
#define SHIELD_CS 7      // VS1053 chip select pin (output)
#define SHIELD_DCS 6     // VS1053 Data/command select pin (output)

// These are common pins between breakout and shield
#define CARDCS 4  // Card chip select pin
// DREQ should be an Int pin, see http://arduino.cc/en/Reference/attachInterrupt
#define DREQ 3  // VS1053 Data request, ideally an Interrupt pin

Adafruit_VS1053_FilePlayer musicPlayer =
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);  // Preset from online documentation

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing Audio Treasure Hunt... ");

  if (!musicPlayer.begin()) {  // initialise the music player
    Serial.println(F("Couldn't find Mp3 Shield, do you have the right pins defined?"));
    while (1)
      ;
  }
  Serial.println(F("Mp3-Shield found"));

  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1)
      ;
  }

  // Set volume for left, right channels. lower numbers == louder volume!
  musicPlayer.setVolume(5, 5);

  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);  // DREQ int

  Serial.println("Done initializing Audio Treasure Hunt!");
}

void loop() {

  // This Array includes all secret codes, secretCodes[CodeNumber][pressedIndex]
  // Every secretCode consists of six numbers.
  const int amountOfCodes = 29;

  // Some Arrays are empty because I'm not done with my personal project yet. The code works anyways.
  const int secretCodes[amountOfCodes][6] = {

    { 5, 5, 1, 5, 1, 3 },
    { 2, 2, 2, 2, 2, 2 },
    { 2, 4, 6, 1, 3, 5 },
    { 1, 2, 3, 5, 5, 5 },
    { 1, 2, 3, 3, 2, 1 },
    { 1, 2, 3, 4, 5, 1 },
    {},
    {},
    { 5, 5, 5, 5, 5, 5 },
    {},
    {},
    {},
    {},
    {},
    {},
    { 4, 4, 4, 4, 4, 4 },
    {},
    {},
    {},
    {},
    {},
    {},
    { 6, 6, 6, 6, 6, 6 },
    {},
    {},
    {},
    {},
    {},
    {}

    // New Codes can be added here. Don't forget to change the lenght of the Array!

  };



  // Button Input
  // if you want to change the amount of buttons, change the 1. length of the enteredCode[] Array, 2. the for loops header and 3. the condition including correct keys
  int enteredCode[6] = { 0, 0, 0, 0, 0, 0 };  // Array for buttonInput | 1.
  int correctKeys = 0;
  int success = 0;
  byte pressed;  //stores values of button pressed
  int i = 0;

  // 2.
  // Iterate over all buttons via check_buttons() until a button is pressed
  for (i = 0; i < 6; i++) {
    do {
      pressed = check_buttons();
    } while (pressed < 1);

    enteredCode[i] = pressed;
    delay(500);
    Serial.println(enteredCode[i]);  // Debugging
  }

  // 2.
  // Debugging
  for (i = 0; i < 6; ++i) {
    Serial.print(enteredCode[i]);
  }
  Serial.println();

  // Check if enteredCode[] matches with one code inside of secretCodes[][]
  for (int secretCode = 0; secretCode < amountOfCodes; ++secretCode) {
    for (int chara = 0; chara < 6; ++chara) {  // 2.
      if (enteredCode[chara] == secretCodes[secretCode][chara]) {
        correctKeys = correctKeys + 1;
      }
    }

    // 3.
    if (correctKeys == 6) {
      Serial.print("Matching Code found at ");
      Serial.println(secretCode);
      Serial.print("Playing secret message no. ");
      Serial.println(secretCode);

      // Play secretMessage
      musicPlayer.stopPlaying();
      String path = "/" + String(secretCode) + ".mp3";  // (name your secretmessages according to this scheme)
      musicPlayer.playFullFile(path.c_str());

      success = 1;
    }

    correctKeys = 0;
  }

  // Errorhandler
  if (success == 1) {
    success = 0;
  } else {
    Serial.println("No matching code found!");

    musicPlayer.stopPlaying();
    musicPlayer.playFullFile("/error.mp3");
  }
}

// returns which button was pressed
// change this function according to your button layout and pin layout
// I used the Mp3-Shield's included GPIOs for convinience. This way, you can only connect 6 Buttons since the first GPIO-Pin is some kind of special pin since the first GPIO-Pin is some kind of special pin
byte check_buttons() {
  byte pressed = 0;

  for (uint8_t i = 2; i < 8; i++) {  // The first GPIO-Pin is not used!
    musicPlayer.GPIO_pinMode(i, INPUT);

    if (musicPlayer.GPIO_digitalRead(i) != 0) {
      pressed = i - 1;

      musicPlayer.stopPlaying();
      // Plays a sound when you press a button, it's hard to know wheather the buttonpress was received or not without
      musicPlayer.playFullFile("/feedback.mp3");
    }
  }
  return (pressed);  // returns which button was pressed
}
