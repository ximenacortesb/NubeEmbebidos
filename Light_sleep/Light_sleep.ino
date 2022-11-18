#define uS_TO_S_FACTOR 1000000  //Factor de conversion de s a us
#define TIME_TO_SLEEP 10 //Tiempo que el ESP va a dormir en a
#define LED_PIN 32

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP*uS_TO_S_FACTOR);
  Serial.println("Configurando ESP32 para dormir por " + String(TIME_TO_SLEEP) + " segundos.");
  


}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED_PIN, LOW);
  esp_light_sleep_start();

  digitalWrite(LED_PIN, HIGH);
  delay(500);
  
  print_wakeup_reason();

}

void print_wakeup_reason(){
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason){
    case ESP_SLEEP_WAKEUP_EXT0:
      Serial.println("Inicio causado por señal en el RTC_IO (Periféricos del RTC)");
    
    case ESP_SLEEP_WAKEUP_EXT1:
      Serial.println("Inicio causado por señal en el RTC_CNTL");

    case ESP_SLEEP_WAKEUP_TIMER:
      Serial.println("Inicio causado por señal de un timer");

    case ESP_SLEEP_WAKEUP_TOUCHPAD:
      Serial.println("Inicio causado por señal en un pin touch");
    
    case ESP_SLEEP_WAKEUP_ULP:
      Serial.println("Inicio causado por señal lanzada por el ULP croprocesador");
    break;

    default:
      Serial.printf("El inicio no fue causado por ninguna razón conocida %d\n", wakeup_reason); 
  }
}
