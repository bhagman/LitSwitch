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


#ifndef LitSwitch_h
#define LitSwitch_h

#include "Arduino.h"

#define LitSwitch_MAX_BUTTONS    20

enum buttonType {PULLDOWN = 0, PULLUP, PULLUP_INTERNAL};
enum LEDControlType {ANODE = 0, CATHODE = 1};


class LitSwitch {
  public:
    LitSwitch(byte buttonPin, LEDControlType LEDControl = CATHODE, buttonType type = PULLUP_INTERNAL, unsigned long debounceDelay = 50, unsigned long holdDelay = 0, unsigned long holdInterval = 0);
    ~LitSwitch();
    boolean update();
    boolean justPressed();
    boolean justReleased();
    boolean isPressed();

    void setType(buttonType type);
    unsigned long getDownTime();
    
    boolean LED;

    void (*onPress)(LitSwitch*);
    void (*onRelease)(LitSwitch*);
    void (*onClick)(LitSwitch*);
    void (*onHold)(LitSwitch*);

    static void updateAll();

  private:
    byte id;
    byte pin;
    byte pressedValue;
    byte stableButtonState;
    byte lastButtonState;
    boolean updated;
    LEDControlType LEDControl;
    buttonType type;
    unsigned long debounceDelay;
    unsigned long holdDelay;
    unsigned long holdInterval;
    unsigned long holdSent;
    unsigned long lastDebounceTime;
    unsigned long downTime;

    static LitSwitch *buttons[];
    static byte buttonId;
};

#endif

