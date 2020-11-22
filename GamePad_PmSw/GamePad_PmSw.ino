//Test für Commits

// Gamepad, welches aus dem Projekt in PmSweng entstanden ist.
// Dieses Programm kann mit einem Arduino Micro oder einem
// Arduino Leonardo genutzt werden.
// Andere Mikrokontrollerboards mit einem AtMega 32u4
// Chip sollten auch funktionieren.
//
// Pin Layout:
//  2 = auf
//  3 = rechts
//  4 = runter
//  5 = links
//  6 = a
//  7 = b
//  8 = x
//  9 = y
// 10 = start
// 11 = select
//
// David Feldmann
// 22.09.2020
//--------------------------------------------------------------------

#include <Joystick.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  6, 0,                  // Anzahl Buttons, Anzahl Hat Buttons
  true, true, false,     // Lx, Ly, Lz Achsen
  false, false, false,   // Rx, Ry, Rz Achsen
  false, false,          // Seitenruder, Drosselklappe
  false, false, false);  // Gaspedal, Bremspedal, Lenkung

void setup()
{
  // Alle Buttons als Input mit internem Pullup
  for(int i=2;i<=12;i++)
    pinMode( i, INPUT_PULLUP);

  // Joystick Library initialisieren
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);
}

int letzterZustand[10] = {0,0,0,0,0,0,0,0,0,0};

void loop() {

  // 
  for (int index = 0; index <= 9; index++)
  {
    int jetzigerZustand = !digitalRead(index + 2);
    if (jetzigerZustand != letzterZustand[index])
    {
      switch (index) {
        case 0: // auf
          if (jetzigerZustand == 1) {
            Joystick.setYAxis(-1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 1: // rechts
          if (jetzigerZustand == 1) {
            Joystick.setXAxis(1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        case 2: // runter
          if (jetzigerZustand == 1) {
            Joystick.setYAxis(1);
          } else {
            Joystick.setYAxis(0);
          }
          break;
        case 3: // links
          if (jetzigerZustand == 1) {
            Joystick.setXAxis(-1);
          } else {
            Joystick.setXAxis(0);
          }
          break;
        case 4: // a
          Joystick.setButton(0, jetzigerZustand);
          break;
        case 5: // b
          Joystick.setButton(1, jetzigerZustand);
          break;
        case 6: // x
          Joystick.setButton(2, jetzigerZustand);
          break;
        case 7: // y
          Joystick.setButton(3, jetzigerZustand);
          break;
        case 8: // start
          Joystick.setButton(4, jetzigerZustand);
          break;
        case 9: // select
          Joystick.setButton(5, jetzigerZustand);
          break;
      }
      letzterZustand[index] = jetzigerZustand;
    }
  }

  delay(10);
}

