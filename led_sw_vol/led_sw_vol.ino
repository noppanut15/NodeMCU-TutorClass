#define VOL A0
#define SW D0
#define RED D1
#define GREEN D2
#define BLUE D3
void setup() {
  // put your setup code here, to run once:
  pinMode(VOL, INPUT);
  pinMode(SW, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int vol = analogRead(VOL);
  analogWrite(RED, vol/4);
  analogWrite(GREEN, vol/4);
  analogWrite(BLUE, vol/4);
//  delay(500);
  if(!digitalRead(SW)){
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
  }
}
