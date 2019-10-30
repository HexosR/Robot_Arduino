/*
    Name:       rom57_Robotisc_Group.ino
    Author:     Robert Mlynarczyk
*/

//----------PREDEFINE-INPUTS-AND-OUTPUTS----------
//IR
#define IR_transmitter 3													// I havent define inputs for buttons because I'm not using them
#define IR_receiver 2

//Diodes
#define RED 13
#define GREEN 7
#define YELLOW 12

//Servos
#define RIGHT_MOTOR 5
#define	LEFT_MOTOR 6 

//----------PREDEFINE-VALUES----------

//Consts    
const int STOP_RIGHT = 80;											    //80 and 89 this values are gonna stop the motors
const int STOP_LEFT = 89;
const int something = 1;												//This value gonna help us to create a infinite loop for STOP function
const int LDR_light_border = 400;										//Below this value, LDR will read a black stripe
const int Speed_Barcode_Right = 72;										//This four values are for setting the speed of the servos for reading the barcode (slower) and for driving faster
const int Speed_Barcode_Left = 97;	
const int Speed_Right = 18;
const int Speed_Left = 122;
const int Time_Border = 1000;											//This time responds as a limit value for the wide and thin stipe (above = wide ; below = thin)

//Arrays
long middle_LDR[11];													//This array is needed to calculate an average of the middle LDR reading 
int barcode[4];														    //4 int's that gonna contain: 1 for short barcode or 2 for the wide one 
int BAR_Right[4] = { 1,2,1,2 };											//I have made 5 arrays to order the barcodes 
int BAR_Left[4] = { 2,2,1,1 };
int BAR_Uturn[4] = { 1,1,2,1 };
int BAR_Stop[4] = { 1,2,2,1 };
int BAR_Dance[4] = { 2,1,1,2 };

//Longs
long time_before;														//Time in which the robot drove to the beginning of the black stripe
long time_after;														//Time in which robot is receiving low values on the LDR (time after passing black stripe)

//Ints
int check;																//This value will check if robot started reading a barcode, if so will not allow to detect obstacle
int middle_Ave;															//Contains average value of the LDR reading 
int IfBlack;															//This value help us with definiig in which clour stripe is our robot 
int WhichOneBarcode;													//Value that counts barcodes max = 4 
int numberOfTheBarcode;													//Adds the number of barcode array 

//----------VALUES-FOR-SERVOS--------
#include <Servo.h>

//Servo
Servo RightServo;
Servo LeftServo;

//----------FUNCTIONS-THAT-WILL-BE-USED-IN-CODE----------

//FUNCTIONS	
void FORWARD_BARCODE() {											    //Robot gonna go straight forward, slowlier than normaly because he's gonna read the barcodes
	digitalWrite(GREEN, LOW);
	digitalWrite(YELLOW, LOW);
	digitalWrite(RED, LOW);
	RightServo.write(Speed_Barcode_Right);
	LeftServo.write(Speed_Barcode_Left);
}

void FORWARD_OBSTACLE(int centimeters) {							    //Robot gonna go straight forward faster
	RightServo.write(Speed_Right);
	LeftServo.write(Speed_Left);										//delay(121), was calculated from the circumference of a robot wheel and it responds to time that robot will travel a distance = 1cm
	delay(121 * centimeters);										    //changing the int centimeters will change the lenght of the path that robot will pass
}
	
void LEFT(int left_degrees) {											//Robot turns left 90 degrees
	digitalWrite(GREEN, HIGH);
	digitalWrite(YELLOW, LOW);
	digitalWrite(RED, LOW);
	RightServo.write(STOP_RIGHT - 20);
	LeftServo.write(STOP_LEFT - 20);
	delay(24 * left_degrees);											//delay calculated by dividing delay for 90 degrees
	digitalWrite(GREEN, LOW);
}
	
void RIGHT(int right_degrees) {											//Robot turns right 90 degrees
	digitalWrite(GREEN, LOW);
	digitalWrite(YELLOW, HIGH);
	digitalWrite(RED, LOW);
	RightServo.write(STOP_RIGHT + 20);
	LeftServo.write(STOP_LEFT + 20);
	delay(23 * right_degrees);											//delay calculated by dividing delay for 90 degrees
	digitalWrite(YELLOW, LOW);
}

void UTURN() {														    //Robot turns right 180 degrees I'have created another function for the other LED's set
	digitalWrite(GREEN, HIGH);
	digitalWrite(YELLOW, HIGH);
	digitalWrite(RED, LOW);
	RightServo.write(STOP_RIGHT + 20);
	LeftServo.write(STOP_LEFT + 20);
	delay(23 * 180);
	digitalWrite(GREEN, LOW);
	digitalWrite(YELLOW, LOW);
}

void STOP() {															//Robot stops
	digitalWrite(GREEN, LOW);											//This function need a delay or loop to hold robot in stop position 
	digitalWrite(YELLOW, LOW);
	digitalWrite(RED, HIGH);
	RightServo.write(STOP_RIGHT);
	LeftServo.write(STOP_LEFT);
}

void OBSTACLE() {														//When in fron of the robot will be some obstacle he will turn left 90 degrees, go forward 25cm and turn right 90 degrees
	if (check == 0) {
		tone(IR_transmitter, 38000);										//I was forced not to use the predefined functions to turn right and left because they use different LEDs
		delay(50);
		if (digitalRead(IR_receiver) == LOW) {							//When I'm starting the program, the first thing that my robot is doing is detecting an obstacle even when there is no obstacle in fornt of him 
			delay(250);													//So I have added this nested if's to slow down the process, it works properly with this delay
			if (digitalRead(IR_receiver) == LOW) {
				digitalWrite(GREEN, HIGH);
				digitalWrite(YELLOW, HIGH);
				digitalWrite(RED, HIGH);
				RightServo.write(STOP_RIGHT + 20);						//Robot turns right 90 degrees
				LeftServo.write(STOP_LEFT + 20);
				delay(23 * 90);
				FORWARD_OBSTACLE(25);
				RightServo.write(STOP_RIGHT - 20);						//Robot turns left 90 degrees
				LeftServo.write(STOP_LEFT - 20);
				delay(24 * 90);
				digitalWrite(GREEN, LOW);
				digitalWrite(YELLOW, LOW);
				digitalWrite(RED, LOW);
				noTone(IR_transmitter);
			}
		}
	}
}

void BOOGIE() {															//LET'S DANCE - I'm gonna describe it in documentation
	digitalWrite(GREEN, HIGH);
	RightServo.write(STOP_RIGHT + 40);
	delay(1000);
	digitalWrite(YELLOW, HIGH);
	RightServo.write(STOP_RIGHT - 40);
	delay(250);
	digitalWrite(RED, HIGH);
	RightServo.write(STOP_RIGHT + 40);
	delay(250);
	digitalWrite(RED, LOW);
	RightServo.write(STOP_RIGHT - 40);
	delay(2000);
	digitalWrite(YELLOW, LOW);
	RightServo.write(STOP_RIGHT);
	LeftServo.write(STOP_LEFT + 40);
	delay(2000);
	digitalWrite(GREEN, LOW);
	LeftServo.write(STOP_LEFT - 40);
	delay(250);
	digitalWrite(GREEN, HIGH);
	digitalWrite(YELLOW, HIGH);
	LeftServo.write(STOP_LEFT + 40);
	delay(250);
	digitalWrite(YELLOW, LOW);
	digitalWrite(RED, HIGH);
	LeftServo.write(STOP_LEFT - 40);
	delay(1000);
	digitalWrite(YELLOW, HIGH);
	digitalWrite(RED, LOW);
	digitalWrite(GREEN, LOW);
	LeftServo.write(STOP_LEFT + 40);
	delay(1000);
	digitalWrite(YELLOW, LOW);
	digitalWrite(RED, HIGH);
	digitalWrite(GREEN, HIGH);
	LeftServo.write(STOP_LEFT);
	FORWARD_OBSTACLE(5);
	delay(500);
	digitalWrite(YELLOW, HIGH);
	WEETWEET();
	LeftServo.write(STOP_LEFT - 40);
	RightServo.write(STOP_RIGHT + 40);
	delay(500);
	digitalWrite(GREEN, LOW);
	digitalWrite(YELLOW, HIGH);
	LeftServo.write(STOP_LEFT - 40);
	RightServo.write(STOP_RIGHT);
	delay(1000);
	digitalWrite(RED, HIGH);
	digitalWrite(YELLOW, LOW);
	digitalWrite(GREEN, HIGH);
	RightServo.write(STOP_RIGHT - 40);
	LeftServo.write(STOP_LEFT);
	delay(1000);
	digitalWrite(YELLOW, LOW);
	digitalWrite(RED, HIGH);
	digitalWrite(GREEN, HIGH);
	FORWARD_OBSTACLE(5);
	delay(500);
	WEETWEET();
	LeftServo.write(STOP_LEFT - 40);
	RightServo.write(STOP_RIGHT + 40);
	delay(500);
	digitalWrite(YELLOW, HIGH);
	digitalWrite(RED, HIGH);
	digitalWrite(GREEN, LOW);
	RightServo.write(STOP_RIGHT + 40);
	LeftServo.write(STOP_LEFT);
	delay(2000);
	digitalWrite(YELLOW, LOW);
	digitalWrite(RED, LOW);
	WEETWEET();
}

void WEETWEET() {														//this is just a function used in BOOGIE to see more clearly the code 
	LeftServo.write(STOP_LEFT - 40);
	RightServo.write(STOP_RIGHT - 40);
	delay(250);
	digitalWrite(YELLOW, LOW);
	digitalWrite(GREEN, HIGH);
	LeftServo.write(STOP_LEFT + 40);
	RightServo.write(STOP_RIGHT + 40);
	delay(250);
	digitalWrite(YELLOW, HIGH);
	digitalWrite(GREEN, LOW);
	LeftServo.write(STOP_LEFT - 40);
	RightServo.write(STOP_RIGHT - 40);
	delay(250);
	digitalWrite(YELLOW, LOW);
	digitalWrite(GREEN, HIGH);
	LeftServo.write(STOP_LEFT + 40);
	RightServo.write(STOP_RIGHT + 40);
	delay(250);
	digitalWrite(YELLOW, HIGH);
	digitalWrite(GREEN, LOW);
	LeftServo.write(STOP_LEFT - 40);
	RightServo.write(STOP_RIGHT - 40);
	delay(250);
	digitalWrite(YELLOW, LOW);
	digitalWrite(GREEN, HIGH);
	LeftServo.write(STOP_LEFT + 40);
	RightServo.write(STOP_RIGHT + 40);
	delay(250);
	digitalWrite(YELLOW, HIGH);
	digitalWrite(GREEN, LOW);
	LeftServo.write(STOP_LEFT - 40);
	RightServo.write(STOP_RIGHT - 40);
	delay(250);
	digitalWrite(YELLOW, LOW);
	digitalWrite(GREEN, HIGH);
	LeftServo.write(STOP_LEFT + 40);
	RightServo.write(STOP_RIGHT + 40);
	delay(250);
	digitalWrite(YELLOW, HIGH);
	digitalWrite(GREEN, LOW);
}

//-------------------THIS-IS-THE-MOST-IMPORTANT-FUNCTION-WHICH-READS-THE-BARCODES--------------------------

int LDR_Barcode() {
	for (int i = 0; i <= 9; i++) {									    //Reads the middle LDR, 10 times, I'm using only the middle one because of convinience I think that using the other two ones is unnecessary
		middle_LDR[i] = analogRead(A1);
		middle_LDR[10] += middle_LDR[i];
	}
	middle_Ave = middle_LDR[10] / 10;									//then calculates the average 
	if ((middle_Ave <= LDR_light_border) && (IfBlack == 0)) {			//waits for the robot to come to black spot
		check = 1;
		IfBlack = 1;													//the second checked value is just a helper that will not allow robot to do things before he will step on the black stripe
		time_before = millis();											//saves time for later calculations
	}
	if ((middle_Ave >= LDR_light_border) && (IfBlack == 1)) {			//calculates the time it took the robot to pass the one black stripe 
		time_after = millis() - time_before;
		IfBlack = 0;
		WhichOneBarcode++;												//adds one to know which stripe he is reading at the moment 
		if (time_after >= Time_Border) {								//I've calculated that with this speed, wide stripe have 2 seconds and the other one 1 second
			barcode[numberOfTheBarcode++] = 2;							//When time will respond to wide stripe in array will be saved 2
		}
		else {
			barcode[numberOfTheBarcode++] = 1;							//When time will respond to thin stripe in array will be saved 1
		}
	}
	while (WhichOneBarcode == 4) {										//After four readings he will check which barcode he detected 
		WhichOneBarcode = 0;
		numberOfTheBarcode = 0;											//We need to reset the values of 'helpers'
		//I've tried to me this if statemets with for loop but I did not know if we could use array in array, so it's not the most efficient way, but it works
		if (barcode[0] == BAR_Left[0] && barcode[1] == BAR_Left[1] && barcode[2] == BAR_Left[2] && barcode[3] == BAR_Left[3]) {
			LEFT(90);
		}
		else if (barcode[0] == BAR_Right[0] && barcode[1] == BAR_Right[1] && barcode[2] == BAR_Right[2] && barcode[3] == BAR_Right[3]) {
			RIGHT(90);
		}
		else if (barcode[0] == BAR_Uturn[0] && barcode[1] == BAR_Uturn[1] && barcode[2] == BAR_Uturn[2] && barcode[3] == BAR_Uturn[3]) {
			UTURN();
		}
		else if (barcode[0] == BAR_Stop[0] && barcode[1] == BAR_Stop[1] && barcode[2] == BAR_Stop[2] && barcode[3] == BAR_Stop[3]) {
			STOP();
			while (something == 1) {
			}
		}
		else if (barcode[0] == BAR_Dance[0] && barcode[1] == BAR_Dance[1] && barcode[2] == BAR_Dance[2] && barcode[3] == BAR_Dance[3]) {
			BOOGIE();
		}
	}
	check = 0;															//we can start checking the obstacle
	middle_LDR[10] = 0;													//We need to reset the values of array
	delay(200);	
																		//Delay that determines the number of LDR readings
}

void setup() {
	RightServo.attach(RIGHT_MOTOR);
	LeftServo.attach(LEFT_MOTOR);
	pinMode(A1, INPUT);
	pinMode(GREEN, OUTPUT);
	pinMode(YELLOW, OUTPUT);
	pinMode(RED, OUTPUT);
	pinMode(IR_transmitter, OUTPUT);
	pinMode(IR_receiver, INPUT);
}

void loop() {
	FORWARD_BARCODE();													//In loop I'm setting the speed for barcode reading 
	OBSTACLE();															//checks if obstacle is in front of the robot and
	LDR_Barcode();													//reads the LDR and check the barcodes
}
