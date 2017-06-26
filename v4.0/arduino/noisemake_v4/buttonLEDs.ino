
int modeButtonState; //button state
long lastPressTime; //to not trigger multiple mode changes

void updateButtons() {
  /* check MODE button, set the global currentMode to
     whichever button has last been pressed   */

  modeButtonState = digitalRead(buttonMode);
  
  //if button is HIGH and it's been over 1 second since last mode change
  if (modeButtonState && (millis() - lastPressTime > 1000)) {
    lastPressTime = millis(); //reset timer
    
    currentMode++;
    if (currentMode > 2) //we only have mode 0 and mode 1 and mode 2 currently
      currentMode = 0;

    Serial.print("currentMode: ");
    Serial.println(currentMode);
    updateModeLed();
  }
}


void updateModeLed() {
  /* check current mode and update onboard LED */
  if (currentMode == 0)
    onboard.setPixelColor(0, onboard.Color(100, 0, 100)); // Moderately bright purple color.
  else if (currentMode == 1)
    onboard.setPixelColor(0, onboard.Color(0, 100, 0)); // Moderately bright green color.
  else if (currentMode == 2)
    onboard.setPixelColor(0, onboard.Color(100, 50, 0)); // Moderately bright green color.


  onboard.show(); //send color update to pixel
}

