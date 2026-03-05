# Arduino Macropad v2

A simple 8-key USB macropad for Arduino-compatible boards that support the `Keyboard` library (e.g., Pro Micro, Leonardo).

## What's Included
- `Macropad_Code.ino` Arduino sketch for an 8-key macro keypad
- `ArduinoMacropad Schem.pdf` wiring schematic
- `Macropad V2 (WIP).f3z` Fusion 360 source
- `Macropad V2 (WIP).step` export for CAD/CAM
- `Macropad V2 (WIP) v11.png` render/preview

## Hardware
- 8 momentary switches
- A microcontroller with USB HID keyboard support
- Common ground wiring for all switches

## Pin Map
The sketch uses internal pullups, so each switch should connect between its pin and GND.

- Buttons:
  - `BUTTON_PIN1` -> D2
  - `BUTTON_PIN2` -> D3
  - `BUTTON_PIN3` -> D4
  - `BUTTON_PIN4` -> D5
  - `BUTTON_PIN5` -> D6
  - `BUTTON_PIN6` -> D7
  - `BUTTON_PIN7` -> D8
  - `BUTTON_PIN8` -> D9
- LED (active-low): `ledPin` -> D17

## Default Key Bindings
Each button is mapped to function keys F13 to F20 by default:

- `BUTTON_KEY1` -> `KEY_F13`
- `BUTTON_KEY2` -> `KEY_F14`
- `BUTTON_KEY3` -> `KEY_F15`
- `BUTTON_KEY4` -> `KEY_F16`
- `BUTTON_KEY5` -> `KEY_F17`
- `BUTTON_KEY6` -> `KEY_F18`
- `BUTTON_KEY7` -> `KEY_F19`
- `BUTTON_KEY8` -> `KEY_F20`

## Build and Upload
1. Open `Macropad_Code.ino` in the Arduino IDE.
2. Select your board and port.
3. Upload the sketch.

## Customizing Keys
Edit the `BUTTON_KEY#` definitions at the top of `Macropad_Code.ino` to assign different keys.  
The available key codes are defined in Arduino's `Keyboard.h`.

## Safety / Failsafe
On boot, grounding pin D1 (RX) will halt the sketch and prevent keyboard input. This is useful if you upload a bad keymap.

## Notes
- Uses a simple 30 ms debounce per button.
- The LED pin is set HIGH by default (active-low).

## Future Updates
Planned ideas include BLE compatibility (ESP32), a better enclosure, and a potentiometer knob for controls like volume.
