
void sportMachine(){
  isMenu = false; 
  isSports = true;
  isSettings = false;
  isUnallocated = false;
   switch (state) {
    case 1:// --------------- case 1: 25m Standard pistol
//      textOnScreen(0, 1, "[1] 2  3  4  5  6");
//      textOnScreen(0, 2, " 7  8  9  10  11  12");
      trapMenuInState(nothing, state, "","Standard pistol", "[1] 2  3  4  5  6", "");

      break;
    case 2:// --------------- case 2: 25yard Precision pistol

      trapMenuInState(nothing, state, "","Precision pistol", " 1 [2] 3  4  5  6", "");
 
      break;
    case 3:// --------------- case 3: Free pistol

      trapMenuInState(nothing, state, "","Free pistol", " 1  2 [3] 4  5  6", "");

      break;
    case 4:// --------------- case 4: 10m Air pistol

      trapMenuInState(nothing, state, "","Air pistol", " 1  2  3 [4] 5  6", "");
      
      break;
    case 5:// --------------- case 5: unknown

      trapMenuInState(nothing, state, "","Unknown 1", " 1  2  3  4 [5] 6", "");

      break;
    case 6:// --------------- case 6: unknown
   
      trapMenuInState(nothing, state, "","Unknown 2", " 1  2  3  4  5 [6]", "");  

      break;
    default:
      textOnScreen(0, 0, "Sports Menu");
      textOnScreen(0, 1, "");
      textOnScreen(0, 2, "");
      textOnScreen(0, 3, "");
      delay(900);
      state = 1;
  }

} // close sportSelection



void menuMachine(){
  isMenu = true; 
  isSports = false;
  isSettings = false;
  isUnallocated = false;
  switch (state) {
      case 1: // --------------- case 1 - Settings
        //lcd.clear();
        textOnScreen(0, 0, "Settings");
        textOnScreen(0, 1, "[1] 2  3  4");
        //Pass appropriate function and text for lines 1, 2, 3 & 4
        trapMenuInState(nothing, state, "Settings", "[1] 2  3  4", "", "");
        

        break;
      case 2: // --------------- case 2 - Sports
        //lcd.clear();
        textOnScreen(0, 0, "Sports Menu");
        textOnScreen(0, 1, " 1 [2] 3  4");
        trapMenuInState(sportMachine, state, "Sports", " 1 [2] 3  4", "", "");

        break;
      case 3:  // --------------- case 3 - Manual mode
       //lcd.clear();
        textOnScreen(0, 0, "Manual mode");
        textOnScreen(0, 1, " 1  2 [3] 4");
        trapMenuInState(nothing, state, "Manual mode", " 1  2 [3] 4", "", "");
        
        break;
      case 4: // --------------- case 4 - Unknown
       // lcd.clear();
        textOnScreen(0, 0, "stateHistory");
        textOnScreen(0, 1, " 1  2  3 [4]");
        trapMenuInState(nothing, state, "stateHistory", " 1  2  3 [4]", "", "");
        
        break;
      default:
      textOnScreen(0, 0, "Main Menu");
      textOnScreen(0, 1, "");
      textOnScreen(0, 2, "");
      textOnScreen(0, 3, "");
      state = 1;
      delay(900);
    }
}


void trapMenuInState(void (*passedStateMachine)(),int nestedState, String text1, String text2, String text3, String text4){
  
  while(!backNextAccept){
          textOnScreen(0, 0, text1);
          textOnScreen(13, 0, "Choose?");
          textOnScreen(0, 1, text2);
          textOnScreen(0, 2, text3);
          textOnScreen(0, 3, text4);
          monitorButtonPress();
          
          if(okAccept){
            textOnScreen(13, 0, "Chosen!");
            okAccept = false;
            state = 0;
            while(!exitAccept){ // ------ this is new main loop() when in a nested function
              monitorButtonPress();
//            Send system to appropriate function here
              
             (*passedStateMachine)();
             
            } // -----------------  new main loop() end
            exitAccept = false;
            state =  nestedState;
          }
          else if(exitAccept) {
            state = 0;
            exitAccept = false;
            break;
          }
        }
        backNextAccept = false;
}

void nothing(){
  textOnScreen(0,2,"Placeholder function");
  textOnScreen(0,3,"    press exit");
}
