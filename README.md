# transposetaster2000

MIDI transpose device for Arduino

Simply wire a Arduiono Uno or Nano with a 74HC/HCT166 Shift-Register and two DIN-Connectors to build a Midi-Transpose Device.


## Parts used:

* Arduino Nano
* 74HC/HCT166 Shift register
* Reichelt.de: "DS 1PC :: Stufen-Drehschalter, 1 Pol, 12 Stellungen Printk."
* Two DIN 5 Pin 180° Connectors

## Description

This device will take MIDI in and send everything out to MIDI out. Just NOTE_ON and NOTE_OFF will be changed in pitch by the value of the rotary button. You can use the 12 pos Switch to transpose between -5 and +6 octaves.

## Connections

see "BOB-09598-MIDI_Breakout-v11.pdf" for connecting the MIDI to the Arduino. Connect the Shift-Registers to Pin 7,8,9 (see the Code). Connect "Latch", "Data" and "Clock" to both registers. Then daisy-chain the second Shift-Register: Connect the first Register Pin 13 to the second's Register Pin 1.
Connect the Rotary Switch to the Shift-Registers D0-D7 and D0-D3 (second) inputs.
