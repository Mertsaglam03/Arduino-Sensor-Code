#include <Wire.h>
#include "SparkFunHTU21D.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#define anInput A0
#define co2Zero 0  // Assign an appropriate value

// GPIO where the DS18B20 is connected to
const int oneWireBus = 5;

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(oneWireBus);

// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);
//Create an instance of the object
HTU21D myHumidity;


void setup() {
  Serial.begin(9600); 
  pinMode(anInput, INPUT); 
  myHumidity.begin();
  sensors.begin();

 // initialize serial communication at 9600 bits per second
}

void loop() {

  int analogValue = analogRead(A1);  // read the input on analog pin 0
  Serial.println(analogValue);       // print out the value you read
  float humd = myHumidity.readHumidity();
  float temp = myHumidity.readTemperature();

  Serial.print("Time:");
  Serial.print(millis());
  Serial.print(" Temperature:");
  Serial.print(temp, 1);
  Serial.print("C");
  Serial.print(" Humidity:");
  Serial.print(humd, 1);
  Serial.print("%");

  Serial.println();

  if (analogValue < 100) {
    Serial.println("Fotosentez yapıyor, aydınlık");  // very bright
  } 
  else if (analogValue < 200) {
    Serial.println("Fotosentez yapıyor, yeterince aydınlık");      // bright
  } 
  else if (analogValue < 400) {
    Serial.println("Işık daha durgun");        // shiny or bright
  } 
  else if (analogValue < 700) {
    Serial.println("Işık düzeyi: az, fotosentez için ışığı artırın veya dinlenme sürecinin başlaması için ışığı azaltın"); // slightly dark
  } 
  else {
    Serial.println("Işık çok az, dinlenme sürecinde. Fotosentez yapılmıyor");      // dark
  }
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = sensors.getTempFByIndex(0);
  Serial.print(temperatureC);
  Serial.println("ºC");
  Serial.print(temperatureF);
  Serial.println("ºF");
  int co2now[10];
  int co2raw = 0;
  int co2ppm = 0;
  int zzz = 0;

  for (int x = 0; x < 10; x++) {
    co2now[x] = analogRead(A0);
    delay(200);
  }

  for (int x = 0; x < 10; x++) {
    zzz = zzz + co2now[x];
  }

  co2raw = zzz / 10;  // Corrected to zzz
  co2ppm = co2raw - co2Zero;  // Corrected to co2Zero

  Serial.print("Air Quality: ");
  Serial.print(co2ppm);
  Serial.println(" PPM");


  delay(1000);  // delay in between reads for stability
