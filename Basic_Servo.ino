#include <ESP32Servo.h>
#include <BluetoothSerial.h>


// ONLY WORKS IN C MAJOR.


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

int song1[] = {0,1,0,0,0,1,1,0,1};
int song2[] = {0,1,0,0,0,1,1,0,1};
int song3[] = {0,1,0,0,0,1,1,0,1};
int song4[] = {0,1,0,0,0,1,1,0,1};

int bpm = 60;

int sleeptime;
int note_counter;
int note;
int number_of_notes;
int bt_data;
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

      case 3:
        play_E();
        break;

      case 4:
        play_F();
        break;

      case 5:
        play_G();
        break;

      case 6:
        play_A();
        break;
        
      case 7:
        play_B();
        break;

      case 8:
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
  int note = song1[note_counter];
  number_of_notes = sizeof(song1) / sizeof(song1[0]);
  sleeptime = (60.0/bpm) * 1000;
  start = false;

  Serial.println(sleeptime);

  Serial.println("Starting...");
}

void loop() {
  
  if (start){
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

  if(SerialBT.available()){
    bt_data = SerialBT.read();
    Serial.println(bt_data);

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