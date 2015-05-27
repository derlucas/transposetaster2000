#include <MIDI.h>

MIDI_CREATE_DEFAULT_INSTANCE();

int latchPin = 8;
int dataPin = 9;
int clockPin = 7;

byte switchVar1 = 72;  //01001000
byte switchVar2 = 159; //10011111
uint16_t both = 0;
int8_t transpose = 0;
uint8_t counter = 0;

void handleNoteOn(byte channel, byte pitch, byte velocity) {
  // Send a Note (pitch 42, velo 127 on channel 1)
  MIDI.sendNoteOn(pitch+transpose,velocity,channel);
}

void handleNoteOff(byte channel, byte pitch, byte velocity) {
  MIDI.sendNoteOff(pitch+transpose,velocity,channel);
}


void setup() {
  
  MIDI.turnThruOff();
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
  MIDI.turnThruOff();

  //define pin modes
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT); 
  pinMode(dataPin, INPUT);

}

void loop() {

  if(MIDI.read()) {
    int type = MIDI.getType();
    if(type != 0x80 && type != 0x90) {
      MIDI.send(MIDI.getType(),MIDI.getData1(),MIDI.getData2(),MIDI.getChannel()); 
    }  
  } 
  
  if(++counter > 250) {
    counter = 0;

    digitalWrite(latchPin,1);
    delayMicroseconds(20);
    digitalWrite(latchPin,0);

    switchVar1 = shiftIn(dataPin, clockPin);
    switchVar2 = shiftIn(dataPin, clockPin);

    both = switchVar1 + (switchVar2 << 8);

    switch(both) {
    case 1:
      transpose = -5;
      break;
    case 2048:
      transpose = -4;
      break;
    case 1024:
      transpose = -3;
      break;
    case 512:
      transpose = -2;
      break;
    case 256:
      transpose = -1;
      break;
    default:
    case 64:
      transpose = 0;
      break;
    case 32:
      transpose = 1;
      break;
    case 16:
      transpose = 2;
      break;
    case 128:
      transpose = 3;
      break;
    case 8:
      transpose = 4;
      break;  
    case 4:
      transpose = 5;
      break;
    case 0:
      transpose = 6;
      break;
    }
  }

  
}


byte shiftIn(int myDataPin, int myClockPin) { 
  int i;
  int temp = 0;
  int pinState;
  byte myDataIn = 0;

  pinMode(myClockPin, OUTPUT);
  pinMode(myDataPin, INPUT);

  for (i=7; i>=0; i--)
  {
    digitalWrite(myClockPin, 0);
    delayMicroseconds(2);
    temp = digitalRead(myDataPin);
    if (temp) {
      pinState = 1;
      //set the bit to 0 no matter what
      myDataIn = myDataIn | (1 << i);
    }
    else {
      pinState = 0;
    }

    digitalWrite(myClockPin, 1);

  }
  return myDataIn;
}

