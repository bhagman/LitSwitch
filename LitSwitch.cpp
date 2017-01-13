/*
|| @author         Brett Hagman <bhagman@roguerobotics.com>
|| @url            http://www.roguerobotics.com/
|| @url            http://wiring.org.co/
||
|| @description
|| | A special library for an LED/momentary switch hardware combination.
|| |
|| | Wiring Cross-platform Library
|| #
||
|| @notes
|| |
|| | Based on DebounceSwitch by Chris van Marle
|| |
|| |   This library is free software: you can redistribute it and/or modify
|| |   it under the terms of the GNU General Public License as published by
|| |   the Free Software Foundation, either version 3 of the License, or
|| |   (at your option) any later version.
|| |
|| |   This library is distributed in the hope that it will be useful,
|| |   but WITHOUT ANY WARRANTY; without even the implied warranty of
|| |   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
|| |   GNU General Public License for more details.
|| |
|| |   You should have received a copy of the GNU General Public License
|| |   along with this program.  If not, see <http://www.gnu.org/licenses/>.
|| |
|| | Version Modified By Date       Comments
|| | ------- ----------- ---------- --------
|| | 0001    B Hagman    2010/05/21 Initial coding
|| | 1.0.0   B Hagman    2016/01/13 Release for Arduino Library Manager
|| #
*/

#include "LitSwitch.h"

LitSwitch::LitSwitch(byte buttonPin,
                     LEDControlType LEDControl,
                     buttonType type,
                     unsigned long debounceDelay,
                     unsigned long holdDelay,
                     unsigned long holdInterval)
: pin(buttonPin),
  debounceDelay(debounceDelay),
  holdDelay(holdDelay),
  holdInterval(holdInterval),
  LEDControl(LEDControl),
  LED(false),
  lastDebounceTime(0),
  updated(false),
  holdSent(false),
  onPress(NULL),
  onRelease(NULL)
{
  this->id = buttonId++;
//  this->pin = buttonPin;
//  this->holdDelay = holdDelay;
//  this->holdInterval = holdInterval;
  LitSwitch::buttons[this->id] = this;

  setType(type);

  // some defaults
//  lastDebounceTime = 0;
//  this->debounceDelay = debounceDelay;
//  updated = false;
//  holdSent = false;
//  onPress = NULL;
//  onRelease = NULL;
}

LitSwitch::~LitSwitch()
{
  for(int i=this->id; i<buttonId; ++i)
  {
    buttons[i] = buttons[i+1];
  }
  buttonId--;
}


boolean LitSwitch::update()
{
  // set for digital sample
  pinMode(pin, INPUT);
  // enable internal pull up
  if (type == PULLUP_INTERNAL)
    digitalWrite(pin, HIGH);
  else
    digitalWrite(pin, LOW);

  // read
  int reading = digitalRead(pin);

  // now set for LED output
  digitalWrite(pin, LEDControl ^ LED);
  pinMode(pin, OUTPUT);

  unsigned long now = millis();

  if(reading != lastButtonState)
  {
    lastDebounceTime = now;
  }

  updated = false;

  if((now - lastDebounceTime) > debounceDelay)
  {
    // Switched from unpressed to pressed or vica versa
    if(stableButtonState != reading)
    {
      stableButtonState = reading;
      updated = true;
      holdSent = 0;

      if(stableButtonState == pressedValue && onPress != NULL)
      {
        onPress(this);
      }

      if(stableButtonState != pressedValue)
      {
        if(onRelease != NULL)
        {
          onRelease(this);
        }
        if((downTime < holdDelay || onHold == NULL) && onClick != NULL)
        {
          onClick(this);
        }
      }

    }
    else if(stableButtonState == pressedValue)
    {
      downTime = now - lastDebounceTime - debounceDelay;

      if(holdDelay > 0 && // The owner wants hold events, and
        (!holdSent || holdInterval > 0 && (now - holdSent) > holdInterval) && // we haven't sent the event yet or it's time for another, and
        downTime > holdDelay && // we have waited long enough, and
        onHold != NULL) // someone is actually listening
      {
          onHold(this);
          holdSent = now;
      }
    }
  }

  lastButtonState = reading;

  return (stableButtonState == pressedValue);
}

boolean LitSwitch::isPressed()
{
  return stableButtonState == pressedValue;
}

boolean LitSwitch::justPressed()
{
  return updated && (stableButtonState == pressedValue);
}

boolean LitSwitch::justReleased()
{
  return updated && (stableButtonState != pressedValue);
}

void LitSwitch::setType(buttonType type)
{
  pinMode(pin, INPUT);
  // enable internal pull up
  if (type == PULLUP_INTERNAL)
    digitalWrite(pin, HIGH);
  else
    digitalWrite(pin, LOW);

  switch(type)
  {
    case PULLDOWN:
      pressedValue = HIGH;
      lastButtonState = stableButtonState = LOW;
      break;
    case PULLUP:
    case PULLUP_INTERNAL:
      pressedValue = LOW;
      lastButtonState = stableButtonState = HIGH;
      break;
  }
}

unsigned long LitSwitch::getDownTime()
{
  return downTime;
}

LitSwitch *LitSwitch::buttons[LitSwitch_MAX_BUTTONS];
byte LitSwitch::buttonId = 0;

void LitSwitch::updateAll()
{
  for(int i=0; i<buttonId; ++i)
  {
    buttons[i]->update();
  }
}

