//#include <LiquidCrystal.h>
//LiquidCrystal lcd(13, 12, 5, 4, 3, 2);
#include  <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int Pwmpin=9;//Pwm Output Pin
int Fchange= A0;//Frequency change through Potentiometer

int ena_pin = 12;
int dir_pin = 11;
int pul_pin = 9;

//int Button=1;//Button to change the frequency
void setup(){
  lcd.init();
  lcd.backlight();
  
  pinMode(ena_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(pul_pin, OUTPUT);

  //pinMode(Button, INPUT);//Button as Input
  TCCR1A=_BV(COM1A1)|_BV(COM1B1);//Non-inverted Mode
  TCCR1B=_BV(WGM13)|_BV(CS11);//Prescalar 8
  lcd.setCursor(0, 0);//Lcd Coulomb 0 Row 1
  lcd.print("Pwm Period = 50%");

  digitalWrite(ena_pin, LOW); // ALTO DESHABILITA / BAJO HABILITA
  digitalWrite(dir_pin, LOW); // ALTO IZQUIERDA / BAJO DERECHA
}

float freq=0;
float count=10000,countt=0,Pinput=0;

void loop(){
  ICR1=count;//variable Frequency
  countt=2*8*count;
  freq= int(16000000/countt);
  OCR1A=int(count/2);
  lcd.setCursor(0, 1);//Lcd Coulomb 0 Row 2
  lcd.print("Pwm Freq =");
  lcd.print(freq);
  
  count=10000;
  Pinput=analogRead(A0);//Read input value
  Pinput=(Pinput/0.0113);
  count=count+Pinput;
  if(count>=100000){
      count=10000;
  }
}
