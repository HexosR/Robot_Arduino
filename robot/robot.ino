//----------PREDEFINE-INPUTS-AND-OUTPUTS----------
#include <Servo.h>
//IR
#define IR_transmiter 3
#define IR_receiver 2

//Buttons
#define PBL 2
#define PBR 4

//Diodes
#define RED 13
#define GREEN 7
#define YELLOW 12

//----------PREDEFINE-VALUES----------

//Consts    
const int STOP_RIGHT = 80;              //80 and 89 this values are gonna stop the motors
const int STOP_LEFT = 89; 
const int something = 1;              //This value gonna help us to create a infinite loop

//Arrays
long middle_LDR[11];                //This array is needed to calculate an average of the middle LDR reading 
int barcode[4];                   //4 int's that gonna contain: 1 for short barcode or 2 for the wide one 

//Ints
int middle_Ave;                   //Contains average value of the LDR reading 
int IfBlack;
int WhichOneBarcode;
int numberOfTheBarcode;

//Servo
Servo RightServo;
Servo LeftServo;

//Longs
long time_before;
long time_after;

//----------FUNCTIONS-THAT-WILL-BE-USED-IN-CODE----------

//FUNCTIONS
void FORWARD_BARCODE() {              //Robot gonna go straight forward, slowlier than normaly because he's gonna read the barcodes
 digitalWrite(GREEN, LOW);
 digitalWrite(YELLOW, LOW);
 digitalWrite(RED, LOW);
 RightServo.write(72);
 LeftServo.write(97);
}

void FORWARD_OBSTACLE(int centimeters) {      //Robot gonna go straight forward faster
 digitalWrite(GREEN, LOW);
 digitalWrite(YELLOW, LOW);
 digitalWrite(RED, LOW);
 RightServo.write(18);     
 LeftServo.write(122);     
 delay(121 * centimeters);            //delay(121), was calculated from the circumference of a robot wheel and it responds to time that robot will travel a distance = 1cm
}

void LEFT() {                   //Robot turns left 90 degrees
 digitalWrite(GREEN, HIGH);
 digitalWrite(YELLOW, LOW);
 digitalWrite(RED, LOW);
 RightServo.write(STOP_RIGHT - 20);
 LeftServo.write(STOP_LEFT - 20);
 delay(1900);
 digitalWrite(GREEN, LOW);
}

void RIGHT() {                    //Robot turns right 90 degrees
 digitalWrite(GREEN, LOW);
 digitalWrite(YELLOW, HIGH);
 digitalWrite(RED, LOW);
 RightServo.write(STOP_RIGHT + 20);
 LeftServo.write(STOP_LEFT + 20);
 delay(1730);
 digitalWrite(YELLOW, LOW);
}

void UTURN(){                    //TURN 180 DEGREE
 digitalWrite(GREEN, HIGH);
 digitalWrite(YELLOW, HIGH);
 digitalWrite(RED, LOW);
 RightServo.write(STOP_RIGHT + 20);
 LeftServo.write(STOP_LEFT + 20);
 delay(6800);
 digitalWrite(GREEN, LOW);
 digitalWrite(YELLOW, LOW);
}

void STOP() {
 digitalWrite(GREEN, LOW);
 digitalWrite(YELLOW, LOW);
 digitalWrite(RED, HIGH);
 RightServo.write(STOP_RIGHT);
 LeftServo.write(STOP_LEFT);
}

void OBSTACLE(){               //When in fron of the robot will be some obstacle he will turn left go forward for 25cm and turn right
  tone(IR_transmiter, 38000);        //I was forced not to use the predefined functions to turn right and left because they use different LEDs
  delay(50);
  if (digitalRead(IR_receiver) == LOW) {
    delay(1500);
    if (digitalRead(IR_receiver) == LOW) {
    middle_LDR[10] = 0;
    IfBlack = 0;
    WhichOneBarcode = 0;
    numberOfTheBarcode = 0;
    digitalWrite(GREEN, HIGH);
    digitalWrite(YELLOW, HIGH);
    digitalWrite(RED, HIGH);
    RightServo.write(STOP_RIGHT + 20);
    LeftServo.write(STOP_LEFT + 20);
    delay(1730);
    FORWARD_OBSTACLE(25);
    RightServo.write(STOP_RIGHT - 20);
    LeftServo.write(STOP_LEFT - 20);
    delay(1900);
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(RED, LOW);
    noTone(IR_transmiter);
    }
  }
}

void WEETWEET(){ //this is just a function used in BOOGIE to se more clearly the code 
  LeftServo.write(STOP_LEFT - 40);
  RightServo.write(STOP_RIGHT - 40);
  delay(250);
  LeftServo.write(STOP_LEFT + 40);
  RightServo.write(STOP_RIGHT + 40);
  delay(250);
  LeftServo.write(STOP_LEFT - 40);
  RightServo.write(STOP_RIGHT - 40);
  delay(250);
  LeftServo.write(STOP_LEFT + 40);
  RightServo.write(STOP_RIGHT + 40);
  delay(250);
  LeftServo.write(STOP_LEFT - 40);
  RightServo.write(STOP_RIGHT - 40);
  delay(250);
  LeftServo.write(STOP_LEFT + 40);
  RightServo.write(STOP_RIGHT + 40);
  delay(250);
  LeftServo.write(STOP_LEFT - 40);
  RightServo.write(STOP_RIGHT - 40);
  delay(250);
  LeftServo.write(STOP_LEFT + 40);
  RightServo.write(STOP_RIGHT + 40);
  delay(250);
}

void BOOGIE(){  //LET'S DANCE
  RightServo.write(STOP_RIGHT + 40);
  delay(1000);
  RightServo.write(STOP_RIGHT - 40);
  delay(250);
  RightServo.write(STOP_RIGHT + 40);
  delay(250);
  RightServo.write(STOP_RIGHT - 40);
  delay(2000);
  RightServo.write(STOP_RIGHT);
  LeftServo.write(STOP_LEFT + 40);
  delay(2000);
  LeftServo.write(STOP_LEFT - 40);
  delay(250);
  LeftServo.write(STOP_LEFT + 40);
  delay(250);
  LeftServo.write(STOP_LEFT - 40);
  delay(1000);
  LeftServo.write(STOP_LEFT + 40);
  delay(1000);
  LeftServo.write(STOP_LEFT);
  FORWARD_OBSTACLE(5);
  delay(500);
  WEETWEET();
  LeftServo.write(STOP_LEFT - 40);
  RightServo.write(STOP_RIGHT + 40);
  delay(500);
  LeftServo.write(STOP_LEFT - 40);
  RightServo.write(STOP_RIGHT);
  delay(1000);
  RightServo.write(STOP_RIGHT - 40);
  LeftServo.write(STOP_LEFT);
  delay(1000);
  FORWARD_OBSTACLE(5);
  delay(500);
  WEETWEET();
  LeftServo.write(STOP_LEFT - 40);
  RightServo.write(STOP_RIGHT + 40);
  delay(500);
  RightServo.write(STOP_RIGHT + 40);
  LeftServo.write(STOP_LEFT);
  delay(1000);
  WEETWEET();
}

int CALIBRATE_LDR() {               //THIS IS THE MOST IMPORTANT FUNCTION WHICH READS THE BARCODES  
  for (int i = 0; i <= 9; i++) {          //after checking the obstacle, he reads the LDR, 10 times
    middle_LDR[i] = analogRead(A1);
    middle_LDR[10] += middle_LDR[i];
  }
  middle_Ave = middle_LDR[10] / 10;       //then calculates the average 
  Serial.println(middle_Ave);
  if ((middle_Ave <= 400) && (IfBlack == 0)) {  //waits for the robot to come to black spot
    IfBlack = 1;                //the second checked value is just a helper that will not allow robot to do things before he will step on the black one
    time_before = millis();
  }
  if ((middle_Ave >= 400) && (IfBlack == 1)) {  //calculates the time it took the robot to pass the one black stripe 
    time_after = millis() - time_before;
    IfBlack = 0;
    WhichOneBarcode++;              //adds one to knov which stripe he is reading at the moment 
    if (time_after >= 900) {         //I've calculated that with this speed, wide stripe have 2 seconds and the other one 1 second
      Serial.println("2");    
      Serial.println(time_after);
      barcode[numberOfTheBarcode++] = 2;
    }
    else {
      Serial.println("1");
      Serial.println(time_after);
      barcode[numberOfTheBarcode++] = 1;
    }
  }
  while (WhichOneBarcode == 4) {          //After four readings he will check which barcode he detected 
    WhichOneBarcode = 0;
    numberOfTheBarcode = 0;
    if (barcode[0] == 2 && barcode[1] == 2 && barcode[2] == 1 && barcode[3] == 1) {
      LEFT();
      }
    else if (barcode[0] == 1 && barcode[1] == 2 && barcode[2] == 1 && barcode[3] == 2) {  
      RIGHT();
    }
    else if (barcode[0] == 1 && barcode[1] == 1 && barcode[2] == 2 && barcode[3] == 1) {
      UTURN();
    }
    else if (barcode[0] == 1 && barcode[1] == 2 && barcode[2] == 2 && barcode[3] == 1) {
      STOP(); 
      while (something == 1) {
      }
    }
    else if (barcode[0] == 2 && barcode[1] == 1 && barcode[2] == 1 && barcode[3] == 2) {
      BOOGIE();
    }
  }
  middle_LDR[10] = 0;
  delay(200);
}

void setup() {
  Serial.begin(9600);
  RightServo.attach(5);
  LeftServo.attach(6);
  pinMode(A1, INPUT);
  pinMode(PBL, INPUT);
  pinMode(GREEN, OUTPUT);  
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  //pinMode(IR_transmiter, OUTPUT);
  //pinMode(IR_receiver, INPUT);
}

void loop() {
    FORWARD_BARCODE();
    OBSTACLE();
    CALIBRATE_LDR();
  }
 
