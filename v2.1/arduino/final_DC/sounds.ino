//define notes
//windFish
int melody1[] = {
  NOTE_D5, NOTE_E5, NOTE_F5, 
  NOTE_D5, NOTE_E5, NOTE_F5, 
  NOTE_E5, NOTE_D5, NOTE_A4, 
  NOTE_C5, NOTE_D5, 0
};
int noteDurations1[] = {
  200, 200, 800, 
  200, 200, 800,
  200, 200, 200, 
  600, 600, 600
};

//songOfStorms
int melody2[] = {
  NOTE_D4, NOTE_F4, NOTE_D5, 
  NOTE_D4, NOTE_F4, NOTE_D5, 
  NOTE_E5, NOTE_F5, NOTE_E5, 
  NOTE_F5, NOTE_E5, NOTE_C5, NOTE_A4, 0
};
int noteDurations2[] = {
  200, 200, 600, 
  200, 200, 600, 
  600, 200, 200, 
  200, 200, 200, 600, 600
};

//overWorld
int melody3[] = {
  NOTE_A4, NOTE_E4, NOTE_A4, 
  NOTE_A4, NOTE_B4, NOTE_C5, 
  NOTE_D5, NOTE_E5, 0
};
int noteDurations3[] = {
  300, 600, 200,
  200, 200, 200, 
  200, 600, 600
};

//mario
int melody4[] = {
  NOTE_E4, NOTE_E4, NOTE_E4, NOTE_C4, NOTE_E4, NOTE_G4, NOTE_G3,
  NOTE_C4, NOTE_G3, NOTE_E3, NOTE_A3, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_B3,
  NOTE_C4, NOTE_G3, NOTE_E3, NOTE_A3, NOTE_B3, NOTE_AS3, NOTE_A3, NOTE_G3, NOTE_E4, NOTE_G4, NOTE_A4, NOTE_F4, NOTE_G4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_B3,
  NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_GS3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_G4, NOTE_FS4, NOTE_E4, NOTE_DS4, NOTE_E4, NOTE_GS3, NOTE_A3, NOTE_C4, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_DS4, NOTE_D4, NOTE_C4,
  NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_G3, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4,
  NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_A3, NOTE_G3
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations4[] = {
  8,4,4,8,4,2,2,
  3,3,3,4,4,8,4,8,8,8,4,8,4,3,8,8,3,
  3,3,3,4,4,8,4,8,8,8,4,8,4,3,8,8,2,
  8,8,8,4,4,8,8,4,8,8,3,8,8,8,4,4,4,8,2,
  8,8,8,4,4,8,8,4,8,8,3,3,3,1,
  8,4,4,8,4,8,4,8,2,8,4,4,8,4,1,
  8,4,4,8,4,8,4,8,2
};

//play windFish
void windFish(){
  int noteDuration = noteDurations1[thisNote];
  tone(audioOut, melody1[thisNote], noteDuration);
  int pauseBetweenNotes = noteDuration;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 12; 
}

//play songOfStorms
void songOfStorms(){
  int noteDuration = noteDurations2[thisNote];
  tone(audioOut, melody2[thisNote], noteDuration);
  int pauseBetweenNotes = noteDuration;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 14;
}

//play overWorld
void overWorld(){
  int noteDuration = noteDurations3[thisNote];
  tone(audioOut, melody3[thisNote], noteDuration);
  int pauseBetweenNotes = noteDuration;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 9;
}

//play mario
void mario(){
  int noteDuration = 1000/noteDurations4[thisNote];
  tone(audioOut, melody4[thisNote],noteDuration);
  int pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);
  thisNote = (thisNote + 1) % 98;
}


