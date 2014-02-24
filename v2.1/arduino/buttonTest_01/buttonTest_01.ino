
#define buttonMode 2
#define buttonRange 4
#define LedStrip 6
#define LedMode 7
#define audioOut 8
#define LedOnboard 13

uint8_t currentMode = 0; //modes could be 0 - 8

void setup(){
  pinMode(buttonMode, INPUT);
  pinMode(buttonRange, INPUT);
  pinMode(LedMode, OUTPUT);
  pinMode(LedOnboard, OUTPUT);

}

void loop(){

  updateButtons();
  updateModeLeds();

}

void updateButtons(){
  /* check both buttons, set the global currentMode to
   * whichever button has last been pressed   */
   
  int currModeBut = digitalRead(buttonMode); 
  if(currModeBut) currentMode = 1;

  int currRangeBut = digitalRead(buttonRange); 
  if(currRangeBut) currentMode = 0;
}


void updateModeLeds(){
  /* check current mode and turn on correct modeLED */
  if(currentMode == 0)  digitalWrite(LedMode, HIGH);
  else digitalWrite(LedMode, LOW);
}


