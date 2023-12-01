#include <Servo.h>

// ONLY WORKS IN C MAJOR.
// ONLY PLAYS QUARTER NOTES.

#define PIN_SERVO0 20
#define PIN_SERVO1 19
#define PIN_SERVO2 18
#define PIN_SERVO3 13

#define C 0
#define D 1
#define E 2
#define F 3
#define G 4

int servo0_opened = 90;
int servo0_closed = 105;

int servo1_opened = 95;
int servo1_closed = 120;

int servo2_opened = 120;
int servo2_closed = 152;

int servo3_opened = 110;
int servo3_closed = 120;

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;

int note;
/*
int song[] = {E,E,E,C,G,E,C,G,E}; // The imperial march
float song_times[] = {1,1,1,0.75,0.25,1,0.75,0.25,2};
int song_bpm = 30;
int number_of_notes = 9;
*/

int song[] = {E,E,F,G,G,F,E,D,C,C,D,E,E,D,D,E,E,F,G,G,F,E,D,C,C,D,E,D,C,C}; // Ode to Joy (C major)
float song_times[] = {1,1,1,1,1,1,1,1,1,1,1,1,1.5,0.5,2,1,1,1,1,1,1,1,1,1,1,1,1,1.5,0.5,2};
int song_bpm = 80;
int number_of_notes = 30;

int note_counter, sleeptime, init_time, wait_time;

void play_C(){
  Serial.println("C");
  servo0.write(servo0_closed);
  servo1.write(servo1_closed);
  servo2.write(servo2_closed);
  servo3.write(servo3_closed);

}

void play_D(){
  Serial.println("D");
  servo0.write(servo0_opened);
  servo1.write(servo1_closed);
  servo2.write(servo2_closed);
  servo3.write(servo3_closed);
}

void play_E(){
  Serial.println("E");
  servo0.write(servo0_opened);
  servo1.write(servo1_opened);
  servo2.write(servo2_closed);
  servo3.write(servo3_closed);

}
void play_F(){
  Serial.println("F");
  servo0.write(servo0_opened);
  servo1.write(servo1_opened);
  servo2.write(servo2_opened);
  servo3.write(servo3_closed);
}
void play_G(){
  Serial.println("G");
  servo0.write(servo0_opened);
  servo1.write(servo1_opened);
  servo2.write(servo2_opened);
  servo3.write(servo3_opened);
}

void play_note(int note){
  switch (note)
  {
      case 0:
        play_C();
        break;

      case 1:
        play_D();
        break;

      case 2:
        play_E();
        break;

      case 3:
        play_F();
        break;

      case 4:
        play_G();
        break;
  }
}


void setup() {
  Serial.begin(115200);
  servo0.attach(PIN_SERVO0);
  servo1.attach(PIN_SERVO1);
  servo2.attach(PIN_SERVO2);
  servo3.attach(PIN_SERVO3);
  note_counter = 0;
  note = 0;
  init_time = 0;
  wait_time = 0;
  sleeptime = (60.0/song_bpm) * 1000.0;

  Serial.println("start...");
  delay(2000);
}

void loop() {
  if (note_counter < number_of_notes){
    if ((millis() - init_time) >= wait_time){
      note = song[note_counter];
      play_note(note);
      wait_time = sleeptime*song_times[note_counter];
      Serial.print("wait_time: ");
      Serial.println(wait_time);
      init_time = millis();
      note_counter++;
    }
  }
}