#define SW D0
#define LED D1
void setup() {
  // put your setup code here, to run once:
  pinMode(SW, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(!digitalRead(SW)){
    digitalWrite(LED, HIGH);
  }
  digitalWrite(LED, LOW);
}
