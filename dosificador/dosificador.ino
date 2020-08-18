#include  <Wire.h>
#include  <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

int ena_pin = 12;
int dir_pin = 11;
int pul_pin = 10;

int pot = 0; // entrada potenciometro
int led = 13; // led de funcionamiento

int iniciar = 3; // boton iniciar
int modo_detener = 2; // boton seleccion de modo(cuando este detenido), detener
int pedal = 9; // para funcionamiento manual 

int velocidad = 0;
int inicio = 0;
int modo = 0; // 0: pedal, 1: manual

void setup(){
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
//  TCCR1A=0b01010000;
//  TCCR1B=0b00011011;
  TCCR1A=0b00010000;
  TCCR1B=0b00011011;
  TCCR1C=0;
  ICR1=0;
  
  pinMode(iniciar, INPUT_PULLUP);
  pinMode(modo_detener, INPUT_PULLUP);
  pinMode(pedal, INPUT_PULLUP);
  pinMode(led, OUTPUT); 

  pinMode(ena_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(pul_pin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(modo_detener), cambiar_modo, RISING);
  attachInterrupt(digitalPinToInterrupt(iniciar), estado_inicio, RISING);
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Modo: Pedal");
  lcd.setCursor(0, 1);
  lcd.print("Vel: 0");  
  lcd.setCursor(9, 1);
  lcd.print("ml/s");

  inicio = 0;
  digitalWrite(ena_pin, HIGH); // ALTO DESHABILITA / BAJO HABILITA
  digitalWrite(dir_pin, LOW); // ALTO IZQUIERDA / BAJO DERECHA
}

void estado_inicio(){  
  inicio = 1;
  digitalWrite(ena_pin, LOW); // ALTO DESHABILITA / BAJO HABILITA
}

void LCD_Textos(){  
  lcd.setCursor(6, 0);
  if (modo==0){
    lcd.print("Pedal     ");
  }else if (modo==1){
    lcd.print("Automatico");
  }

  lcd.setCursor(5, 1);
  lcd.print("    ");
  lcd.setCursor(5, 1);
  lcd.print(velocidad);
//  lcd.print((300-(velocidad-150))/10);
//  lcd.print(map(velocidad, 75, 100, 40, 2)); // 0.007 - 2280 ml/min => 0 - 40 ml/s
  lcd.setCursor(9, 1);
  lcd.print("ml/s");
}

void cambiar_modo(){
  if ((modo == 0)&&(inicio==0)){
    modo = 1;    
  }else if ((modo == 1)&&(inicio==0)){
    modo = 0;    
  }else{
    inicio = 0;// detiene
    digitalWrite(ena_pin, HIGH); // ALTO DESHABILITA / BAJO HABILITA
  }
  delay(300);
}

void loop(){
    velocidad = map(analogRead(pot), 0, 1023, 1, 100); // 29, 50    // 100, 450    // 100 - 3000
    LCD_Textos();

    if (inicio==1){
        if ((modo==1) || ((modo==0) && ((digitalRead(pedal) == LOW)))){
            ICR1 = velocidad;
        }else{
          ICR1 = 0;
        }
    }else{
      ICR1 = 0;
    }
    
    delay(200);
}
