//int pinLDR = 25;
#define PIN_LDR 25
#define PIN_LM35 34

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  //Serial.println(analogRead(PIN_LDR));
  Serial.println(analogRead(PIN_LM35)*0.1221);//Grados
  delay(100);
}
