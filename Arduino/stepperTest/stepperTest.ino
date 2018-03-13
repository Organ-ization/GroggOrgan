//Ludvig Ström 2018-03-13
//arduino sketch for evaluating stepper motor controls for organ

//Serial commands:
//+ increase timer
//- decrease timer
//s status
//m move
//t toggle direction

int dirPin = 2;
int pulPin = 3;
int enaPin = 4;
int delayTime = 40;
bool toggleDir = false;

void setup() {
  pinMode(dirPin, OUTPUT);
  pinMode(pulPin, OUTPUT);
  pinMode(enaPin, OUTPUT);
  digitalWrite(dirPin, LOW);
  digitalWrite(pulPin, LOW);
  digitalWrite(enaPin, HIGH);

  Serial.begin(9600);
}

void loop() {
  handleSerial();
}

void handleSerial() {
  while (Serial.available() > 0) {
    char incomingCharacter = Serial.read();
    switch (incomingCharacter) {
      case '+':
        delayTime += 5;
        break;

      case '-':
        delayTime -= 5;
        if (delayTime <= 0)
          delayTime = 0;
        break;

      case 's':
        //print status
        Serial.println("Delay time:" + delayTime);
        break;

      case 'm':
        //move
        moveDistance(30000, toggleDir);
        break;

      case 't':
        //toggle direction
        if (toggleDir == true)
          toggleDir = false;
        else
          toggleDir = true;
        break;
      }
    }
}


void moveDistance(int steps, bool dir) {
  //set direction
  if (dir == true)
    digitalWrite(dirPin, HIGH);
  else
    digitalWrite(dirPin, LOW);

  digitalWrite(enaPin, LOW);

  pulsePin(pulPin, steps);

  //disables driver
  digitalWrite(enaPin, HIGH);

}

void pulsePin(int pin, int times) {
  for (int i = 0; i < times; i++) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(pin, LOW);
    delayMicroseconds(delayTime);
  }
}
