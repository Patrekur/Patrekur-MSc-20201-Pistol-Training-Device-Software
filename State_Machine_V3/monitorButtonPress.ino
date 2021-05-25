void monitorButtonPress(){
  bool justEntered = true; 

  if ((millis() - pressTime) > 50) {
/* This is to prevent wrong-button-presses from 
   lingering in the system. */
    okAccept = false;
    exitAccept = false;
    backNextAccept = false;
    pressTime = 0;
  }

// the debounceDelay makes sure that one button press doesn't get 
// interpreted as multiple.
  if ((millis() - lastDebounceTime) > debounceDelay) {
//    Serial.print("         lDt: ");Serial.println(lastDebounceTime);
//    Serial.print("millis - lDt: ");Serial.println(millis() - lastDebounceTime);
    while(onlyAllowRisingButton(backButtonPin, backButtonState)){
    if(justEntered){//only do this once
      lastDebounceTime = millis();
      backButtonPressed();
      justEntered = false;
    }

    }
    while(onlyAllowRisingButton(nextButtonPin, nextButtonState)){
       if(justEntered){//only do this once
        lastDebounceTime = millis();
        nextButtonPressed();
        justEntered = false;
      }
    }
    while(onlyAllowRisingButton(okButtonPin, okButtonState)){
      if(justEntered){//only do this once
        lastDebounceTime = millis();
        okButtonPressed();
        justEntered = false;
      }
      
    }
    while(onlyAllowRisingButton(exitButtonPin, exitButtonState)){
      if(justEntered){//only do this once
        lastDebounceTime = millis();
        exitButtonPressed();
        justEntered = false;
      }
    }
  }
} // end monitorButtonPress()


bool onlyAllowRisingButton(int reading, int bState ) {
  bool isButtonHigh = false;
  
  if(bState != digitalRead(reading) && digitalRead(reading) == HIGH ){ 
    // now: state = low, reading = high
    // meaning: button has been pressed, but unknown if button is kept down 
    if(!isButtonHigh){ // only if button is NOT kept down
      bState = HIGH; 
      isButtonHigh = true;
    }
  
    //now: state = high, reading = high, isButtonHigh = true
    // meaning: computer knows the button has been pressed, and is being kept that way. 
  }
  else if ( bState != digitalRead(reading) && digitalRead(reading) == LOW ){ 
    //now: state = high, reading = low
    //meaning: button has been released
    bState = LOW;
    isButtonHigh = false;
    //now: state = low, isButtonHigh = false
    // meaning: computer knows button has been released
  } 
  //else: state = low, reading = low, do: nothing

  if(bState == HIGH){
    return true;
  }
  else {
    return false;
  }
}// end onlyAllowRisingButton()





void okButtonPressed(){
  okAccept = true;
  pressTime = millis();

  Serial.print("Inside okButtonPressed(): "),
  Serial.print("pressTime = "); 
  Serial.println(String(pressTime));
}

void exitButtonPressed(){
  exitAccept = true;
  pressTime = millis();
}

void nextButtonPressed(){
  //This makes sure not to overflow
  // when cycling through the menus
  pressTime = millis();
  int maximum = 0;
  
  if(isMenu){
    maximum = 4;
  }
  else if(isSports){
    maximum = 6;
  }
  else if(isSettings){
    maximum = 3;
  }

  
  else if(isUnallocated){
    maximum = 3;
  }
  
  if(state + 1 <= maximum){
    state++;
  }
  else {
    state = 1;
  }
  backNextAccept = true;
}

void backButtonPressed() {
  pressTime = millis();
  int maximum = 0;
  
  if(isMenu){
    maximum = 4;
  }
  else if(isSports){
    maximum = 6;
  }
  else if(isSettings){
    maximum = 3;
  }
  else if(isUnallocated){
    maximum = 2;
  }

  if(state - 1 >= 1){
    state--;
  }
  else {
    state = maximum;
  }
  backNextAccept = true;
}
