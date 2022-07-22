
String readString;
#include <Stepper.h>
const int stepsPerRevolution = 1000; 
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);
int menu =0;
int rpm = 0;
int maxrpm = 250;
int maxstroke = 3;
int strokelength = 1;//default
//String c;
void setup() {
    myStepper.setSpeed(100);
  // initialize the serial port:
  Serial.begin(9600);
  logo();
  callmenu();
}
char input = 0;
void loop() {
  if (Serial.available() > 0) {  
    input = Serial.read();
  switch (input) {
//-------------------------MAXIMUM FREQUENCY     
      case '1':
       Serial.println(">> Motor RPM = 250");
       Serial.println(">> Frequncy = 1hz");
       delay(100);
        while( input != '0'){
            input = Serial.read();
            myStepper.setSpeed(250);
            myStepper.step(stepsPerRevolution); // forward
            myStepper.step(-stepsPerRevolution); //backward
        }
        stopmessage();
      break;
 //-------------------------LOWEST FREQUENCY     
      case '2':
            Serial.println(">> Motor RPM = 50");
            //Serial.println(">> Frequncy = 1/2 hz");
        while( input != '0'){
            input = Serial.read();
            myStepper.setSpeed(100);
            myStepper.step(stepsPerRevolution); // forward
            myStepper.step(-stepsPerRevolution); //backward
       }
       stopmessage();
      break;
  //--------------------------Custom speed
      case '3':
      Serial.println("***RPM RANGE BETWEEN 50 RPM TO 250 RPM***");
      readinputrpm();
      delay(200);
       while( input != '0') 
       {
            input = Serial.read();
            myStepper.setSpeed(rpm);
            myStepper.step(stepsPerRevolution); // forward
           // myStepper.step(stepsPerRevolution); // forward
            //delay(200);
            //myStepper.step(-stepsPerRevolution); //backward
            myStepper.step(-stepsPerRevolution); //backward
       }
       rpm=0;
       stopmessage();
      break;
   //----------------------------Custom stroke length and rpm
      case '4':
      space();
      Serial.println("********************************************************");
      delay(200);
      Serial.println(">> Enter desired Stroke length and rpm");
      Serial.println(">> Enter Stroke Legnth");
      readstrokelength();
      delay(1000);
      Serial.println(">> Enter RPM");
      readinputrpm();
      delay(200);
      myStepper.setSpeed(rpm);
      while( input != '0')
      {
      input = Serial.read();
      stroke();
      }
       rpm=0;
      stopmessage();
      break;
    //---------------------------reposition actuator
    case '5':
     space();
     delay(500);
     Serial.println("*********************************************************");
     Serial.println(">> Actuator speed set to 25 RPM");
     delay(500);
     Serial.println(">> NOTE :- At this speed motor will not make any noise");
     Serial.println("          so be while careful repositioning the actuator");
     Serial.println("          Actuator plate should be in the middle near");
     Serial.println("          25 cm mark on the guide");
     delay(5000);
     Serial.println(">> To change the direction of movement CHANGE THE PIN CONNECTION TO OPPOSITE");
     Serial.println(">> Positioning will start in 5 seconds");
     Serial.println(">> Press Zero (0) when actuator reaches desired position");
     delay(5000);
     Serial.println(">> Movement started");
     myStepper.setSpeed(50);
     while( input != '0')
      {
      input = Serial.read();
      myStepper.step(stepsPerRevolution);
      }
      rpm=0;
      stopmessage();
    break;
    //---------------------------How to use
      case '6':
      Serial.println(">> Update coming soon Press RESET to go back");
      
      break;
      //---------------------------About
      case '7':
      Serial.println(">> Wave tank built by Shubham Bhatt(NA841) NAVAL ARCH. Batch 8 under guidance of Dr. Shameem B M");
      
      break;
      default:
      Serial.println(">> Invalid option");
      break;
    } // end: switch (rx_byte)
}
}
void callmenu()
{
        
        Serial.println("********************* MENU *****************************");
        Serial.println("                1. Actuate at Maximum frequency");
        Serial.println("                2. Actuate at Lowest frequency");
        Serial.println("                3. Enter Custom RPM");
        Serial.println("                4. Enter Stroke length and RPM") ;
        Serial.println("                5. Reposition Actuator") ;
        Serial.println("                6. How to use") ;
        Serial.println("                7. About") ;
        Serial.println("*********************************************************");
        Serial.println("***INPUT 0 (zero) anytime to STOP ACTUATOR from RUNNIG***");
}
void readinputrpm()
{
   Serial.println(">> waiting for input...");
   while(Serial.available() == 0) { }
   String c = Serial.readString();  //gets one byte from serial buffer
   Serial.println(">> Input recieved = "+ c);
   delay(500);  //slow looping to allow buffer to fill with next character
   Serial.println(c);  //so you can see the captured string 
   int n = c.toInt();
   if ( n >=50 && n <= maxrpm)
   {
   delay(200);
    rpm = n;
   }
   if ( n < 50 || n > maxrpm)
   {
    warning();  
}
}
void stopmessage(){
  Serial.println("***Actuator Stopped if not press RESET on microcontoller***");
  Serial.println();
  callmenu();
}
void logo()
{
Serial.println("db   d8b   db  .d8b.  db    db d88888b      d888888b  .d8b.  d8b   db db   dD       db     .d88b.");  
Serial.println("88   I8I   88 d8' `8b 88    88 88'          `~~88~~' d8' `8b 888o  88 88 ,8P'      o88    .8P  88."); 
Serial.println("88   I8I   88 88ooo88 Y8    8P 88ooooo         88    88ooo88 88V8o 88 88,8P         88    88  d'88"); 
Serial.println("Y8   I8I   88 88~~~88 `8b  d8' 88~~~~~         88    88~~~88 88 V8o88 88`8b         88    88 d' 88"); 
Serial.println("`8b d8'8b d8' 88   88  `8bd8'  88.             88    88   88 88  V888 88 `88.       88 db `88  d8' ");
Serial.println(" `8b8' `8d8'  YP   YP    YP    Y88888P         YP    YP   YP VP   V8P YP   YD       VP VP  `Y88P'");  
}
void warning()
{
 Serial.println("");
 Serial.println("             ___________    ____                             ******WARNING******");
 Serial.println("      ______/   \\__//   \__/____\\\\                            INVALID INPUT RANGE");
 Serial.println("    _/   \_/  :           //____ \\\\          ");
 Serial.println("   /|      :  :  ..      /        \\      ");
 Serial.println("  | |     ::     ::      \\        /        You will damage actuator please follow instructions carefully"); 
 Serial.println("  | |     :|     ||     \\ \\______/ ");
 Serial.println("  | |     ||     ||      |\\  /  | ");
 Serial.println("   \\|     ||     ||      |   / | \\ ");
 Serial.println("    |     ||     ||      |  / /_\ \\ ");
 Serial.println("    | ___ || ___ ||      | /  /   \\ ");
 Serial.println("     \\_-_/  \\_-_/ | ____ |/__/      \\ ");
 Serial.println("                  _\\_--_/    \\\      / ");
 Serial.println("                 /____             / ");
 Serial.println("                /     \\           / ");
 Serial.println("                \\______\\_________/");
while(1 > 0)
{
}
}
void space()
{
  for(int i=0;i<=5;i++)
  Serial.println(" ");
}
void readstrokelength()
{
Serial.println(">> waiting for input...");
   while(Serial.available() == 0) { }
   String c = Serial.readString();  //gets one byte from serial buffer
   Serial.println(">> Input recieved = "+ c);
   delay(500);  //slow looping to allow buffer to fill with next character
   Serial.println(c);  //so you can see the captured string 
   int n = c.toInt();
   if ( n >= 1 && n <= maxstroke)
   {
   delay(200);
    strokelength = n;
   }
   if ( n < 1 || n > maxstroke)
   {
    warning();  
}
}
void stroke()
{
  for(int i=1;i<=strokelength;i++)
  {
    myStepper.step(stepsPerRevolution);
  }
  for(int j=1;j<=strokelength;j++)
  {
    myStepper.step(-stepsPerRevolution);
  }
  }



