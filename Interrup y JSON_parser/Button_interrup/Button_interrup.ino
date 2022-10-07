struct Button {
  const int PIN; //pin
  int numTimeButtonPressed; //veces que se ha presionado
  bool pressed; //presionado ahorita?
};

Button button1 = {33,0,false}; //pin 33, inicializando presionado 0 veces, por default no esta presionado
void IRAM_ATTR isr_button(){
  button1.numTimeButtonPressed += 1;
  button1.pressed = true;
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(button1.PIN, INPUT);
  attachInterrupt(button1.PIN, isr_button, RISING);//ejecuta funcion isr cuando baja el boton "sube"

}

void loop() {
  // put your main code here, to run repeatedly:
  if(button1.pressed == true){
    Serial.printf("El botón se ha presionado %u veces\n", button1.numTimeButtonPressed);
    button1.pressed = false; //lo regresas a false
  }
}
