

byte digitalButton (int pin) {

  for (int i = 0; i < numDigButtons; i++) {
    // Read the state of the button

    buttonVal[i] = digitalRead(digitalButtonPins[i]);

    //delay(10);

    // Test for button pressed and store the down time
    if (buttonVal[i] == LOW && buttonLast[i] == HIGH && (millis() - btnUpTime[i]) > debounce)
    {
      btnDnTime[i] = millis();
    }

    // Test for button release and store the up time
    if (buttonVal[i] == HIGH && buttonLast[i] == LOW && (millis() - btnDnTime[i]) > debounce)
    {
      if (ignoreUp[i] == false && menuMode[i] == false) event1(digitalButtonPins[i]);
      else ignoreUp[i] = false;
      btnUpTime[i] = millis();
    }

    // Test for button held down for longer than the hold time
    if (buttonVal[i] == LOW && menuMode[i] == false && (millis() - btnDnTime[i]) > long(holdTime))
    {
      //Serial.println("Menu Mode");
      ignoreUp[i] = true;
      btnDnTime[i] = millis();
      menuMode[i] = true;
    }
    if (buttonVal[i] == HIGH && buttonLast[i] == LOW && (millis() - btnDnTime[i]) > debounce)
    {
      if (ignoreUp[i] == false && menuMode[i] == true) event2(digitalButtonPins[i]);
      else ignoreUp[i] = false;
      btnUpTime[i] = millis();
    }
    if (buttonVal[i] == LOW && menuMode[i] == true && (millis() - btnDnTime[i]) > long(holdTime))
    {
      //Serial.println("Normal Mode");
      ignoreUp[i] = true;
      btnDnTime[i] = millis();
      menuMode[i] = false;
    }
    buttonLast[i] = buttonVal[i];
  }
}

// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long analogLastDebounceTime = 0;  // the last time the output pin was toggled
//long debounceDelay = 8;    // the debounce time; increase if the output flickers


void readAnalogButtons() {
  AXIS_X.readAxis();
  AXIS_Y.readAxis();
  if (menuState != MENU_STATE_EDIT_NUMBER) {
    if (AXIS_X.wasAxisPressed() == 1) {
      if (menuSelectLine < 5) {
        menuSelectLine++;
#ifdef DEBUG
        Serial.println("Down; Select line:  " + String(menuSelectLine) + "; Print line: " + String(menuPrintLine));
#endif
      }
    } else if (AXIS_X.wasAxisPressed() == 2) {
      if (menuSelectLine > 0) {
        menuSelectLine--;
#ifdef DEBUG
        Serial.println("Up; Select line: " + String(menuSelectLine) + "; Print line: " + String(menuPrintLine));
#endif
      }
    } else if (AXIS_Y.wasAxisPressed() == 1) {
#ifdef DEBUG
      Serial.println("Left");
#endif
    } else if (AXIS_Y.wasAxisPressed() == 2) {
#ifdef DEBUG
      Serial.println("Right");
#endif
    }
  }
}


// Events to trigger by click and press+hold

void event1(int pin) {
  if (pin > 20  && pin < 40) {
    if (pin == 27) {
#ifdef DEBUG
      Serial.println("Select");
#endif
    } else if (pin == 32) {
      state = 1;
//      if (state == 1) {
//        mainMenuScreen();
//      }
#ifdef DEBUG
      Serial.println("Menu");
      Serial.println("State is :" + String(state));
#endif
    } else if (pin == 33) {
      state = 0; 
      if (state == 0) {
        loopScreen();
      }
#ifdef DEBUG
      Serial.println("Back");
      Serial.println("State is :" + String(state));
#endif
      //      menuSelectLine = 0;
    } else
#ifdef DEBUG
      Serial.println("button 1 (" + String(pin) + ")");
#endif
  }
  delay(50);
  //  if (pin == 32) {
  //    menuScreen();
  //  } else if (pin == 33) {
  //    loopScreen();
  //  }
}

void event2(int pin)
{
  if (pin > 20 && pin < 40) {
    Serial.println("button 2 (" + String(pin) + ")");
  }
  delay(50);
  //  if (pin == 33) {
  //    loopScreen();
  //  }
}
