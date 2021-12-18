#include "config.h"
#include "DHT.h"
#define DHTPIN 4 // GIOP21
#define LED_PIN 21
#define DHTTYPE DHT11
#define FEED_OWNER "gowelyu"
DHT dht(DHTPIN, DHTTYPE);
 

AdafruitIO_Feed *temperatureb = io.feed("Beijing temperature");
AdafruitIO_Feed *humidityb = io.feed("Beijing humidity");
AdafruitIO_Feed *sharedFeed = io.feed("temperature", FEED_OWNER);



void setup() {
  
 // start the serial connection
  Serial.begin(115200);
  dht.begin();
  pinMode(LED_PIN, OUTPUT);
  // wait for serial monitor to open
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  sharedFeed->onMessage(handleMessage);
  sharedFeed->get();

//   temperatureb->onMessage(handleMessage);
   humidityb->onMessage(handleMessage);
   Serial.println();
   Serial.println(io.statusText());

  }


void loop() {
  io.run();
  delay(2000);
  
  
  // read humidity
  float humi  = dht.readHumidity();
  // read temperature as Celsius
  float tempC = dht.readTemperature();
  // read temperature as Fahrenheit
  float tempF = dht.readTemperature(true);

  // check if any reads failed
  if (isnan(humi) || isnan(tempC) || isnan(tempF)) 
  {
    Serial.println("Failed to read from DHT sensor!");
  } 
  else 
  {
//    Serial.print("Beijing Humidity: ");
//    Serial.print(humi);
//    Serial.print("%");
//
//    Serial.print("  |  "); 
//
//    Serial.print("Beijing Temperature: ");
//    Serial.print(tempC);
//    Serial.print("°C ~ ");
//    Serial.print(tempF);
//    Serial.println("°F");
  }
  
  temperatureb->save(tempC);
  humidityb->save(humi);
  delay(5000);
}

void handleMessage(AdafruitIO_Data *data) {

  // convert the data to integer
  //int reading = data->toInt();
  

  Serial.print("Shenzhen received <- ");
  Serial.println(temperature);
  if (reading >26.2)
  {
     digitalWrite(21, HIGH);
  }

  else
  {
    digitalWrite(21, LOW);
  }


}
