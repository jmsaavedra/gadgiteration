
int ctr = 0;
int led[6] = {
  3, 5, 6, 12, 11, 10};

void setup(){
  for (int i=0; i<7; i++){
    pinMode(led[i], OUTPUT); 
  }
  Serial.begin(9600);
}

void loop(){
  Serial.print("loop number: ");
  Serial.println(ctr);
  ctr++;
  for(int i=0; i<7; i++){
    digitalWrite(led[i], HIGH);
    delay(100);
    digitalWrite(led[i], LOW);
    delay(100);
  }

  for(int i=0; i<7; i++){
    digitalWrite(led[i], LOW);
  }

  for(int i=0; i<7; i++){
    digitalWrite(led[i], HIGH);
    delay(100);
  }

  for(int i=7; i>0; i--){
    digitalWrite(led[i], LOW);
    delay(100);
  }
}

