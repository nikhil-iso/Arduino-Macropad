# Arduino-Based Macropad

Revisited 8-key Arduino Pro Micro macropad with two rotary encoders, Cherry MX Blue switches, cleaner firmware, and a smaller screw-fastened 3D printed enclosure.

I started this project in Grade 11 during COVID. At the time, I wanted to get my foot in the door with accessible engineering projects, and I remember hearing about groups that helped people with disabilities enjoy gaming by building custom input devices. That stuck with me. This macropad became my first real engineering project, and it helped point me toward human-centered hardware, accessible design, and eventually prosthesis development.

The original version was intentionally simple: an 8-key macropad built around an Arduino Pro Micro and a 3D printed friction-fit case. It was my first real experience with soldering, 3D printing, and writing Arduino code for a device I could actually use. Four years later, I revisited the same project with more experience and a better understanding of what I would change if I built it again.

---

## Project Images

![Original macropad enclosure CAD render](<Macropad V1/Macropad V2 (WIP) v11.png>)
*Original 8-key enclosure CAD render.*

![Updated macropad layout with rotary encoders and Cherry MX Blue switches](<Macropad V3/Macropad V5 v8 with rotary encoders.png>)
*Updated macropad layout with two rotary encoders and Cherry MX Blue switches.*

![Macropad internal CAD render with Pro Micro and heat-set inserts](<Macropad V3/Macropad V5 v8 heat press inserts and pro micro and inside visible .png>)
*Internal layout with the Pro Micro and heat-set inserts visible.*

![Temporary drill press jig used to install heat-set inserts](<Macropad V3/Macropad Heat press Jig.jpg>)
*Temporary drill press jig for installing heat-set inserts square and flush.*

![Macropad switches and wiring dry-fit inside the enclosure](<Macropad V3/Macropad wires and switches dry fit.jpg>)
*Switches and wiring dry-fit before final assembly.*

![Macropad interior after installing rotary encoders and wiring](<Macropad V3/Macropad insides after adding encoders.jpg>)
*Interior after adding the rotary encoders and wiring.*

---

## Design Goals

This revision keeps the spirit of the original project while improving the parts that felt unfinished after real use:

* Preserve the simple 8-key USB HID macropad layout
* Add rotary encoders for continuous input, not only on/off key presses
* Improve the feel of the board with Cherry MX Blue switches
* Reduce the enclosure size by roughly 30%
* Replace the friction-fit case with a serviceable screw-fastened assembly
* Clean up the firmware so future keymap and encoder changes are easier

The rotary encoders were an important addition because they let the board act less like a small keyboard and more like a flexible input device. A switch is basically pressed or released, but an encoder can be turned, clicked, and mapped to volume, brightness, scrolling, timeline control, CAD navigation, or other workflows.

---

## Mechanical Revision

The older enclosure worked, but it had unused volume and the friction-fit closure wore down after repeated opening. The new housing is smaller, more intentional, and fastens with screws into heat-set inserts installed in the top half of the case.

To install the inserts repeatably, I made a temporary press using a soldering iron with a heat-set insert tip mounted in a drill press. The setup kept each insert aligned at 90 degrees to the printed part and gave controlled vertical travel, so the inserts could be set flush without tilting or melting the surrounding plastic.

Before final soldering and closure, I dry-fit the switches, encoder bodies, wiring, screw bosses, and Arduino Pro Micro inside the smaller enclosure. That check caught clearance and routing issues while the case was still easy to adjust.

---

## Features

* 8 programmable macro keys
* 2 EC11 rotary encoders
* Cherry MX Blue mechanical switches
* Arduino Pro Micro with ATmega32U4
* Standard USB HID keyboard behavior
* Media key support through the HID-Project library
* Compact 3D printed enclosure designed in Fusion 360
* Screw-fastened case with heat-set inserts
* No external host software required

---

## Current Keymap

The V3 firmware currently sends F13 through F20 on the eight keys. These are useful macro keys because most programs do not already bind them by default.

| Key   | Function |
| ----- | -------- |
| Key 1 | F13      |
| Key 2 | F14      |
| Key 3 | F15      |
| Key 4 | F16      |
| Key 5 | F17      |
| Key 6 | F18      |
| Key 7 | F19      |
| Key 8 | F20      |

### Encoder A

| Input                    | Function    |
| ------------------------ | ----------- |
| Rotate clockwise         | Volume up   |
| Rotate counter-clockwise | Volume down |
| Press button             | Reserved    |

### Encoder B

| Input                    | Function |
| ------------------------ | -------- |
| Rotate clockwise         | Reserved |
| Rotate counter-clockwise | Reserved |
| Press button             | Reserved |

---

## Hardware

### Electronics

* Arduino Pro Micro, ATmega32U4
* 8 x Cherry MX Blue mechanical switches
* 2 x EC11 rotary encoders with push buttons
* USB-C breakout board
* Wiring and connectors

### CAD and Fabrication

* Fusion 360 enclosure design
* 3D printed top and bottom case
* Heat-set threaded inserts
* Screw-fastened enclosure
* STEP export included for modification in other CAD software

---

## Repository Contents

```text
Macropad V1/
  ArduinoMacropad Schem.pdf
  Macropad_Code.ino
  Macropad V2 (WIP).f3z
  Macropad V2 (WIP).step
  Macropad V2 (WIP) v11.png

Macropad V3/
  MacropadV3.ino
  Macropad V5 v8 with rotary encoders.png
  Macropad V5 v8 heat press inserts and pro micro and inside visible .png
  Macropad wires and switches dry fit.jpg
  Macropad insides after adding encoders.jpg
  Macropad Heat press Jig.jpg
```

---

## Pin Mapping

The firmware uses the Arduino internal pull-up resistors. Switches and buttons connect between the assigned pin and GND.

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
| Button | A0  |

### Encoder B

| Signal | Pin |
| ------ | --- |
| Left   | D15 |
| Right  | D14 |
| Button | A1  |

---

## Firmware

The board acts as a standard USB keyboard, so it works without custom software on the host computer. The current V3 firmware is organized around separate update functions for keys, encoder rotation, and encoder push buttons.

Required Arduino libraries:

* HID-Project by NicoHood
* RotaryEncoder by Matthias Hertel

Common changes can be made in `Macropad V3/MacropadV3.ino`:

* Key assignments: `keyCodes`
* Encoder A rotation behavior: `updateEncoderA()`
* Encoder B rotation behavior: `updateEncoderB()`
* Encoder push-button behavior: `updateEncoderButtons()`

---

## Building and Uploading

1. Install the Arduino IDE.
2. Install the required libraries through the Arduino Library Manager.
3. Connect the Arduino Pro Micro over USB.
4. Open `Macropad V3/MacropadV3.ino`.
5. Select an ATmega32U4-compatible board, such as Arduino Leonardo or SparkFun Pro Micro.
6. Select the correct COM port.
7. Upload the sketch.

---

## Future Improvements

Possible next steps:

* Custom PCB
* Hot-swappable switches
* Native USB-C integration
* Additional encoder mappings
* Configurable keymaps
* OLED display support
* Exploration of more accessibility-focused input layouts

---

Arduino Pro Micro - C++ - USB HID - Cherry MX Blue - Rotary Encoders - Fusion 360 - 3D Printing
