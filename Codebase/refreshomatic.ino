/*************************************************/
/* Name of the program: Refresh-o-Matic          */
/* Author: Volodymyr Semenov, Vasilisa Ignatova  */
/* Program file name: refreshomatic.ino          */
/* Run using: Arduino IDE                        */
/* Date: 11/11/2023                              */
/*************************************************/

#include "ArduinoQueue.h"
#include "HX711.h"
#include <AccelStepper.h>
#include "set.h"
#include "Arduino_LED_Matrix.h"
#include "animation.h"

#define EMERGENCY_STOP_PIN 2
#define PUMP_PIN 12
#define STEPPER_ENABLE_PIN 13

#define STEP_PIN 8
#define DIR_PIN 9
#define MAX_SPEED 200

#define LOADCELL1_DOUT_PIN 10
#define LOADCELL1_SCK_PIN 11
#define LOADCELL1_SCALE 829.025

#define LOADCELL2_DOUT_PIN 4
#define LOADCELL2_SCK_PIN 5
#define LOADCELL2_SCALE 764.771

#define LOADCELL3_DOUT_PIN 6
#define LOADCELL3_SCK_PIN 7
#define LOADCELL3_SCALE 757.016

// NO CUP AREA
#define NO_CUP_WEIGHT 0.3
// CUP NOT FILLED AREA
#define EMPTY_CUP_WEIGHT 10
// FILLING UP CUP AREA
#define FULL_CUP_WEIGHT 210
// DANGER ZONE

struct sensor { 
  HX711 loadcell;
  int id;
  int position_;
};

sensor sensor1;
sensor sensor2;
sensor sensor3;
HX711 sen1;
HX711 sen2;
HX711 sen3;

// create a queue of string
ArduinoQueue<sensor> sensor_queue(3);
Set queue_set;

AccelStepper stepper(1, STEP_PIN, DIR_PIN); // Mode Step Dirr

ArduinoLEDMatrix matrix;
  
void setup() {
  pinMode(EMERGENCY_STOP_PIN, INPUT);
  attachInterrupt(EMERGENCY_STOP_PIN, EMERGENCY_STOP, CHANGE);

  pinMode(PUMP_PIN, OUTPUT);
  pinMode(STEPPER_ENABLE_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(STEPPER_ENABLE_PIN , LOW);

  // Serial.begin(9600);

  stepper.setAcceleration(100);
  stepper.setCurrentPosition(0);
  stepper.setMaxSpeed(MAX_SPEED);

  sen1.begin(LOADCELL1_DOUT_PIN, LOADCELL1_SCK_PIN);
  sen1.set_scale(LOADCELL1_SCALE);
  sen1.tare();

  sen2.begin(LOADCELL2_DOUT_PIN, LOADCELL2_SCK_PIN);
  sen2.set_scale(LOADCELL2_SCALE);
  sen2.tare();

  sen3.begin(LOADCELL3_DOUT_PIN, LOADCELL3_SCK_PIN);
  sen3.set_scale(LOADCELL3_SCALE);
  sen3.tare();

  sensor1.loadcell = sen1;
  sensor1.id = 1;
  sensor1.position_ = 260;

  sensor2.loadcell = sen2;
  sensor2.id = 2;
  sensor2.position_ = 0;

  sensor3.loadcell = sen3;
  sensor3.id = 3;
  sensor3.position_ = -260;


  matrix.begin();
  matrix.loadSequence(animation);
  matrix.autoscroll(300);
  matrix.play(true);
}

void loop() {
  check_sensor(sensor1);
  check_sensor(sensor2);
  check_sensor(sensor3);
  if (!sensor_queue.isEmpty()) {
    sensor head = sensor_queue.getHead();
    // Serial.println(head.id);
    bool Move = true;
    for(int i=0; i<5 ;i++){
      int sensor_value = head.loadcell.get_units(1);
      if(sensor_value < NO_CUP_WEIGHT || sensor_value > FULL_CUP_WEIGHT){
        Move = false;
      }
    }
    if(Move){
      move_to(head);
      fill(head);
    } else {
      sensor_queue.dequeue();
      queue_set.sub(head.id);
    }
  }
}

void move_to(sensor sensor_used){
  stepper.moveTo(sensor_used.position_);
  stepper.runToPosition(); // Blocking
}

void fill(sensor sensor_used ){
  digitalWrite(PUMP_PIN, HIGH);
  digitalWrite(STEPPER_ENABLE_PIN, HIGH);
  long sensor_read = sensor_used.loadcell.get_units(1);
  while(sensor_read > NO_CUP_WEIGHT && sensor_read < FULL_CUP_WEIGHT){
    check_sensor(sensor1);
    check_sensor(sensor2);
    check_sensor(sensor3);
    sensor_read = sensor_used.loadcell.get_units(1);
  }
  digitalWrite(STEPPER_ENABLE_PIN, LOW);
  digitalWrite(PUMP_PIN, LOW);
  sensor_queue.dequeue();
  queue_set.sub(sensor_used.id);
}

void check_sensor(sensor Sensor) {
  int sensor_value = Sensor.loadcell.get_units(1);
  if(sensor_value > NO_CUP_WEIGHT && sensor_value < FULL_CUP_WEIGHT){
    if(!queue_set.has(Sensor.id)){
      sensor_queue.enqueue(Sensor);
      queue_set.add(Sensor.id);
    }
  }
}

void EMERGENCY_STOP(void){
  digitalWrite(PUMP_PIN, LOW);
  digitalWrite(STEPPER_ENABLE_PIN, HIGH);
  while(1){}
}
