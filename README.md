# PMSwEng
Projekt zum Modul Projektmanagement und Softwareengineering an der RJ-Ost (HSR).

Ziel des Projekt ist es ein Gamepad zu erstellen, welches als Eingabegerät für Emulatoren und sonstigen Retrogames mit Gamepadunterstützung genutzt werden kann.

Das Gamepad besitzt über ein Steuerkreuz, vier Buttons (a, b, x, y) und je eine start und select Taste.

Als Mikrokontroller wird ein ATMega 32u4 verwendet. Mit leichten anpassungen sollte es aber auch auf dem ATMega 32u2 lauffäig sein.

Nachfolgend die Verdrahtung für einen Arduino Micro:

  2 = auf
  3 = rechts
  4 = runter
  5 = links
  6 = a
  7 = b
  8 = x
  9 = y
 10 = start
 11 = select
 
 Der Code nutzt die ArduinoJoystickLibrary.
 Diese kann hier heruntergeladen werden:  https://github.com/MHeironimus/ArduinoJoystickLibrary