# DriveFX Pedals as Standalone USB Axes (Arduino Uno + vJoy)

## Overview
This project turns **Logitech DriveFX racing pedals** into a **standalone joystick device** using:
- **Arduino Uno** (reads the pedal potentiometers)
- **vJoy** (virtual joystick driver for Windows)
- **vJoySerialFeeder** (feeds serial data into vJoy)

This way, the pedals can be recognized as throttle and brake axes in racing sims.

---

## Hardware
- Arduino Uno (any model with analog inputs)
- Logitech DriveFX pedals
- Jumper wires
- Optional: DB9 connector for neat wiring

---

## Software Requirements
- [Arduino IDE](https://www.arduino.cc/en/software)
- [vJoy driver](https://sourceforge.net/projects/vjoystick/)
- [vJoySerialFeeder](https://github.com/jshafer817/vJoySerialFeeder)

---

## Wiring
DriveFX pedal DB9 pinout:

-Pin 3 - Throttle potentiometer wiper → Arduino A1
-Pin 4 - +5V → Arduino 5V
-Pin 6 - GND → Arduino GND
-Pin 8 - Brake potentiometer wiper → Arduino A0

## vJoy Setup

Install vJoy and open vJoyConfig.

Create a device with at least 2 axes (X = Gas, Y = Brake).

No buttons are required unless you plan to add them later.


## vJoySerialFeeder Setup

Launch vJoySerialFeeder.

Make sure you select the correct port.

Add at the port setup Baud rate = 115200

Set input mode to CSV.

Map:

CH1 → X Axis (Gas)

CH2 → Y Axis (Brake)

Enable Auto-Scale, or set manual min/max.
