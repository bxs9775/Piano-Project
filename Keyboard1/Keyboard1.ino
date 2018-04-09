
#include <CapacitiveSensor.h>
#include "pitches.h" //same as in Melody example

/* Addapted from Tom Igoe's Melody example - http://arduino.cc/en/Tutorial/Tone */

#define outpin 3   // audio out to speaker or amp
int ledPin = 0;
int thisNote = 0;
float R = 0; //rest

/*
// make sure this array and the following one have same number of entries,
// 43. bottom array is time values
float sunshine[] =  {    
NOTE_C3, NOTE_F3, NOTE_G3, NOTE_A3, NOTE_A3, R, NOTE_A3, NOTE_G3,NOTE_A3, NOTE_F3, NOTE_F3, R,
NOTE_F3, NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_D4, R, NOTE_D4, NOTE_C4, NOTE_AS3, NOTE_A3, R, 
NOTE_F3, NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_D4, R, NOTE_D4, NOTE_C4, NOTE_AS3, NOTE_A3, NOTE_F3, R,
NOTE_F3, NOTE_G3, NOTE_A3, NOTE_AS3, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_F3};
int sunshineDur[] = {
4, 4, 4, 2, 2, 4, 4, 4, 4, 2, 2, 4,
4, 4, 4, 2, 2, 4, 4, 4, 4, 1, 4, 
4, 4, 4, 2, 2, 4, 4, 4, 4, 2, 2, 4,
4, 4, 2.5, 4, 4, 2, 4, 1.25};

// 10M resistor between pins 3 & 2, pin 2 is sensor pin,
// add a wire and or foil if desired
CapacitiveSensor   cs_10_8 = CapacitiveSensor(12,13); 
*/

int noteDuration = 1000/4;

float notes[] = { 
  NOTE_B3,NOTE_C3,NOTE_D3
};

CapacitiveSensor sensors[] = {
  CapacitiveSensor(12,13),CapacitiveSensor(10,11),CapacitiveSensor(8,9)
};

bool pressedCurr[] = {
  false,false,false
};
bool pressedLast[] = {
  false,false,false
};

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}


void loop() {
  bool notePlayed = false;
  int i = 0;
  int count = sizeof(sensors);
  while(!notePlayed && i < count){
    pressedLast[i] = pressedCurr[i];
    
    long start = millis();
    long total =  sensors[i].capacitiveSensor(30);
    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing

    Serial.print(i);
    Serial.print(": ");
    Serial.println(total);                  // print sensor output 1
    
    pressedCurr[i] = (total > 2000);
    if (pressedCurr[i] && !pressedLast[i]){
      playNote(i);
      notePlayed = true;
    }

    int k = map(total, 0, 20000, 0, 255);
    analogWrite(ledPin, k);
  }
}

/*
 // iterate over the notes of the melody
void playMelody() { 
    // to calculate the note duration, take one second 
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000/sunshineDur[thisNote];
    tone(outpin, sunshine[thisNote],noteDuration);

    delay(noteDuration);
    // stop the tone playing:
    noTone(outpin);
    
    thisNote = ++thisNote % 43; //prep next note

}
*/

//plays the note at the given index
void playNote(int index){
    //play note
    tone(outpin, notes[index],noteDuration);

    delay(noteDuration);
    // stop the tone playing:
    noTone(outpin);
}

