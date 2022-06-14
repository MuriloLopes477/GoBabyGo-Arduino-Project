//#include <ezButton.h>
//#include <Servo.h>

#define xJoystick A0
#define yJoystick A1
#define s 4


#define joystickDeadValue 520

int motor1PinR = 5;
int motor1PinL = 6;
int motor2PinR = 9;
int motor2PinL = 10;


//ezButton butonn(s);


//Servo motor1;
//Servo motor2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(motor1PinR, OUTPUT);
  pinMode(motor1PinL, OUTPUT);
  pinMode(motor2PinR, OUTPUT);
  pinMode(motor2PinL, OUTPUT);
  pinMode(s, INPUT);
  
// butonn.setDebounceTime(100);

}

void loop() {
  // put your main code here, to run repeatedly:
  int x = analogRead(xJoystick);
  int y = analogRead(yJoystick);

  y = deadArea(y);
  x = deadArea(x);

 /* if (butonn.isPressed()) {
    Serial.println("Button is on");
  } else {
    Serial.println("Button is off");
  }*/


  int calv = digitalRead(s);
  Serial.println(calv);
  

  movement(x, y);

}
int deadArea(int valueN) {
  if (valueN >= 500 && valueN <= 545) {
    return joystickDeadValue;
  }
  return valueN;
}


int movement(int xValue, int yValue) {

  //pwm values for motor controllers are about 0 - 255
  int rightValue = (yValue - joystickDeadValue) / 2;
  int leftValue = (joystickDeadValue - yValue) / 2;
  if(rightValue > 251){
      rightValue = 251;  
    }
  if(leftValue > 251){
      leftValue = 251;  
    }
  if ((xValue > joystickDeadValue && yValue == joystickDeadValue)) { //forwards x
    analogWrite(motor1PinR, (xValue - joystickDeadValue) / 2);
    analogWrite(motor1PinL, 0);
    analogWrite(motor2PinR, (xValue - joystickDeadValue) / 2);
    analogWrite(motor2PinL, 0);
    //Serial.println(xValue);
    Serial.println((xValue - joystickDeadValue) / 2);
    
 
  } else if (xValue < joystickDeadValue && yValue > joystickDeadValue) { //inferior right diagonal x
    //analogWrite(motor1PinR, HIGH);
    //analogWrite(motor1PinL, HIGH);
    //analogWrite(motor2PinR, HIGH);
    //analogWrite(motor2PinL, HIGH);
  } else if (xValue < joystickDeadValue && yValue < joystickDeadValue) { //inferior left diagonal x
    //analogWrite(motor1PinR, HIGH);
    //analogWrite(motor1PinL, HIGH);
    //analogWrite(motor2PinR, HIGH);
    //analogWrite(motor2PinL, HIGH);
  } else if (xValue > joystickDeadValue && yValue < joystickDeadValue) { //superior left diagonal x
    //analogWrite(motor1PinR, HIGH);
    //analogWrite(motor1PinL, HIGH);
    //analogWrite(motor2PinR, HIGH);
    //analogWrite(motor2PinL, HIGH);
  } else if (xValue > joystickDeadValue && yValue > joystickDeadValue){ //superior right diagonal x
    //analogWrite(motor1PinR, HIGH);
    //analogWrite(motor1PinL, HIGH);
    //analogWrite(motor2PinR, HIGH);
    //analogWrite(motor2PinL, HIGH);
  } else if (xValue < joystickDeadValue && yValue == joystickDeadValue) { //backwards x
    int backValue = (joystickDeadValue - xValue) / 2;
    if(backValue > 251){
      backValue = 251;  
    }
    analogWrite(motor1PinR, 0);
    analogWrite(motor1PinL, backValue);
    analogWrite(motor2PinR, 0);
    analogWrite(motor2PinL, backValue);
    Serial.println(backValue);
  } else if (xValue == joystickDeadValue && yValue < joystickDeadValue) { //rotate left x
    analogWrite(motor1PinR, leftValue);
    analogWrite(motor1PinL, 0);
    analogWrite(motor2PinR, 0);
    analogWrite(motor2PinL, leftValue);
    Serial.println(leftValue);
  } else if (xValue == joystickDeadValue && yValue > joystickDeadValue) { //rotate right x
    analogWrite(motor1PinR, 0);
    analogWrite(motor1PinL, rightValue);
    analogWrite(motor2PinR, rightValue);
    analogWrite(motor2PinL, 0);
    Serial.println(rightValue);
  } else { //no movement x
    analogWrite(motor1PinR, 0);
    analogWrite(motor1PinL, 0);
    analogWrite(motor2PinR, 0);
    analogWrite(motor2PinL, 0);
  }
}
