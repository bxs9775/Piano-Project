
#include <CapacitiveSensor.h>
#include "pitches.h" //same as in Melody example

/* Addapted from Tom Igoe's Melody example - http://arduino.cc/en/Tutorial/Tone */

#define outpin 3   // audio out to speaker or amp
int ledPin = 0;

int noteDuration = 1000/2;

float notes[] = { 
  NOTE_A3,NOTE_B3,NOTE_C3,NOTE_D3,NOTE_E3
};

CapacitiveSensor sensors[] = {
  CapacitiveSensor(12,13),CapacitiveSensor(10,11),CapacitiveSensor(8,9),CapacitiveSensor(6,7),CapacitiveSensor(4,5)
};

bool pressedCurr[] = {
  false,false,false,false,false
};
bool pressedLast[] = {
  false,false,false,false,false
};

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}


void loop() {
  bool notePlayed = false;
  int i = 0;
  int count = 5;
  Serial.print("Count: ");
  Serial.println(count);
  
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
    i++;
  }
  if(!notePlayed){
    delay(noteDuration);
  }
}

//plays the note at the given index
void playNote(int index){
    //play note
    tone(outpin, notes[index],noteDuration);

    delay(noteDuration);
    // stop the tone playing:
    noTone(outpin);
}

