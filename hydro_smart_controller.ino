#include <Servo.h>
Servo myservo;

int servoHome = 90;     
int servoWork = 0;   

#define light 7
#define exhaust 8
#define motionsensor 9
#define odourSensor A5
#define sensor_0 2
#define sensor_1 3
#define sensor_2 4
#define sensor_3 5
#define motor_0 A0
#define motor_1 A1
#define motor_2 A2
#define motor_3 A3
#define potentiometer A4
#define cleanbtn 12
#define odourbtn 11
#define servopin 10

int val_0 = 1;
int val_1 = 1;
int val_2 = 1;
int val_3 = 1;

int lastval_0 = 1;
int lastval_1 = 1;
int lastval_2 = 1;
int lastval_3 = 1;

unsigned long time_0;
unsigned long time_1;
unsigned long time_2;
unsigned long time_3;

bool active_0 = false;
bool active_1 = false;
bool active_2 = false;
bool active_3 = false;

int flash_time = 1000;
int odourValue = 0;




void setup() {
  myservo.attach(servopin);
myservo.write(servoHome);  
  pinMode(exhaust,OUTPUT);
  pinMode(light,OUTPUT);
  pinMode(motionsensor,INPUT);

  pinMode(cleanbtn, INPUT_PULLUP);
  pinMode(odourbtn, INPUT_PULLUP);
  pinMode(potentiometer, INPUT);
  pinMode(sensor_0, INPUT);
  pinMode(sensor_1, INPUT);
  pinMode(sensor_2, INPUT);
  pinMode(sensor_3, INPUT);
  pinMode(motor_0, OUTPUT);
  pinMode(motor_1, OUTPUT);
  pinMode(motor_2, OUTPUT);
  pinMode(motor_3, OUTPUT);
  digitalWrite(motor_0, 1);
  digitalWrite(motor_1, 1);
  digitalWrite(motor_2, 1);
  digitalWrite(motor_3, 1);
 flash_time = analogRead(potentiometer);
flash_time=map(flash_time,0,1023,1000,10000);


  Serial.begin(9600);
  
}

void loop() {
  if (digitalRead(odourbtn) == LOW) {
  myservo.write(servoWork);   
  delay(2000);              
  myservo.write(servoHome);   

  while (digitalRead(odourbtn) == LOW);
}

  if(digitalRead(cleanbtn)==0){digitalWrite(motor_0,0); digitalWrite(motor_1,0); digitalWrite(motor_2,0); digitalWrite(motor_3,0); delay(5000); digitalWrite(motor_0,1); digitalWrite(motor_1,1); digitalWrite(motor_2,1); digitalWrite(motor_3,1); }
  if(digitalRead(motionsensor)) {
    digitalWrite(light, 0); 
    digitalWrite(exhaust, 0); 
  }else {
     digitalWrite(light, 1); 
    digitalWrite(exhaust, 1); 
  }

odourValue = analogRead(odourSensor);

    val_0 = digitalRead(sensor_0);
  val_1 = digitalRead(sensor_1);
  val_2 = digitalRead(sensor_2);
  val_3 = digitalRead(sensor_3);


  if (val_0 == 1 && lastval_0 == 0) {
    digitalWrite(motor_0, 0);
    time_0 = millis();
    active_0 = true;
  }

  if (active_0) {
    if (millis() - time_0 >= flash_time) {
      digitalWrite(motor_0, 1);
      active_0 = false;
    }
  }
  ///////////////////////////////////////////////////////////////////////
  if (val_1 == 1 && lastval_1 == 0) {
    digitalWrite(motor_1, 0);
    time_1 = millis();
    active_1 = true;
  }

  if (active_1) {
    if (millis() - time_1 >= flash_time) {
      digitalWrite(motor_1, 1);
      active_1 = false;
    }
  }
/////////////////////////////////////////////////////////////////////////
  if (val_2 == 1 && lastval_2 == 0) {
    digitalWrite(motor_2, 0);
    time_2 = millis();
    active_2 = true;
  }

  if (active_2) {
    if (millis() - time_2 >= flash_time) {
      digitalWrite(motor_2, 1);
      active_2 = false;
    }
  }
  ///////////////////////////////////////////////////////////////////////
    if (val_3 == 1 && lastval_3 == 0) {
    digitalWrite(motor_3, 0);
    time_3 = millis();
    active_3 = true;
  }

  if (active_3) {
    if (millis() - time_3 >= flash_time) {
      digitalWrite(motor_3, 1);
      active_3 = false;
    }
  }
  ///////////////////////////////////////////////////////////////////////
  lastval_0 = val_0;
  lastval_1 = val_1;
  lastval_2 = val_2;
  lastval_3 = val_3;  
  printData();
}

void printData() {
  Serial.print("MOT:"); Serial.print(digitalRead(motionsensor));
  Serial.print(" | LGT:"); Serial.print(digitalRead(light));
  Serial.print(" | EXH:"); Serial.print(digitalRead(exhaust));
  
  Serial.print(" | SNS:");
  Serial.print(val_0); Serial.print(val_1); Serial.print(val_2); Serial.print(val_3);

  Serial.print(" | MTR:");
  Serial.print(digitalRead(motor_0)); Serial.print(digitalRead(motor_1)); 
  Serial.print(digitalRead(motor_2)); Serial.print(digitalRead(motor_3));

  Serial.print(" | FT:"); Serial.print(flash_time);
  Serial.print(" | OdrV:"); Serial.print(odourValue);
  Serial.print(" | Srv:"); Serial.println(myservo.read());
}


