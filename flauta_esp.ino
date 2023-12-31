#include <ESP32Servo.h>
#include <BluetoothSerial.h>


// ONLY WORKS IN C MAJOR.
// ONLY PLAYS QUARTER NOTES.

#define PIN_SERVO0 23
#define PIN_SERVO1 22
#define PIN_SERVO2 21
#define PIN_SERVO3 19
#define PIN_SERVO4 18
#define PIN_SERVO5 17
#define PIN_SERVO6 16
#define PIN_SERVO7 2
#define PIN_SERVO8 15

#define C 0
#define D 1
#define E 2
#define F 3
#define G 4
#define A 5
#define B 6
#define C2 7

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;

int servo0_closed = 110;
int servo0_opened = 90;
int servo1_closed = 110;
int servo1_opened = 90;
int servo2_closed = 110;
int servo2_opened = 90;
int servo3_closed = 110;
int servo3_opened = 90;
int servo4_closed = 110;
int servo4_opened = 90;
int servo5_closed = 110;
int servo5_opened = 90;
int servo6_closed = 110;
int servo6_opened = 90;
int servo7_closed = 110;
int servo7_opened = 90;
int servo8_closed = 110;
int servo8_opened = 90;


BluetoothSerial SerialBT;

int song1[] = {E,E,F,G,G,F,E,D,C,C,D,E,E,D,D,E,E,F,G,G,F,E,D,C,C,D,E,D,C,C}; // Ode to Joy (C major)
int song1_times[] = {1,1,1,1,1,1,1,1,1,1,1,1,1.5,0.5,2,1,1,1,1,1,1,1,1,1,1,1,1,1.5,0.5,2};
int song1_bpm = 120;

int song2[] = {E,E,E,C,G,E,C,G,E}; // The imperial march
int song2_times[] = {1,1,1,0.75,0.25,1,1.5,0.25,2};
int song2_bpm = 60;

int song3[] = {C,C,C,C,C,C};
int song4[] = {C,C,C,C,C,C};


int sleeptime, wait_time, init_time, note_counter, note, number_of_notes, bt_data, bpm;
bool start;

void play_C(){
  servo0.write(servo0_closed);
  servo1.write(servo1_closed);
  servo2.write(servo2_closed);
  servo3.write(servo3_closed);
  servo4.write(servo4_closed);
  servo5.write(servo5_closed);
  servo6.write(servo6_closed);
  servo7.write(servo7_closed);
  servo8.write(servo8_closed);

}

void play_D(){
  servo0.write(servo0_opened);
  servo1.write(servo1_closed);
  servo2.write(servo2_closed);
  servo3.write(servo3_closed);
  servo4.write(servo4_closed);
  servo5.write(servo5_closed);
  servo6.write(servo6_closed);
  servo7.write(servo7_closed);
  servo8.write(servo8_closed);
}

void play_E(){
  servo0.write(servo0_opened);
  servo1.write(servo1_opened);
  servo2.write(servo2_closed);
  servo3.write(servo3_closed);
  servo4.write(servo4_closed);
  servo5.write(servo5_closed);
  servo6.write(servo6_closed);
  servo7.write(servo7_closed);
  servo8.write(servo8_closed);
}
void play_F(){
  servo0.write(servo0_opened);
  servo1.write(servo1_opened);
  servo2.write(servo2_opened);
  servo3.write(servo3_closed);
  servo4.write(servo4_closed);
  servo5.write(servo5_closed);
  servo6.write(servo6_closed);
  servo7.write(servo7_closed);
  servo8.write(servo8_closed); 
}
void play_G(){
  servo0.write(servo0_opened);
  servo1.write(servo1_opened);
  servo2.write(servo2_opened);
  servo3.write(servo3_opened);
  servo4.write(servo4_closed);
  servo5.write(servo5_closed);
  servo6.write(servo6_closed);
  servo7.write(servo7_closed);
  servo8.write(servo8_closed);  
}
void play_A(){
  servo0.write(servo0_opened);
  servo1.write(servo1_opened);
  servo2.write(servo2_opened);
  servo3.write(servo3_opened);
  servo4.write(servo4_opened);
  servo5.write(servo5_closed);
  servo6.write(servo6_closed);
  servo7.write(servo7_closed);
  servo8.write(servo8_closed); 
}
void play_B(){
  servo0.write(servo0_opened);
  servo1.write(servo1_opened);
  servo2.write(servo2_opened);
  servo3.write(servo3_opened);
  servo4.write(servo4_opened);
  servo5.write(servo5_opened);
  servo6.write(servo6_closed);
  servo7.write(servo7_closed);
  servo8.write(servo8_closed);   
}

void play_C2(){
  servo0.write(servo0_opened);
  servo1.write(servo1_opened);
  servo2.write(servo2_opened);
  servo3.write(servo3_opened);
  servo4.write(servo4_opened);
  servo5.write(servo5_opened);
  servo6.write(servo6_opened);
  servo7.write(servo7_closed);
  servo8.write(servo8_closed);   
}

void set_servos(int note){
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

      case 5:
        play_A();
        break;
        
      case 6:
        play_B();
        break;

      case 7:
        play_C2();
        break;
  }
}

void reset(){
  note_counter = 0;
  int note = song1[note_counter];
}

void setup() {
  Serial.begin(115200);

  servo0.attach(PIN_SERVO0);
  servo1.attach(PIN_SERVO1);
  servo2.attach(PIN_SERVO2);
  servo3.attach(PIN_SERVO3);
  servo4.attach(PIN_SERVO4);
  servo5.attach(PIN_SERVO5);
  servo6.attach(PIN_SERVO6);
  servo7.attach(PIN_SERVO7);
  servo8.attach(PIN_SERVO8);

  SerialBT.begin("Virtuoso");

  note_counter = 0;
  number_of_notes = sizeof(song1) / sizeof(song1[0]);
  int number_of_times = sizeof(song1_times) / sizeof(song1_times[0]);

  if (number_of_notes != number_of_times){
    Serial.println("ERROR. Sizes of notes and durations arrays don't match");
    delay(100000);
  }

  wait_time = 0;
  init_time = 0;

  bpm = song1_bpm;
  sleeptime = (60.0/bpm) * 1000.0;

  start = false;

  Serial.print("sleeptime: ");
  Serial.println(sleeptime);

  Serial.println("Starting...");
}

void loop() {

  if (start){
    if (note_counter < number_of_notes){
      if ((millis() - init_time) >= wait_time){
        note = song1[note_counter];
        set_servos(note);
        Serial.print("Note: ");
        Serial.println(note);
        wait_time = sleeptime*song1_times[note_counter];
        init_time = millis();
        note_counter++;
      }
    }
    
    else {
      Serial.println("END");
      delay(1000);
    }
  }

  if(SerialBT.available()){
    bt_data = SerialBT.read();
    //Serial.println(bt_data);

    if (bt_data == 49){
      //RESET
      Serial.println("RESET");
      reset();
    }
    if (bt_data == 50){
      // START
      Serial.println("START");
      start = true;
    }
    if (bt_data == 51){
      // STOP
      Serial.println("STOP");
      start = false;
    }
  }
}