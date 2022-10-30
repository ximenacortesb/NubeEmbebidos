const int PWM_PIN_LED = 32;
const int BUTTON_PIN = 33;
const int PWM_CHANNEL = 0; 
const int PWM_FREQ = 10000; //Hz
const int PWM_RESOLUTION = 8; //bits para generar señal resolution

int waveform = 0;
float t;
float dutyCycle = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLDOWN);

  ledcSetup(PWM_CHANNEL, PWM_FREQ, PWM_RESOLUTION);
  ledcAttachPin(PWM_PIN_LED, PWM_CHANNEL);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  //Polling button

  if(digitalRead(BUTTON_PIN)){
    waveform++;
    if(waveform > 7){
      waveform = 0;
    }
    Serial.println(waveform);
    delay(500);
  }

  t++;
  if(t >= 256){
    t = 0;
  }

  switch(waveform){
   //Formas de onda constantes
    case 0:
      dutyCycle = 0;
    break;
      
    case 1:
      dutyCycle = 0.3;
    break;

    case 2:
      dutyCycle = 0.5;
    break;

    case 3:
      dutyCycle = 0.8;
    break;

    case 4:
        dutyCycle = 1;
    break;
// Formas de onda variables
    case 5:
      dutyCycle = (t+0.1)/256;
      delay(2.5);
    break;

    case 6:
      dutyCycle = 0.5*sin(2*PI*t/256) + 0.5;
      delay(0.5);      
    break;

    case 7:
        dutyCycle = pow(2.71828, ((t/255)-1)*2);
        delay(4);
    break;
  }

  Serial.println(dutyCycle*100);

  ledcWrite(PWM_CHANNEL, dutyCycle*255);
  
}
