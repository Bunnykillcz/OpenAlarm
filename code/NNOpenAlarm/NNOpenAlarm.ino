/*
 _____  ___  _____  ___        ________ __    ___      ___   _______  ___      _______           __     ___           __       _______  ___      ___       ________ ___  ___ ________ ___________ _______ ___      ___ 
(\"   \|"  \(\"   \|"  \      /"       |" \  |"  \    /"  | |   __ "\|"  |    /"     "|         /""\   |"  |         /""\     /"      \|"  \    /"  |     /"       |"  \/"  /"       ("     _   "/"     "|"  \    /"  |
|.\\   \    |.\\   \    |    (:   \___/||  |  \   \  //   | (. |__) :||  |   (: ______)        /    \  ||  |        /    \   |:        |\   \  //   |    (:   \___/ \   \  (:   \___/ )__/  \\__(: ______)\   \  //   |
|: \.   \\  |: \.   \\  |     \___  \  |:  |  /\\  \/.    | |:  ____/|:  |    \/    |         /' /\  \ |:  |       /' /\  \  |_____/   )/\\  \/.    |     \___  \    \\  \/ \___  \      \\_ /   \/    |  /\\  \/.    |
|.  \    \. |.  \    \. |      __/  \\ |.  | |: \.        | (|  /     \  |___ // ___)_       //  __'  \ \  |___   //  __'  \  //      /|: \.        |      __/  \\   /   /   __/  \\     |.  |   // ___)_|: \.        |
|    \    \ |    \    \ |     /" \   :)/\  |\|.  \    /:  |/|__/ \   ( \_|:  (:      "|     /   /  \\  ( \_|:  \ /   /  \\  \|:  __   \|.  \    /:  |     /" \   :) /   /   /" \   :)    \:  |  (:      "|.  \    /:  |
 \___|\____\)\___|\____\)    (_______/(__\_|_|___|\__/|___(_______)   \_______\_______)    (___/    \___\_______(___/    \___|__|  \___|___|\__/|___|    (_______/ |___/   (_______/      \__|   \_______|___|\__/|___|
                                                                                                                                                                                                                       
Made by Nikola Nejedlý
2021-2022 (c) NejedNiko.cz
With the use of Arduino IDE, made for Arduino NANO

   _____      _   _   _                 
  / ____|    | | | | (_)                
 | (___   ___| |_| |_ _ _ __   __ _ ___ 
  \___ \ / _ \ __| __| | '_ \ / _` / __|
  ____) |  __/ |_| |_| | | | | (_| \__ \
 |_____/ \___|\__|\__|_|_| |_|\__, |___/
                               __/ |    
                              |___/     
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//Your PASSWORD HERE: (example: 9856)
const int n1 = 9; //first  digit
const int n2 = 8; //second digit
const int n3 = 5; //third  digit
const int n4 = 6; //fourth digit

int delay_time_ms_enter = 8000; //the delay for a person to enter the room and enter the code safely
int delay_time_ms_leave = 8000; //the delay for a person to leave before the alarm starts
bool beep_during_entry_sequence = true; //if the buzzer should beep while counting down the entry

/*--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
  _____                                     
 |  __ \                                    
 | |__) | __ ___   __ _ _ __ __ _ _ __ ___  
 |  ___/ '__/ _ \ / _` | '__/ _` | '_ ` _ \ 
 | |   | | | (_) | (_| | | | (_| | | | | | |
 |_|   |_|  \___/ \__, |_|  \__,_|_| |_| |_|
                   __/ |                    
                  |___/                     
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//BUZZER
const int pinBuzz = 19;

//D6-D12 = keyboard
const int pinK1 = 12;
const int pinK2 = 11;
const int pinK3 = 10;
const int pinK4 = 9;
const int pinKA = 6;
const int pinKB = 7;
const int pinKC = 8;

//D2-D5 = display (leds) -> 0 = active
const int pinD1 = 5;
const int pinD2 = 4;
const int pinD3 = 3;
const int pinD4 = 2;

//A3 =  status
const int pinS0 = 17;

//A2 = SIREN OUTPUT
const int pinSiren = 16;

//A0 = SENSORS INPUT
const int pinSensors = 14;

//code digit control
int digitsEntered = 0;
bool d1correct = false;
bool d2correct = false;
bool d3correct = false;
bool d4correct = false;

bool buttonPressed = false;
bool isOff = true;

int row = 0;
int rowcheck = 0;

bool AlertPending = false;
bool AlertActive = false;
bool AlarmPending = false;
bool AlarmActive = false;

unsigned long runtime = 0;
unsigned long ALERT_TIME_S = millis();

void setup() {
  pinMode(pinKA,      INPUT);
  pinMode(pinKB,      INPUT);
  pinMode(pinKC,      INPUT);
  pinMode(pinK1,      OUTPUT);
  pinMode(pinK2,      OUTPUT);
  pinMode(pinK3,      OUTPUT);
  pinMode(pinK4,      OUTPUT);

  digitalWrite(pinK1, LOW);
  digitalWrite(pinK2, LOW);
  digitalWrite(pinK3, LOW);
  digitalWrite(pinK4, LOW);
 
  pinMode(pinD1,     OUTPUT);
  pinMode(pinD2,     OUTPUT);
  pinMode(pinD3,     OUTPUT);
  pinMode(pinD4,     OUTPUT);
  
  digitalWrite(pinD1, HIGH);
  digitalWrite(pinD2, HIGH);
  digitalWrite(pinD3, HIGH);
  digitalWrite(pinD4, HIGH);
  
  pinMode(pinBuzz,    OUTPUT);
  pinMode(pinS0,      OUTPUT);
  pinMode(pinSiren,   OUTPUT);
  pinMode(pinSensors, INPUT);
  
  digitalWrite(pinS0,    LOW);
  digitalWrite(pinBuzz,  LOW);
  digitalWrite(pinSiren, LOW);
  
  Serial.begin(9600);
}

void loop() {

if(AlarmActive)
{
  //Serial.print("Sensor: ");
  //Serial.println(digitalRead(pinSensors)); //pin active on release
  if(digitalRead(pinSensors) == HIGH)
  {
    if(AlertPending == false)
    {
      if(beep_during_entry_sequence)
        Beep(150);
      
      ALERT_TIME_S = millis();
    }
    AlertPending = true;
  }

  if(beep_during_entry_sequence)
    if(AlertPending == true && AlertActive == false)
    {
      if(runtime % 3000 >= 2950) 
        Beep(50);
    }
  
  digitalWrite(pinK1, LOW);
  digitalWrite(pinK2, LOW);
  digitalWrite(pinK3, LOW);
  digitalWrite(pinK4, LOW);
  
  if(buttonPressed == false)
  {
    switch(row)
    {
      case 0:
      digitalWrite(pinK1, HIGH);
        if(digitalRead(pinKA) == HIGH)//1
          {
            buttonPressed = true;
            pressedNewDigit(1, digitsEntered++);
          }
        else
        if(digitalRead(pinKB) == HIGH)//2
          {
            buttonPressed = true;
            pressedNewDigit(2, digitsEntered++);
          }
        else
        if(digitalRead(pinKC) == HIGH)//3
          {
            buttonPressed = true;
            pressedNewDigit(3, digitsEntered++);
          }
        break;
      case 1:
      digitalWrite(pinK2, HIGH);
        if(digitalRead(pinKA) == HIGH)//4
          {
            buttonPressed = true;
            pressedNewDigit(4, digitsEntered++);
          }
        else
        if(digitalRead(pinKB) == HIGH)//5
          {
            buttonPressed = true;
            pressedNewDigit(5, digitsEntered++);
          }
        else
        if(digitalRead(pinKC) == HIGH)//6
          {
            buttonPressed = true;
            pressedNewDigit(6, digitsEntered++);
          }
        break;
      case 2:
      digitalWrite(pinK3, HIGH);
        if(digitalRead(pinKA) == HIGH)//7
          {
            buttonPressed = true;
            pressedNewDigit(7, digitsEntered++);
          }
        else
        if(digitalRead(pinKB) == HIGH)//8
          {
            buttonPressed = true;
            pressedNewDigit(8, digitsEntered++);
          }
        else
        if(digitalRead(pinKC) == HIGH)//9
          {
            buttonPressed = true;
            pressedNewDigit(9, digitsEntered++);
          }
        break;
      case 3:
      digitalWrite(pinK4, HIGH);
        if(digitalRead(pinKA) == HIGH)//#
          {
            buttonPressed = true;
            Serial.println("# (Cancel/Reset)");
            digitsEntered = 0;
            Beep(30);
            delay(30);
            Beep(30);
            delay(30);
            Beep(30);
            delay(30);
            Beep(30);
            delay(300);
          }
        else
        if(digitalRead(pinKB) == HIGH)//0
          {
            buttonPressed = true;
            pressedNewDigit(0, digitsEntered++);
          }
        else
        if(digitalRead(pinKC) == HIGH)//*
          {
            buttonPressed = true;
            Serial.println("* (OK/Enter)");
            
            if(digitsEntered >= 4)
              if(checkPassword() == true)
              {
                AlarmActive = false;
                Serial.println("<< ALARM DEACTIVATED >>");
                digitsEntered = 0;
                Beep(50);
                delay(50);
                Beep(50);
                delay(300);
                if(AlertActive || AlertPending)
                {
                  Serial.println("<< INTRUDER ALERT DEACTIVATED >>");
                  digitalWrite(pinSiren, LOW);
                  AlertActive  = false;
                  AlertPending = false;
                }
              }
              else
              {
                Beep(150);
                digitsEntered = 0;
              }
          }
        break;
    }
    rowcheck = 0;
  }
  else
  {
    switch(rowcheck)
    {
      case 0:
      digitalWrite(pinK1, HIGH);
        if(digitalRead(pinKA) == HIGH || digitalRead(pinKB) == HIGH || digitalRead(pinKC) == HIGH)//1,2,3
          {
            isOff = false;
          }
        break;
      case 1:
      digitalWrite(pinK2, HIGH);
        if(digitalRead(pinKA) == HIGH || digitalRead(pinKB) == HIGH || digitalRead(pinKC) == HIGH)//4,5,6
          {
            isOff = false;
          }
        break;
      case 2:
      digitalWrite(pinK3, HIGH);
        if(digitalRead(pinKA) == HIGH || digitalRead(pinKB) == HIGH || digitalRead(pinKC) == HIGH)//7,8,9
          {
            isOff = false;
          }
        break;
      case 3:
      digitalWrite(pinK4, HIGH);
        if(digitalRead(pinKA) == HIGH || digitalRead(pinKB) == HIGH || digitalRead(pinKC) == HIGH)//#,0,*
          {
            isOff = false;
          }
        break;
    }
    rowcheck++;
    if(rowcheck >= 4 && isOff == true)
      buttonPressed = false;
    else
    if(rowcheck >= 4)
    {
      rowcheck = 0;
      isOff = true;
    }
  }
  
  lightUp(digitsEntered);
  
  row++;
  if(row >= 4)
    row = 0;

    //blinking-active = yes
  if(runtime % 3000 >= 2000 || AlarmPending == true || AlertPending == true) 
    digitalWrite(pinS0, LOW);
  else
    digitalWrite(pinS0, HIGH);

  }
  else
  {
    digitalWrite(pinK4, HIGH);
      if(digitalRead(pinKC) == HIGH)//#,0,*
        {
          AlarmPending = true;
          Serial.println("<< ALARM SET >>");
          Beep(50);
          delay(50);
          Beep(50);
          delay(50);
          Beep(50);
          ALERT_TIME_S = millis();
        }
    //blinking-active = no
    digitalWrite(pinS0, HIGH); 
  }

  runtime = millis();
  
  //Leave the room - timer
  if(AlarmPending == true)
  {
    //Serial.print("TIME: ");
    //Serial.println(runtime - ALERT_TIME_S);
    Beep(70);
    if(runtime - ALERT_TIME_S >= delay_time_ms_leave)
    {
      for(int i = 10; i > 0; i--)
      { 
        delay(50);
        Beep(50);
      }
      AlarmPending = false;
      AlarmActive = true;
      Serial.println("<< ALARM ACTIVATED >>");
    }
    delay(430);
    //IF CANCELLED
    digitalWrite(pinK4, HIGH);
    if(digitalRead(pinKA) == HIGH) // Cancel button
      {
        delay(10);
        Beep(100);
        delay(50);
        Beep(100);
        AlarmPending = false;
        AlarmActive = false;
      }
  }
  //Enter the room - timer
  if(AlertPending == true)
  {
    //Serial.print("TIME: ");
    //Serial.println(runtime - ALERT_TIME_S);
    if(runtime - ALERT_TIME_S >= delay_time_ms_enter)
    {
      Beep(150);
      AlertPending = false;
      AlertActive = true;
      Serial.println("<< INTRUDER ALERT >>");
      digitalWrite(pinSiren, HIGH);
    }
  }
}

void pressedNewDigit(int digit, int id)
{
  if(id < 4)
  {
    if(id == 0)
      if(digit == n1)
      {
        d1correct = true;
        Serial.println("1.OK");
      }
      else
        d1correct = false;
    if(id == 1)
    if(digit == n2)
      {
        d2correct = true;
        Serial.println("2.OK");
      }
      else
        d2correct = false;
    
    if(id == 2)
    if(digit == n3)
      {
        d3correct = true;
        Serial.println("3.OK");
      }
      else
        d3correct = false;
      
    if(id == 3)
    if(digit == n4)
      {
        d4correct = true;
        Serial.println("4.OK");
      }
      else
        d4correct = false;
    
    Serial.println(digit);
    delay(100);
  }
  Beep(100);
}

void lightUp(int dEn)
{
  digitalWrite(pinD1, HIGH);
  digitalWrite(pinD2, HIGH);
  digitalWrite(pinD3, HIGH);
  digitalWrite(pinD4, HIGH);
  
  if(dEn >= 1)
    digitalWrite(pinD1, LOW);
  if(dEn >= 2)
    digitalWrite(pinD2, LOW);
  if(dEn >= 3)
    digitalWrite(pinD3, LOW);
  if(dEn >= 4)
    digitalWrite(pinD4, LOW);    
}

bool checkPassword()
{
  if(d1correct == true)
  if(d2correct == true)
  if(d3correct == true)
  if(d4correct == true)
  {
    Serial.println("Password OK");
    return true;
  }
  
  Serial.println("Password BAD");
  return false;
}

void Beep(int t)
{
    digitalWrite(pinBuzz, HIGH);
    delay(t);
    digitalWrite(pinBuzz, LOW);
}
