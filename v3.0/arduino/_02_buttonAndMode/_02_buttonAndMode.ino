
#define buttonMode 2
#define buttonRange 4
#define ledStrip 6
#define ledMode 5
#define audioOut 8
//#define ledOnboard 5

#define gadgitCircuitIn A0
#define humanCircuitIn A1

uint8_t currentMode = 0; //modes could be 0 - 8
int currentVal = 0;

void setup(){
  pinMode(buttonMode, INPUT);
  pinMode(buttonRange, INPUT);
  pinMode(ledMode, OUTPUT);
//  pinMode(ledOnboard, OUTPUT);
  
  Serial.begin(57600);
}

void loop(){

  /* update buttons and mode LEDs */
  updateButtons();
//  updateModeLeds();
  
  switch(currentMode){
   
    case 0: //--- REGULAR GADGIT MODE ---
      digitalWrite(ledMode, HIGH);
      currentVal = analogRead(gadgitCircuitIn);      
      //TODO: map currentVal to 0-1000 or 0-100 or something even
      
      
      
      
      Serial.print("GADGIT currentVal:\t");
      Serial.println(currentVal);
      break;
    
    case 1: //--- HUMAN CIRCUIT MODE ---
      digitalWrite(ledMode, LOW);
      currentVal = analogRead(humanCircuitIn);
      //TODO: map currentVal to 0-1000 or 0-100 or something even
      
      
      
      Serial.print("HUMAN currentVal:\t");
      Serial.println(currentVal);
      
      break;   
  }
}

void updateButtons(){
  /* check both buttons, set the global currentMode to
   * whichever button has last been pressed   */
   
  int currModeBut = digitalRead(buttonMode); 
  if(currModeBut) currentMode = 1;

  int currRangeBut = digitalRead(buttonRange); 
  if(currRangeBut) currentMode = 0;
}


//void updateModeLeds(){
//  /* check current mode and turn on correct modeLED */
//  if(currentMode == 0)  digitalWrite(ledMode, HIGH);
//  else digitalWrite(ledMode, LOW);
//}
//


