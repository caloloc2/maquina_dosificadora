int ena_pin = 12;
int dir_pin = 11;
int pul_pin = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(ena_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(pul_pin, OUTPUT);

  digitalWrite(ena_pin, LOW); // ALTO DESHABILITA / BAJO HABILITA
  digitalWrite(dir_pin, LOW); // ALTO IZQUIERDA / BAJO DERECHA
}

int tiempo = 5; // 1.5 // 5

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(pul_pin, HIGH);
  delay(tiempo);
  digitalWrite(pul_pin, LOW);
  delay(tiempo);  
}
