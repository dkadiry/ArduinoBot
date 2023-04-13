//The Following Code is the source code for controlling the Line Following Robot

//Initial variable decleration

// Bluetooth Variables
int relayPin = 6; //Setting a digital pin for the Bluetooth sensor
int state = 0; 
int flag = 0; //Setting initial state and flag of the sensor to 0

// IR Variables
int LED = A4;
int LEDr= A5;//Setting the analog pins A4 and A5 to variables LED (for the LED on the left) and LEDr (for the LED on the right)
int LeftObstaclePin = 2;  // This is the input pin for sensor on the left
int RightObstaclePin = 3; // This is the input pin for sensor on the right
int Left;// HIGH MEANS BLACK/NO COLOUR/NO INFRARED SIGNAL DETECTED
int Right; //Setting variables "Left" and "Right"  

//Ultrasonic Sensor Variables
const int trigPin = 4;
const int echoPin = 5; //Setting variables "trigPin" and "echoPin" to 4 and 5; these are the pin numbers that will be used to send and recieve signals from and to ultrasonic sensor
long duration;
int distance;// "duration" and "distance" are the variables used to calculate and display the distance between the sensor and the closest obstacle

//H-Bridge Variables
const int IN1 = 8;
const int IN2 = 9;
const int IN3 = 12;
const int IN4 = 13;//Assigning pin numbers to all the H-Bridge connections for controlling the motor direction
const int ENA = 10;
const int ENB = 11;//Assigning pin numbers to the H-Bridge enable pins which control the speed of the motors
int currentspeedA = 230;
int currentspeedB = 230;//Initiating the start speed to 0
 
void setup() {
  // Bluetooth Setup
 pinMode(relayPin, OUTPUT);//Setting the relayPin as an output
 digitalWrite(relayPin, LOW);//Setting the output of the bluetooth as Low initially

 
// IR SETUP
  pinMode(LED, OUTPUT);
  pinMode(LeftObstaclePin, INPUT);
  pinMode(RightObstaclePin, INPUT);
  pinMode(LEDr, OUTPUT);//Setting the pins as inputs and outputs depending on how we use them

  
 //Ultrasonic SETUP
 pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

//Bridge Setup
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);//Setting all H-Bridge pins as outputs as required


  //NEW
   int Left1 = digitalRead(LeftObstaclePin);
  int Right1 = digitalRead(RightObstaclePin);

  
Serial.begin(9600);
}
 
void loop() {

//Ultrasonic LOOP

// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
//Sets trigPin back to Low
digitalWrite(trigPin, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);
// Calculating the distance
distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);//printing distance
delay(200);
  
  
// Bluetooth LOOP
 if(Serial.available() > 0){
 state = Serial.read();//takes an input from phone
 flag=0;
 }

 if (state == 'z') {//if input from phone is "0" then bluetooth output is "0" meaning relay isn't activated and motors don't start
 digitalWrite(relayPin, LOW);//sending a Low output
 if(flag == 0){
 Serial.println("Motors: off");
 flag = 1;
 }
 }

 else if (state == 'Z') {//if input from phone is "1" then bluetooth output is "1" meaning relay is activated and motors start
 digitalWrite(relayPin, HIGH);//sending a HIGH output
 if(flag == 0){
 Serial.println("Motors: on");
 flag = 1;
 }
 }





 if ((((digitalRead(LeftObstaclePin))==1)&&((digitalRead(RightObstaclePin))==1))||(distance<40))
  {
    Serial.println("Stop");    
       analogWrite(ENA, 0);
       analogWrite(ENB, 0);

      
      digitalWrite(LED, HIGH);
      digitalWrite(LEDr, HIGH);
      delay(200);
      digitalWrite(LED, LOW);
      digitalWrite(LEDr,LOW);
      delay (200); 
       
  }
  else
  {
     // IR SENSOR LOOP
 //digitalRead(LeftObstaclePin);
 //digitalRead(RightObstaclePin);//reading the input signals from the left and right IR sensors
  
  if (((digitalRead(LeftObstaclePin))==1)&&((digitalRead(RightObstaclePin))==0))//this line of code is saying: when Left sensor detects the line while right sensor does not, do the following
  {
    Serial.println("Left Turn!!!");//make a left turn
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(1000);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);//keeping the H-Bridge pins active so the motors keep moving
      analogWrite(ENB, 0);//keeping the motors on the right at constant speed
      analogWrite(ENA, 90);
  //analogWrite(ENA, 0);
     
      digitalWrite(LED, HIGH);
      delay(200);
      digitalWrite(LED, LOW);
      delay (200); //making the LED on the left side blink to indicate left turn
      
      delay(10);
  }
  
  else
  {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 90);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 90);
  digitalWrite(LED, LOW);//In the case that the "if" statemnt isn't met, then keep LEDs Low while leaving the H-Bridge untouched
  Serial.println("Forward!!!");
  }

  
  if (((digitalRead(LeftObstaclePin))==0)&&((digitalRead(RightObstaclePin))==1))//this line of code is saying: when Left sensor detects the line while right sensor does not, do the following
  {
    Serial.println("Right Turn!!!");//make a left turn
   analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  delay(100);
    digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);//keeping the H-Bridge pins active so the motors keep moving
      analogWrite(ENA, 90);//keeping the motors on the right at constant speed
;//keeping the H-Bridge pins active so the motors keep moving
      analogWrite(ENB, 0);
     
      digitalWrite(LEDr, HIGH);
      delay(200);
      digitalWrite(LEDr, LOW);
      delay (200); //making the LED on the left side blink to indicate left turn
      
     delay(10);
  }
  
  else
  {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 90);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 90);
  digitalWrite(LED, LOW);//In the case that the "if" statemnt isn't met, then keep LEDs Low while leaving the H-Bridge untouched
  }

  }





}
