/*
||
|| This is a slightly modified version of Alexander Brevig's FiniteStateMachine.cpp library for Arduino.
|| It has been modified by Zane Lewin
||
||The original source code can be found at https://playground.arduino.cc/Code/FiniteStateMachine/
||
|| Reproduced under the GNU Lesser General Public License, with the original license notice placed below
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU Lesser General Public
|| | License as published by the Free Software Foundation; version
|| | 2.1 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | Lesser General Public License for more details.
|| |
|| | You should have received a copy of the GNU Lesser General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
|| #
||
*/


#ifndef PrinterFSM_h
#define PrinterFSM_h

#include "Arduino.h"

class State{
  public:
    State( void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)()); // Constructor to assign function pointers

    void enter();
    void update();
    void exit();
	
	bool operator == (const State &s1);
	bool operator != (const State &s1);
    
  private:
    void (*userEnter)();
    void (*userUpdate)();
    void (*userExit)();
  
};


class FiniteStateMachine{
  public:
    FiniteStateMachine(State& current);
    FiniteStateMachine& update();
    FiniteStateMachine& transitionTo(State& state);
	State& getCurrentState();
    unsigned long timeInCurrentState();
	void resetTimeInCurrentState();
    
  private:
    FiniteStateMachine& transition(State& state);

    unsigned long stateChangeTime;
    State* currentState;
    State* nextState;
};
  

#endif
