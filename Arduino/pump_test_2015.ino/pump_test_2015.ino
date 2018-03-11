//one tunr = 12800, 
//recomennded speed = 40uS/Step.
//one ml = 4266,7 steps

#define STEP_PIN 3

void setup() { 
  pinMode(STEP_PIN, OUTPUT); 
} 

void loop(){ 
  
  rotateAccel(1, 10, 25); //pour x cl, acceltime x%, speed X uS.
  delay(1000); //wait one second 
}

void rotate(int steps, float speed){ //rotate a number of steps, with speed. Lower speed is faster 40uS recommended
  for(int i=0; i < steps; i++){
    toggleStepPin(speed); 
  }
}

void rotateAccel(int centiLitre, int accelProcent, float accelLimit){ //rotate number of steps, accelProcent controls how long to accelerate, accelLimit is the limit.

  long steps = centiLitre * 42667; //calculate number of steps to take. 42667 pulses/centiLitre 
  
  if(accelProcent == 0 || accelProcent > 100){
    accelProcent = 0;
  }
  
  long accelTime = steps * ((float)accelProcent*0.01); //calculate for how long to accelerate
  long timeToDeaccelerate = steps - accelTime; //when to start deaccelerate 
  float speedRightNow = 250; //start delay time
  
  //calculate how much to decrese delay each time
  float speedDecreseValue = (float)speedRightNow - accelLimit;
  speedDecreseValue = speedDecreseValue / accelTime;
  
  for(long i=0; i < steps; i++){
  
    if(accelTime > 0 && speedRightNow > accelLimit){ //accelerate if suitible
      accelTime--;
      speedRightNow -= speedDecreseValue;
    }
    
    if(i >= timeToDeaccelerate){ //deaccelerate if suitible
      speedRightNow += speedDecreseValue;
    }
    
    toggleStepPin(speedRightNow);
  }
  
}

  void toggleStepPin(float delayTime){
    digitalWrite(STEP_PIN, HIGH); 
    delayMicroseconds(delayTime); 

    digitalWrite(STEP_PIN, LOW); 
    delayMicroseconds(delayTime); 
}


