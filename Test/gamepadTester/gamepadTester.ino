


///--------------------------------------------------------------------           
/// @file
/// \brief Hardwaretest für das Gamepad aus dem PmSwEng-Projekt                   
///
/// Nachfolgend die Funktionen:                                                   \n
/// u - up                                                                        \n
/// d - down                                                                      \n
/// l - left                                                                      \n
/// r - right                                                                     \n
/// a - a                                                                         \n
/// b - b                                                                         \n  
/// x - x                                                                         \n
/// y - y                                                                         \n
/// s - start                                                                     \n
/// S - select                                                                    \n  
/// 1 - automatische testsequenz                                                  \n  
/// Jedes Kommando emuliert einen Tastendruck für zwei Sekunden.                  \n
///                                                                               \n
/// David Feldmann                                                                \n
/// 09.12.2020                                                                     
//--------------------------------------------------------------------           

/// The buffer stores the recived strng
String buff;

/// configure the arduino output-pins and the serial port
void setup()                                        
{
  for(int i=2; i<12; i++)
  {
    pinMode(i,OUTPUT);
    digitalWrite(i,HIGH);
  }
  Serial.begin(9600);
}

///\brief emulates a active button for 2sec.
///\param pinNumber Which pin schould be tested
void emulateButton(byte pinNumber)
{
  digitalWrite(pinNumber,LOW);
  delay(2000);
  digitalWrite(pinNumber,HIGH);
}
///\brief The main loop of the Arduino
///
/// recives the command via seral port and excecutes the corresponding case.
///
///
void loop()
{
  if(Serial.available()>0)
  {
     buff=Serial.readStringUntil('\n');   
     Serial.println(buff);
     switch(buff[0])
     {
       case 'u':
         Serial.println("'up' button pressed");
         emulateButton(2);
         break;
       case 'r':
         Serial.println("'right' button pressed");
         emulateButton(3);
         break;
       case 'd':
         Serial.println("'down' button pressed");
         emulateButton(4);
         break;
       case 'l':
         Serial.println("'left' button pressed");
         emulateButton(5);
         break;
       case 'a':
         Serial.println("'a' button pressed");
         emulateButton(6);
         break;
       case 'b':
         Serial.println("'b' button pressed");
         emulateButton(7);
         break;
       case 'x':
         Serial.println("'x' button pressed");
         emulateButton(8);
         break;
       case 'y':
         Serial.println("'y' button pressed");
         emulateButton(9);
         break;
       case 's':
         Serial.println("'start' button pressed");
         emulateButton(10);
         break;
       case 'S':
         Serial.println("'select' button pressed");
         emulateButton(11);
         break;
       case '1':
         Serial.println("automatic test mode");
         Serial.println("Pushing each button for 2 seconds in their defined order");
         for(int i=2; i<12;i++)
         {
           Serial.print(".");
           emulateButton(i);
         }
         Serial.println();
         Serial.println("done");
         break;
       default:
         Serial.println("Invalid command received.");
         Serial.println("Valid commands:");
         Serial.println("u - up");
         Serial.println("d - down");
         Serial.println("l - left");
         Serial.println("r - right");
         Serial.println("a - a");
         Serial.println("b - b");
         Serial.println("x - x");
         Serial.println("y - y");
         Serial.println("s - start");
         Serial.println("S - select");
         Serial.println("1 - automatic testsequence");
         Serial.println("Each command will cause a button to be emulated for 2 seconds.");
         break;
     }
  }
}
