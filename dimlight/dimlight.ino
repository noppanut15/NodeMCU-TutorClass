#define VOL A0
#define LED D0
void setup() {
  // put your setup code here, to run once:
  pinMode(VOL, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
}
int input = 0;
void loop() {
  // put your main code here, to run repeatedly:
  input = analogRead(VOL);
  analogWrite(LED, input/4);
  Serial.println(input);
 // delay(1000);

}
