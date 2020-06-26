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


#include "Arduino.h"
#include "PrinterFSM.h"


State::State( void (*enterFunction)(), void (*updateFunction)(), void (*exitFunction)()){
  userEnter = enterFunction;
  userUpdate = updateFunction;
  userExit = exitFunction; 
}

void State::enter(){
  if(userEnter){
    userEnter();
  }
}


void State::update(){
  if(userUpdate){
    userUpdate();
  }
}

void State::exit(){
  if(userExit){
    userExit();
  }
}

bool State::operator == (const State &s1){
	return (this == &s1);
}

bool State::operator != (const State &s1){
	return !(this == &s1);
}


FiniteStateMachine::FiniteStateMachine(State& current){
  currentState = nextState = &current;
  stateChangeTime = 0;
}


FiniteStateMachine& FiniteStateMachine::update(){
  if (currentState != nextState){
    transition(*nextState);
  }
  currentState->update();
  return *this;
}

FiniteStateMachine& FiniteStateMachine::transitionTo(State& state){
  nextState = &state;
//  stateChangeTime = millis();
  return *this;
}

unsigned long FiniteStateMachine::timeInCurrentState(){
  return (millis() - stateChangeTime);
}

State& FiniteStateMachine::getCurrentState(){
	return *currentState;
}

FiniteStateMachine& FiniteStateMachine::transition(State& state){
  currentState->exit();
  currentState = nextState = &state;
  currentState->enter();
  stateChangeTime = millis();
//  Serial.println(stateChangeTime);
  return *this;
}



void FiniteStateMachine::resetTimeInCurrentState(){
	stateChangeTime = millis();
}
