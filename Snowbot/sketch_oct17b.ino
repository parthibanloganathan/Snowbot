
int dirPin1 = 3;
int stepperPin1 = 2;
int dirPin2 = 7;
int stepperPin2 = 6;
void setup() {
  pinMode(dirPin1, OUTPUT);
  pinMode(stepperPin1, OUTPUT);
  pinMode(dirPin2, OUTPUT);
  pinMode(stepperPin2, OUTPUT);
}

void step(boolean dir,int steps){
  digitalWrite(dirPin1,dir);
  digitalWrite(dirPin2,dir);
  delay(50);
  //for(int i=0;i<steps;i++)
  while(1){
    //digitalWrite(stepperPin1, HIGH);
    digitalWrite(stepperPin2, HIGH);
    delayMicroseconds(500);
    //digitalWrite(stepperPin1, LOW);
    digitalWrite(stepperPin2, LOW);
    delayMicroseconds(500);
  }
}

void loop(){
  step(true,1600*5);
  delay(500);
  step(false,1600*5);
  delay(500);
}
