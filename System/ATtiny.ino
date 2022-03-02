// C++ code
int ledR1=0,ledR2=1,reset=3,buzzer=4;
void setup()
{
  pinMode(reset,INPUT);
  pinMode(ledR1,OUTPUT);
  pinMode(ledR2,OUTPUT);
  pinMode(buzzer,OUTPUT);
  
}
void lamp()
{
  
   digitalWrite(ledR1,1);
  digitalWrite(ledR2,1);
  digitalWrite(buzzer,1);
}
void resetSys()
{
   digitalWrite(ledR1,0);
  	digitalWrite(ledR2,0);
    digitalWrite(buzzer,0);
  
}
void loop()
{
    lamp();
  if(digitalRead(reset))
    resetSys();

}