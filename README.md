# Arduino Macropad v2

A custom USB macropad built around the Arduino Pro Micro (ATmega32U4). The project features eight programmable keys, dual rotary encoders, media controls, and a compact 3D-printed enclosure designed in Fusion 360.

The macropad is recognized by the host computer as a standard USB HID device and can be used for productivity shortcuts, media control, streaming, CAD workflows, programming, and general desktop use.

---

## Features

* 8 programmable macro keys
* Dual rotary encoders
* Dedicated media controls
* USB HID keyboard functionality
* 3D printed enclosure
* Open source hardware and firmware
* Uses common through-hole mechanical components
* No external software required on the host computer

---

## Current Keymap

| Key   | Function                             |
| ----- | ------------------------------------ |
| Key 1 | F13                                  |
| Key 2 | F14                                  |
| Key 3 | Windows Screenshot (Win + Shift + S) |
| Key 4 | F16                                  |
| Key 5 | Previous Track                       |
| Key 6 | Next Track                           |
| Key 7 | F19                                  |
| Key 8 | F20                                  |

### Encoder A

| Input                    | Function     |
| ------------------------ | ------------ |
| Rotate Clockwise         | Volume Up    |
| Rotate Counter-Clockwise | Volume Down  |
| Press Button             | Play / Pause |

### Encoder B

Currently reserved for future functionality.

---

## Hardware

### Electronics

* Arduino Pro Micro (ATmega32U4)
* 8 × Mechanical keyboard switches
* 2 × EC11 rotary encoders with push buttons
* USB-C breakout board
* Wiring and connectors

### CAD

* Designed in Fusion 360
* Fully 3D printable enclosure
* STEP export included for modification in other CAD software

---

## Repository Contents

```text
Macropad_Code.ino          Main firmware
ArduinoMacropad Schem.pdf Wiring schematic
Macropad V2 (WIP).f3z     Fusion 360 source file
Macropad V2 (WIP).step    STEP export
Macropad V2 (WIP) v11.png Render image
```

---

## Pin Mapping

The firmware uses the Arduino internal pull-up resistors. All switches and buttons connect between the assigned pin and GND.

### Key Switches

| Key   | Pin |
| ----- | --- |
| Key 1 | D2  |
| Key 2 | D3  |
| Key 3 | D4  |
| Key 4 | D5  |
| Key 5 | D6  |
| Key 6 | D7  |
| Key 7 | D8  |
| Key 8 | D9  |

### Encoder A

| Signal | Pin |
| ------ | --- |
| Left   | D16 |
| Right  | D10 |
| Button | A1  |

### Encoder B

| Signal | Pin |
| ------ | --- |
| Left   | D15 |
| Right  | D14 |
| Button | A0  |

---

## Software

### Required Libraries

Install the following libraries through the Arduino Library Manager:

* HID-Project by NicoHood
* RotaryEncoder by Matthias Hertel

These libraries provide USB media key support and reliable rotary encoder handling.

---

## Building and Uploading

1. Install the Arduino IDE.
2. Install the required libraries.
3. Connect the Pro Micro via USB.
4. Open `Macropad_Code.ino`.
5. Select:

   * Board: Arduino Leonardo or SparkFun Pro Micro (ATmega32U4)
   * Correct COM port
6. Upload the sketch.

---

## Customization

The firmware is designed to be easy to modify.

Common customizations include:

* Application shortcuts
* CAD hotkeys
* Media controls
* OBS controls
* Discord shortcuts
* Browser controls
* Game macros

Key assignments can be modified in the `doKeyAction()` function.

Encoder actions can be modified in:

```cpp
updateEncoderA()
updateEncoderB()
```

Button actions can be modified in:

```cpp
updateEncoderAButton()
updateEncoderBButton()
```

---

## Project Images

Render:

![Macropad Render](Macropad%20V2%20\(WIP\)%20v11.png)

---

## Future Improvements

Planned upgrades include:

* Fully custom PCB
* Hot-swappable switches
* RGB lighting
* USB-C native integration
* Wireless Bluetooth version
* Additional encoder functionality
* Configurable keymaps through software
* OLED display support

---

## License

This project is open source and intended for personal, educational, and hobby use. Feel free to modify the hardware and firmware to suit your own workflow.
