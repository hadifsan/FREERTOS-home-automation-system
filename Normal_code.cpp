#define Analog  A1  //Analog output of Light Sensor Module connected to A0 of BBFuino
#define Digital 2   //Digital Output of Light Sensor Module connected to D2 of BBfuino
#define LED_porch     13  //LED at D13 pin
const int sensor=A0; // Assigning analog pin A0 to variable 'sensor'
float tempc;  //variable to store temperature in degree Celsius
float vout;  //temporary variable to hold sensor reading
int motor_fan = 5;
int AnalogValue = 0;  //to store analog value
const int LED_room =  8;
const int trigPin = 6;
const int echoPin = 7;

long duration;
int distance;

void setup() {
  // put your setup code here, to run once:
pinMode(sensor,INPUT);
pinMode(motor_fan,OUTPUT);
Serial.begin(9600);
pinMode(LED_porch, OUTPUT);
pinMode(Analog, INPUT);
digitalWrite(LED_porch, LOW);  //off LED 
pinMode(LED_room, OUTPUT);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
AnalogValue = analogRead(Analog); //read LDR sensor value
Serial.println(AnalogValue); //display LDR sensor value
vout=analogRead(sensor);
vout=(vout*500)/1023;
tempc=vout; // Storing value in Degree Celsius
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin,LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034/2;

  Serial.println("Distance: ");
  Serial.println(distance);

  if(tempc >= 20){
    digitalWrite(motor_fan, HIGH);
}
  else {
    digitalWrite(motor_fan, LOW);
  }
  if (analogRead(Analog) <= 1020) {
    digitalWrite(LED_porch, HIGH);
  }
  else {
    digitalWrite(LED_porch, LOW);
  }
  
  if( distance <= 500  && distance > 400){
    digitalWrite(LED_room, HIGH);
    
    Serial.println("Distance: ");
    Serial.println(distance);
  }
  else {
    digitalWrite(LED_room,LOW);
    
  Serial.println("Distance: ");
  Serial.println(distance);
  }
}
