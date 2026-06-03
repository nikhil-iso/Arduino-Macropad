/*
  Arduino Pro Micro Macropad

  Board:
  - Arduino Pro Micro / ATmega32U4

  Libraries:
  - HID-Project by NicoHood
  - RotaryEncoder by Matthias Hertel

  Functions:
  - Keys 1-8 send F13 to F20
  - Encoder A controls volume up/down
  - Encoder B is blank for now
  - Encoder A button is A0, blank for now
  - Encoder B button is A1, blank for now
*/

#include <HID-Project.h>
#include <HID-Settings.h>
#include <RotaryEncoder.h>

// --------------------------------------------------
// Function declarations
// --------------------------------------------------

void updateKeys();
void updateEncoderA();
void updateEncoderB();
void updateEncoderButtons();

void updateBlankButton(
  int buttonPin,
  bool &lastReading,
  bool &stableState,
  unsigned long &lastDebounceTime
);

// --------------------------------------------------
// Pin definitions
// --------------------------------------------------

// Key switches
const int NUM_KEYS = 8;

const int keyPins[NUM_KEYS] = {
  2,  // Key 1
  3,  // Key 2
  4,  // Key 3
  5,  // Key 4
  6,  // Key 5
  7,  // Key 6
  8,  // Key 7
  9   // Key 8
};

const KeyboardKeycode keyCodes[NUM_KEYS] = {
  KEY_F13,
  KEY_F14,
  KEY_F15,
  KEY_F16,
  KEY_F17,
  KEY_F18,
  KEY_F19,
  KEY_F20
};

// Encoder A, volume encoder
const int ENCODER_A_LEFT   = 16;
const int ENCODER_A_RIGHT  = 10;
const int ENCODER_A_BUTTON = A0;

// Encoder B, blank encoder
const int ENCODER_B_LEFT   = 15;
const int ENCODER_B_RIGHT  = 14;
const int ENCODER_B_BUTTON = A1;

// --------------------------------------------------
// Encoder setup
// --------------------------------------------------

// Your encoder rested at state 11 in testing, so FOUR3 should match it well.
RotaryEncoder encoderA(
  ENCODER_A_LEFT,
  ENCODER_A_RIGHT,
  RotaryEncoder::LatchMode::FOUR3
);

RotaryEncoder encoderB(
  ENCODER_B_LEFT,
  ENCODER_B_RIGHT,
  RotaryEncoder::LatchMode::FOUR3
);

long lastEncoderAPosition = 0;
long lastEncoderBPosition = 0;

// --------------------------------------------------
// Debounce setup
// --------------------------------------------------

const unsigned long DEBOUNCE_DELAY = 25;

// Key state tracking
bool lastKeyReading[NUM_KEYS];
bool stableKeyState[NUM_KEYS];
unsigned long lastKeyDebounceTime[NUM_KEYS];

// Encoder button state tracking
bool lastEncoderAButtonReading;
bool stableEncoderAButtonState;
unsigned long lastEncoderAButtonDebounceTime = 0;

bool lastEncoderBButtonReading;
bool stableEncoderBButtonState;
unsigned long lastEncoderBButtonDebounceTime = 0;

// --------------------------------------------------
// Setup
// --------------------------------------------------

void setup() {
  Keyboard.begin();
  Consumer.begin();

  // Set up key switches
  for (int i = 0; i < NUM_KEYS; i++) {
    pinMode(keyPins[i], INPUT_PULLUP);

    lastKeyReading[i] = digitalRead(keyPins[i]);
    stableKeyState[i] = lastKeyReading[i];
    lastKeyDebounceTime[i] = 0;
  }

  // Encoder pins are handled by the RotaryEncoder library.
  lastEncoderAPosition = encoderA.getPosition();
  lastEncoderBPosition = encoderB.getPosition();

  // Set up encoder push buttons
  pinMode(ENCODER_A_BUTTON, INPUT_PULLUP);
  pinMode(ENCODER_B_BUTTON, INPUT_PULLUP);

  lastEncoderAButtonReading = digitalRead(ENCODER_A_BUTTON);
  stableEncoderAButtonState = lastEncoderAButtonReading;

  lastEncoderBButtonReading = digitalRead(ENCODER_B_BUTTON);
  stableEncoderBButtonState = lastEncoderBButtonReading;
}

// --------------------------------------------------
// Main loop
// --------------------------------------------------

void loop() {
  updateKeys();

  updateEncoderA();
  updateEncoderB();

  updateEncoderButtons();
}

// --------------------------------------------------
// Key handling
// --------------------------------------------------

void updateKeys() {
  for (int i = 0; i < NUM_KEYS; i++) {
    bool reading = digitalRead(keyPins[i]);

    if (reading != lastKeyReading[i]) {
      lastKeyDebounceTime[i] = millis();
      lastKeyReading[i] = reading;
    }

    if ((millis() - lastKeyDebounceTime[i]) > DEBOUNCE_DELAY) {
      if (reading != stableKeyState[i]) {
        stableKeyState[i] = reading;

        // INPUT_PULLUP logic:
        // LOW  = pressed
        // HIGH = released
        if (stableKeyState[i] == LOW) {
          Keyboard.press(keyCodes[i]);
        } else {
          Keyboard.release(keyCodes[i]);
        }
      }
    }
  }
}

// --------------------------------------------------
// Encoder A: volume control
// --------------------------------------------------

void updateEncoderA() {
  encoderA.tick();

  long currentPosition = encoderA.getPosition();

  if (currentPosition != lastEncoderAPosition) {
    if (currentPosition > lastEncoderAPosition) {
      Consumer.write(MEDIA_VOLUME_UP);
    } else {
      Consumer.write(MEDIA_VOLUME_DOWN);
    }

    lastEncoderAPosition = currentPosition;
  }
}

// --------------------------------------------------
// Encoder B: blank for now
// --------------------------------------------------

void updateEncoderB() {
  encoderB.tick();

  long currentPosition = encoderB.getPosition();

  if (currentPosition != lastEncoderBPosition) {
    // Encoder B intentionally does nothing for now.

    lastEncoderBPosition = currentPosition;
  }
}

// --------------------------------------------------
// Encoder buttons: blank for now
// --------------------------------------------------

void updateEncoderButtons() {
  updateBlankButton(
    ENCODER_A_BUTTON,
    lastEncoderAButtonReading,
    stableEncoderAButtonState,
    lastEncoderAButtonDebounceTime
  );

  updateBlankButton(
    ENCODER_B_BUTTON,
    lastEncoderBButtonReading,
    stableEncoderBButtonState,
    lastEncoderBButtonDebounceTime
  );
}

void updateBlankButton(
  int buttonPin,
  bool &lastReading,
  bool &stableState,
  unsigned long &lastDebounceTime
) {
  bool reading = digitalRead(buttonPin);

  if (reading != lastReading) {
    lastDebounceTime = millis();
    lastReading = reading;
  }

  if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
    if (reading != stableState) {
      stableState = reading;

      // Button is intentionally blank for now.
      // LOW  = pressed
      // HIGH = released
    }
  }
}