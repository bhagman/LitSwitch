#include <LitSwitch.h>

// LitSwitch buttonName = LitSwitch(pin,
//                             [LEDControl=CATHODE],            // optional
//                             [type=PULLUP_INTERNAL],          // optional
//                             [debounceDelay=50],              // optional (milliseconds)
//                             [holdDelay=0],                   // optional (milliseconds)
//                             [holdInterval=0]);               // optional (milliseconds)
//
// LEDControl = {CATHODE, ANODE}
// type = {PULLDOWN, PULLUP, PULLUP_INTERNAL}
// 
// Events:
// onPress: As soon as the switch is pressed and debounced for debounceDelay ms
// onHold:  When switch is held down for holdDelay ms (if holdInterval > 0, this is called repeatedly every holdInterval ms)
// onClick: If switch has a holdDelay > 0, and switch released before holdDelay ms
// onRelease: As soon as switch is released
//
// onHold, and onClick can be used for short and long presses of the switch.
// Special case for onHold when holdInterval > 0, allows for repeat calling of onHold.


LitSwitch buttonGreen = LitSwitch(28, CATHODE, PULLUP_INTERNAL, 50, 1000, 500);
LitSwitch buttonYellow = LitSwitch(29, CATHODE, PULLUP_INTERNAL, 50, 1000);
LitSwitch buttonRed = LitSwitch(30, CATHODE, PULLUP_INTERNAL, 50);

void setup()
{
  Serial.begin(9600);
  
  buttonGreen.onPress = onPressGreen;
  buttonGreen.onRelease = onReleaseGreen;
  buttonGreen.onClick = onClickGreen;
  buttonGreen.onHold = onHoldGreen;
  buttonYellow.onPress = onPressYellow;
  buttonYellow.onRelease = onReleaseYellow;
  buttonYellow.onClick = onClickYellow;
  buttonYellow.onHold = onHoldYellow;
  buttonRed.onPress = onPressRed;
  buttonRed.onRelease = onReleaseRed;
  buttonRed.onClick = onClickRed;        // Never called, because onHold == 0
  buttonRed.onHold = onHoldRed;          //     "           "           "
}

void loop()
{
  LitSwitch::updateAll();
}

void onPressGreen(LitSwitch *btn)
{
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.println("Green pressed");
}

void onReleaseGreen(LitSwitch *btn)
{
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Green released after ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

void onClickGreen(LitSwitch *btn)
{
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Green clicked for ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

void onHoldGreen(LitSwitch *btn)
{
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Green hold for ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

void onPressYellow(LitSwitch *btn)
{
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.println("Yellow pressed");
}

void onReleaseYellow(LitSwitch *btn)
{
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Yellow released after ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

void onClickYellow(LitSwitch *btn)
{
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Yellow clicked for ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

void onHoldYellow(LitSwitch *btn)
{
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Yellow hold for ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

void onPressRed(LitSwitch *btn)
{
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.println("Red pressed");
}

void onReleaseRed(LitSwitch *btn)
{
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Red released after ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

void onClickRed(LitSwitch *btn)
{
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Red clicked for ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

void onHoldRed(LitSwitch *btn)
{
  Serial.print(millis(), DEC);
  Serial.print(" ");
  Serial.print("Red hold for ");
  Serial.print(btn->getDownTime(), DEC);
  Serial.println("ms");
}

