//Lecturas del sensor barométrico (T y P) con SD

#include <Adafruit_BMP280.h>
#include <SD.h>
#include <sd_diskio.h>
#include <sd_defines.h>

#define PIN_LED 32

Adafruit_BMP280 bmp;
File readings;
File read_me;
char payload[50]; //Datos a escribir en SD y serial

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(115200); // inicializar serial UART-USB
  bmp.begin(0x76);// Inicializar comunicación I2C con el sensor barometrico
  SD.begin();

  pinMode(PIN_LED, OUTPUT);
  
  //README
  read_me = SD.open("/README.txt", FILE_WRITE);
  read_me.print("Archivo de lecturas del sensor BMP280.\n"
  "Temperatura [°C], Presión [Pa]");
  read_me.close();

}

void loop() {
  // put your main code here, to run repeatedly:
  //hacer columna 1: temperatura; columna 2: presion

  
  //sprintf(payload, "Temp:%8.2f,Press:%8.2f",bmp.readTemperature(),bmp.readPressure());
  //pones en donde vas a escribir, y luego lo que quieres escribir
  //Le pones el numero de cifras enteras y decimales que quieres al %f
  
  //Ahora vamos a ponerlo solo datos para poder extraer facil
  sprintf(payload, "%.2f,%.2f",bmp.readTemperature(),bmp.readPressure());
  Serial.println(payload);
  /*
  //Serial.print(bmp.readPressure());
  //Serial.print(',');
  //Serial.println(bmp.readTemperature());
  */

//ABRO ARCHIVO Y ESCRIBO
digitalWrite(PIN_LED,HIGH);
  readings = SD.open("/readings.csv",FILE_APPEND);
  readings.println(payload); //escribes
  readings.close(); //cierras
digitalWrite(PIN_LED, LOW);
delay(500);
  

}
