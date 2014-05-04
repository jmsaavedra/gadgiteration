

byte led[] = {
  3, 4, 5, 6, 23, 22, 21, 20};
int numLeds;

int dTime = 100; //delay time

void setup(){
  numLeds = sizeof(led);
  pinMode(13, OUTPUT); // teensy orange led on, so that
  digitalWrite(13, HIGH); // we know teensy on and has power
  
  for(int j=0; j<3; j++){ //set LEDs to output, blink thrice
    for (int i=0; i<numLeds; i++){
      pinMode(led[i], OUTPUT);
      digitalWrite(led[i], HIGH);
    } 
    delay(150);
    for (int i=0; i<numLeds; i++){
      digitalWrite(led[i], LOW);
    }   
    delay(150);
  }
  
}

void loop(){
  for (int i=0; i<numLeds; i++){
    digitalWrite(led[i], HIGH);
    delay(dTime);
  }
  for (int i=numLeds-1; i>=0; i--){
    digitalWrite(led[i], LOW);
    delay(dTime);
  }
}






