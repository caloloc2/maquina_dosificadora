void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  TCCR1A=0b00010000;
  TCCR1B=0b00011011;
  TCCR1C=0;
  ICR1=500; 
}

void loop() {
  ICR1= map(analogRead(0), 0, 1023, 10, 100);
  delay(10);
}
