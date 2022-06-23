#include <Arduino_FreeRTOS.h>
#pragma GCC optimize ("03")
#define Analog  A1  //Analog output of Light Sensor Module connected to A0 of BBFuino
#define LED_porch     13  //LED at D13 pin
#define sensor A0 // Assigning analog pin A0 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float vout;  //temporary variable to hold sensor reading
#define motor_fan 5
int AnalogValue = 0;  //to store analog value
#define LED_room 8
#define trigPin 6
#define echoPin 7


long duration;
int distance;

TaskHandle_t TaskHandle_1;
TaskHandle_t TaskHandle_2;
TaskHandle_t TaskHandle_3;
TaskHandle_t TaskHandle_4;
TaskHandle_t TaskHandle_5;
TaskHandle_t TaskHandle_6;

void setup()
{
  Serial.begin(9600);
  pinMode(motor_fan,OUTPUT); // for fan control by relay
  pinMode(sensor,INPUT); // temp varaiable to hold LDR reading
  pinMode(LED_porch, OUTPUT); //LED porch control by LDR
  pinMode(Analog, INPUT); // analog input for LDR sensor
  pinMode(trigPin, OUTPUT); // trigpin for ultrasonic
  pinMode(echoPin, INPUT); // echopin for ultrasonic
  pinMode(LED_room, OUTPUT); // as a room light
  digitalWrite(LED_porch, LOW);  //off LED 
  digitalWrite(motor_fan, LOW);
  delay(1000);
}


void loop()
{
  vout=analogRead(sensor);
  vout=(vout*500)/1023;
  tempc=vout; // Storing value in Degree Celsius
  if (tempc >= 20){
    //task 1 motor
    xTaskCreate(Fan_on, "Fan on", 100, NULL, 1, &TaskHandle_1);
    delay(2000);
  }
  else if (tempc <= 19){
    //motor off
    xTaskCreate(Fan_off, "Fan off", 100, NULL, 1, &TaskHandle_2);
    delay(2000);
  }
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;
  if (distance <= 500){
    // room light on
    xTaskCreate(room_on, "light on", 100, NULL, 2, &TaskHandle_3);
    delay(2000);
  }
  else if (distance >= 501){
    // room light off
    xTaskCreate(room_off, "light off", 100, NULL, 2, &TaskHandle_4);
    delay(2000);
  }
    AnalogValue = analogRead(Analog);
   if (analogRead(Analog) <= 1020){
    // porch light on
    xTaskCreate(porch_on, "porch on", 100, NULL, 3, &TaskHandle_5);
    delay(2000);
  }
  else if (analogRead(Analog) >= 1020){
    // porch light off
    xTaskCreate(porch_off, "porch off", 100, NULL, 3, &TaskHandle_6);
    delay(2000);
  }
  
}

/* task 1 */
static void Fan_on(void* pvParameters)
{
  while(1) // A Task shall never return or exit.
  {    
    digitalWrite(motor_fan, HIGH);
    vTaskDelete(TaskHandle_1);  //delete task after execution
    }
  }

 /* task with priority 2 */
static void Fan_off(void* pvParameters)
{
  while(1) // A Task shall never return or exit.
  {    
    digitalWrite(motor_fan, LOW);
    vTaskDelete(TaskHandle_2);  //delete task after execution
  }
  }

  /* task with priority 3 */
static void room_on (void* pvParameters)
{
  while(1)
  {    
     digitalWrite(LED_room, HIGH);
     vTaskDelete(NULL);
  }
}

/* task with priority 4 */
static void room_off (void* pvParameters)
{
  while(1)
  {    
    digitalWrite(LED_room,LOW);
    vTaskDelete(NULL);
  }
}

static void porch_on (void* pvParameters)
{
  while(1)
  {    
     digitalWrite(LED_porch, HIGH);
     vTaskDelete(NULL);
  }
}


/* task with priority 4 */
static void porch_off (void* pvParameters)
{
  while(1)
  {    
    digitalWrite(LED_porch,LOW);
    vTaskDelete(NULL);
  }
}
  





  
