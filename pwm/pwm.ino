int ena_pin = 12;
int dir_pin = 11;
int pul_pin = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(ena_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(pul_pin, OUTPUT);

  digitalWrite(ena_pin, LOW); // ALTO DESHABILITA / BAJO HABILITA
  digitalWrite(dir_pin, LOW); // ALTO IZQUIERDA / BAJO DERECHA
}

int tiempo = 1000; // 1.5 // 5200

void loop() {
//  tiempo = map(analogRead(0), 0, 1023, 10, 1000);
  // put your main code here, to run repeatedly:
  digitalWrite(pul_pin, HIGH);
  delayMicroseconds(tiempo);
  digitalWrite(pul_pin, LOW);
  delayMicroseconds(tiempo);
}
