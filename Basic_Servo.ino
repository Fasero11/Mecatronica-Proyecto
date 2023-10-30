#include <Servo.h>

Servo servo0;
/*
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;
*/
int melody[] = {0,1,0,0,0,1,1,0,1};
int bpm = 60;

int closed_pos = 110;
int open_pos = 90;
int sleeptime;
int note_counter = 0;
int note;
int number_of_notes;

void set_servos(int note){
  switch (note)
  {
      case 0:
        servo0.write(closed_pos);
        break;

      default:
        servo0.write(open_pos);
        break;
  }
}

void setup() {
  Serial.begin(9600);
  servo0.attach(9);
  /*
  servo1.attach(1);
  servo2.attach(2);
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);
  servo6.attach(6);
  servo7.attach(7);
  servo8.attach(8);
*/
  Serial.begin(9600);

  int note = melody[note_counter];
  number_of_notes = sizeof(melody) / sizeof(melody[0]);
  sleeptime = (60.0/bpm) * 1000;
  Serial.println(sleeptime);
}

void loop() {
  if (note_counter < number_of_notes){
    set_servos(note);
    Serial.println(note);
    note = melody[++note_counter];
    delay(sleeptime);
  }
  
  else {
    Serial.println("END");
    delay(10000);
  }

}