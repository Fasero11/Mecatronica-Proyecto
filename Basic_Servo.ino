#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int counter = 0;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
    Serial.println(counter++);
    myservo.write(50);              // tell servo to go to position in variable 'pos'
    delay(3000); 
    myservo.write(110); 
    delay(3000);                      // waits 15ms for the servo to reach the position
}