/// @file 
//! \brief Main arduino programm including the parameter-setup
//--------------------------------------------------------------------
// Pin Layout:
//  2 = up
//  3 = right
//  4 = down
//  5 = left
//  6 = a
//  7 = b
//  8 = x
//  9 = y
// 10 = start
// 11 = select
//
// Lea Bernhardsgrütter
// 06.12.2020
///--------------------------------------------------------------------
#include <Joystick.h>                                                       //for all joystick button functions
#include <TimerOne.h>                                                       //for time interrupts

                                                                            ///Enum of all used buttons
namespace Button
{
                                                                           //! \brief Set gamepad button names
  enum Button                                                              
  {
   up,
   down,
   left,
   right,
   a,
   b,
   x,
   y,
   start,
   select,
   numberOfButtons
  };
}
namespace ButtonPin                                                         ///  Allocates button names to pins
{
  enum ButtonPin                                                            //!  Allocates button names to pins
  {
   up = 2,
   down = 4,
   left = 5,
   right = 3,
   a = 6,
   b = 7,
   x = 8,
   y = 9,
   start = 10,
   select = 11
  };
}

const int getButtonPin[Button::numberOfButtons] =                          //!built a array with all states of buttons
{                                                                          // keep the same order as enum ButtonPin
  ButtonPin::up,
  ButtonPin::down,
  ButtonPin::left,
  ButtonPin::right,
  ButtonPin::a,
  ButtonPin::b,
  ButtonPin::x,
  ButtonPin::y,
  ButtonPin::start,
  ButtonPin::select
};

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,        
  6, 0,                                                                     //number of buttons, nuber of hat switch
  true, true, false,                                                        //Lx, Ly, Lz axis
  false, false, false,                                                      //no Rx, Ry, Rz axis
  false, false,                                                             //no rudder, throttle
  false, false, false);                                                     //no accelerator, brake, steering


void setup()
{
  // put your setup code here, to run once:
  for (int i = 0; i < Button::numberOfButtons; ++i)
  {
    pinMode(getButtonPin[i], INPUT_PULLUP);                                 //!all pins are setup for buttons as input with pullup  
  }
  
  // Joystick Library initialisieren
  Joystick.begin();                                                         //start autosend States
  Joystick.setXAxisRange(-1, 1);                                            //set range x axis
  Joystick.setYAxisRange(-1, 1);                                            //set range y axis

  Timer1.initialize(1000);                                                  //initialize timer1, and set a 1 millisecond period
  Timer1.attachInterrupt(callback);                                         //attaches callback() as a timer overflow interrupt
}

void loop()                                                                 /// emty runtime loop, the arduino waits for interrupt
{
 
}

void callback()                                                             /// the Interrupt-routine in case of a pressed button
{
  static int presentState[Button::numberOfButtons] = {0};                   //present states saved for every button
  static int lastState[Button::numberOfButtons] = {0};                      //last states saved for every button
  static unsigned int lockStateChange[Button::numberOfButtons] = {0};       //used for software debouncing
  enum {lockTime = 10};

  for(int i = 0; i < Button::numberOfButtons; ++i)
  {
    presentState[i] = !digitalRead(getButtonPin[i]);                        //active low buttons
  }

  for(int i = 0; i < Button::numberOfButtons; ++i)
  {
    if(lockStateChange[i])                                                  //check if a button is locked because set during the lock time
    {
       --lockStateChange[i]; 
    } 
    else if (lastState[i]!=presentState[i])                                 //check which button was set during the lock time -> software debouncing
    {
      switch(i)
      {
        case Button::up:
          Joystick.setYAxis(0-presentState[i]);                             //set button up and autosend
          break;
        case Button::down:
          Joystick.setYAxis(0+presentState[i]);                             //set button down and autosend
          break;
        case Button::left:
          Joystick.setXAxis(0-presentState[i]);                             //set button left and autosend
          break;
        case Button::right:
          Joystick.setXAxis(0+presentState[i]);                             //set button right and autosend
          break;
        case Button::a:
          Joystick.setButton(0,presentState[i]);                            //set button a and autosend
          break;
        case Button::b:
          Joystick.setButton(1,presentState[i]);                            //set button b and autosend
          break;
        case Button::x:
          Joystick.setButton(2,presentState[i]);                            //set button x and autosend
          break;
        case Button::y:
          Joystick.setButton(3,presentState[i]);                            //set button y and autosend
          break;
        case Button::start:
          Joystick.setButton(4,presentState[i]);                            //set button start and autosend
          break;
        case Button::select:
          Joystick.setButton(5,presentState[i]);                            //set button select und autosend
          break;
        default:
          break;
      }
      lastState[i]=presentState[i];                                         //present state becomes last state
      lockStateChange[i] = lockTime - 1;                                    //set lock time afte set a button
    }
  }
}
