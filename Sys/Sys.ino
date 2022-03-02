
// include the library code:
#include <LiquidCrystal.h>
#include<EEPROM.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {A5, A4, A3, A2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A1, 10, 9}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int but1=7,led=8,alarm=6,emergency=A0;
char password[5];
int tryCase=2;
bool test,case2=true;
bool isCorrect()//fucntion which tests password is valid or not
{
  int j;
  test=true;
   lcd.print("Enter Password");
    delay(1000);
    lcd.clear();
  for(int i=0,j=0;i<4;i++,j++)
  {
    if(EEPROM.read(i)!=keypad.waitForKey())
    test=false;
     lcd.setCursor(j,0);
    lcd.print('*');
  }
  lcd.clear();
  return test;
}
void createNewPassword()
{
  lcd.setCursor(2,0);
    lcd.print("Enter Default");
    lcd.setCursor(3,1);
    lcd.print("Password");
    delay(1500);
    lcd.clear();
  int z;
  for(int i=0,z=0;i<4;i++,z++)
  {
    password[i]=keypad.waitForKey();
    lcd.setCursor(z,0);
    lcd.print('*');
    EEPROM.update(i,password[i]);
  }
  lcd.clear();
  lcd.print("Password has ");
  lcd.setCursor(0,1);
  lcd.print(" been Saved");
  delay(1500);
  lcd.clear();
}
void openSystem()
{
    while(1)
    {
      if(digitalRead(!but1))
      {
      lcd.print("Enter Password");
      delay(1000);
      lcd.clear();
      break;
      }
    }
    if(isCorrect())
      getVerified();
   else
    {
      while(tryCase>0)
       {
      lcd.print("Try Again");
        delay(1500);
        lcd.clear();
        tryCase--;
      if(isCorrect())
      getVerified();
   
        else
          if(tryCase==0)
            breakInto();
       }   
   }
}
void breakInto()
{
   digitalWrite(alarm,1);
        delay(600000);
       
}
void getVerified()
{
  lcd.setCursor(0,0);
      lcd.print("Door is Opened");
    digitalWrite(led,1);
      delay(1500);
  digitalWrite(led,0);
      lcd.clear();
      tryCase=2;
       exit(0);
}
void setup()   
{
  lcd.begin(16, 2);
  pinMode(but1,INPUT);
  pinMode(led,OUTPUT);
  pinMode(alarm,OUTPUT);
  pinMode(emergency,INPUT);
  if(EEPROM.read(0)==NULL)
  createNewPassword();
  else
  {
    for(int i=0;i<4;i++)
    password[i]=EEPROM.read(i);
  }
}
void loop()   
{
 if(digitalRead(but1) && case2)
 openSystem();
  if(digitalRead(emergency)==1)
  {
    breakInto();
    case2=false;
  }
  
}

// 430 LE
