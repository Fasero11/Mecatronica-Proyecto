#include <ESP32Servo.h>
#include <BluetoothSerial.h>

#define PIN_SERVO0 23
#define PIN_SERVO1 22
#define PIN_SERVO2 21
#define PIN_SERVO3 19
#define PIN_SERVO4 18
#define PIN_SERVO5 17
#define PIN_SERVO6 16
#define PIN_SERVO7 2
#define PIN_SERVO8 15

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;

BluetoothSerial SerialBT;

int song1[] = {0,1,0,0,0,1,1,0,1};
int song2[] = {0,1,0,0,0,1,1,0,1};
int song3[] = {0,1,0,0,0,1,1,0,1};
int song4[] = {0,1,0,0,0,1,1,0,1};

int bpm = 60;

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


int sleeptime;
int note_counter = 0;
int note;
int number_of_notes;

void play_C(){
  servo0.write(servo0_closed);
  servo1.write(servo1_opened);
  servo2.write(servo2_opened);
  servo3.write(servo3_opened);
  servo4.write(servo4_opened);
  servo5.write(servo5_opened);
  servo6.write(servo6_opened);
  servo7.write(servo7_opened);
  servo8.write(servo8_opened);
}

void play_D(){
  servo0.write(servo0_closed);
  servo1.write(servo1_closed);
  servo2.write(servo2_opened);
  servo3.write(servo3_opened);
  servo4.write(servo4_opened);
  servo5.write(servo5_opened);
  servo6.write(servo6_opened);
  servo7.write(servo7_opened);
  servo8.write(servo8_opened);  
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
  }
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

  Serial.begin(9600);
  SerialBT.begin("Virtuoso");

  int note = song1[note_counter];
  number_of_notes = sizeof(song1) / sizeof(song1[0]);
  sleeptime = (60.0/bpm) * 1000;
  Serial.println(sleeptime);
}

void loop() {
  if (note_counter < number_of_notes){
    set_servos(note);
    Serial.println(note);
    note = song1[++note_counter];
    delay(sleeptime);
  }
  
  else {
    Serial.println("END");
  }

}