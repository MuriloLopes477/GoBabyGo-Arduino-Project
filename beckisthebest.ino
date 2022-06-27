//pin definitions
#define xJoystick A0
#define yJoystick A1
#define s 4

/DeadArea value
#define joystickDeadValue 520

/Motor pin definitions
int motor1PinR = 5;
int motor1PinL = 6;
int motor2PinR = 9;
int motor2PinL = 10;


//ezButton butonn(s);

//Adjusts pins to either output or input respectively.
void setup() {
  //begins the serial monitor.
  Serial.begin(9600);
  pinMode(motor1PinR, OUTPUT);
  pinMode(motor1PinL, OUTPUT);
  pinMode(motor2PinR, OUTPUT);
  pinMode(motor2PinL, OUTPUT);
  pinMode(s, INPUT);

  //possible button
  //butonn.setDebounceTime(100);

}

void loop() {
  //Set X and Y to the joystick's axis.
  int x = analogRead(xJoystick);
  int y = analogRead(yJoystick);

  //Makes sure x and y don't get off the dead area by small changes.
  y = deadArea(y);
  x = deadArea(x);

  //Old button code.
 /* if (butonn.isPressed()) {
    Serial.println("Button is on");
  } else {
    Serial.println("Button is off");
  }*/

  //reads button and prints it's value.
  /*int calv = digitalRead(s);
  Serial.println(calv);*/
  
  //Moves in the direction in which tbe joystick relies on.
  movement(x, y);
}

//Creates a dead area where values around a specific range will alyaws set x and y to joystickDeadValue, else it will return the actual axis value.
int deadArea(int valueN) {
  if (valueN >= 440 && valueN <= 580) {
    return joystickDeadValue;
  }
  return valueN;
}

//Movement function which controls wheelchair's movement if a condition is met.
int movement(int xValue, int yValue) {
  //pwm values for motor controllers are about 0 - 255
  /*int rightValue = (yValue - joystickDeadValue) / 2;
  int leftValue = (joystickDeadValue - yValue) / 2;
  int backValue = (joystickDeadValue - xValue) / 2;*/
  int xSpeed = (xValue - joystickDeadValue) / 2;
  int ySpeed = (yValue - joystickDeadValue) / 2;
  //prevents pwm values from exceding 251
  /*if(rightValue > 251){
      rightValue = 251;  
    }
  if(leftValue > 251){
      leftValue = 251;  
    }
   if(backValue > 251){
     backValue = 251;  
   }*/
   xSpeed = abs(xSpeed);
   ySpeed = abs(ySpeed);
   if (xSpeed > 251){
    xSpeed = 251;
   }
   if (ySpeed > 251) {
    ySpeed = 251;
   }
   
   Serial.print("xSpeed = ");
   Serial.print(xSpeed);
   Serial.print(", ySpeed = ");
   Serial.println(ySpeed);
   
   Serial.print("xValue = ");
   Serial.print(xValue);
   Serial.print(", yValue = ");
   Serial.println(yValue);
  if ((xValue > joystickDeadValue && yValue == joystickDeadValue)) { //forwards x
    analogWrite(motor1PinR, /*(xValue - joystickDeadValue) / 2*/ xSpeed);
    analogWrite(motor1PinL, 0);
    analogWrite(motor2PinR, /*(xValue - joystickDeadValue) / 2*/ xSpeed);
    analogWrite(motor2PinL, 0);
    //Serial.println(xValue);
    Serial.println(/*(xValue - joystickDeadValue) / 2*/ xSpeed);    
  } else if (xValue < joystickDeadValue && yValue == joystickDeadValue) { //backwards x
    analogWrite(motor1PinR, 0);
    analogWrite(motor1PinL, /*backValue*/(xSpeed));
    analogWrite(motor2PinR, 0);
    analogWrite(motor2PinL, xSpeed);
    //Serial.println(backValue);
    Serial.println(-1 * xSpeed);
  } else if (xValue == joystickDeadValue && yValue < joystickDeadValue) { //rotate left x
    analogWrite(motor1PinR, /*leftValue*/ (ySpeed));
    analogWrite(motor1PinL, 0);
    analogWrite(motor2PinR, 0);
    analogWrite(motor2PinL, /*leftValue*/ (ySpeed));
    //Serial.println(leftValue);
    Serial.println(-1 * ySpeed);
  } else if (xValue == joystickDeadValue && yValue > joystickDeadValue) { //rotate right x
    analogWrite(motor1PinR, 0);
    analogWrite(motor1PinL, /*rightValue*/ ySpeed);
    analogWrite(motor2PinR, /*rightValue*/ ySpeed);
    analogWrite(motor2PinL, 0);
    //Serial.println(rightValue);
    Serial.println(ySpeed);
  } else if (xValue < joystickDeadValue && yValue > joystickDeadValue) { //inferior right diagonal x
    if (yValue >= 520 && yValue < 771) {
      ySpeed = abs(cos((yValue - 520)/251)) * 245;
    } else if (yValue >= 771 && yValue <= 1023) {
      ySpeed = abs(sin(yValue - 628)/251) * 245;
    }
    analogWrite(motor1PinL, ySpeed);    
    analogWrite(motor1PinR, 0);
    analogWrite(motor2PinR, 0);
    analogWrite(motor2PinL, xSpeed);
  } else if (xValue < joystickDeadValue && yValue < joystickDeadValue) { //inferior left diagonal x
    if (yValue <= 520 && yValue > 260) {
      ySpeed = abs(cos((yValue - 514)/251)) * 245;
    } else if (yValue >= 0 && yValue <= 260) {
      ySpeed = abs(sin(yValue - 401)/251) * 245;
    }
    analogWrite(motor1PinR, 0);
    analogWrite(motor1PinL, xSpeed);
    analogWrite(motor2PinR, 0);
    analogWrite(motor2PinL, ySpeed * 0.8);
    } else if (xValue > joystickDeadValue && yValue < joystickDeadValue) { //superior left diagonal x
    //motor1PinR pwm has to be the higher speed when this logic is executed
    if (yValue <= 520 && yValue > 260) {
      ySpeed = abs(cos((yValue - 514)/251)) * 245;
    } else if (yValue >= 0 && yValue <= 260) {
      ySpeed = abs(sin(yValue - 401)/251) * 245;
    }
    analogWrite(motor1PinR, xSpeed);
    analogWrite(motor1PinL, 0);
    analogWrite(motor2PinR, ySpeed);
    //analogWrite(motor2PinR, ySpeed * 0.8);
    analogWrite(motor2PinL, 0);
    
  } else if (xValue > joystickDeadValue && yValue > joystickDeadValue){ //superior right diagonal x
    //analogWrite(motor1PinR, ySpeed * 0.8);
    if (yValue >= 520 && yValue < 771) {
      ySpeed = abs(cos((yValue - 520)/251)) * 245;
    } else if (yValue >= 771 && yValue <= 1023) {
      ySpeed = abs(sin(yValue - 628)/251) * 245;
    }
    analogWrite(motor1PinR, ySpeed);
    analogWrite(motor1PinL, 0);
    analogWrite(motor2PinR, xSpeed);
    analogWrite(motor2PinL, 0);
    
  } else { //no movement x
    analogWrite(motor1PinR, 0);
    analogWrite(motor1PinL, 0);
    analogWrite(motor2PinR, 0);
    analogWrite(motor2PinL, 0);
    Serial.println("No movement.");
  }
}
