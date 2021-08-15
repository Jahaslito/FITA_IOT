#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

const char *ssid = "";
const char *password = "";

double temp_amb;
double temp_obj;
int led = 2;

void connectWifi(){
  delay(1000);
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println(" ");
  Serial.print("Connecting");

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
 
  
}

void sendSensorData(){
  HTTPClient http;
  WiFiClient client;
  String postData; 
  String sensorData = (String)temp_obj;
  String url = "http://127.0.0.1/esp8266/postData.php";
  

  postData = "Temperature = "+ sensorData;

  http.begin(client, url);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST(postData);
  String payload = http.getString();
  Serial.print("httpCode");
  Serial.println(httpCode);
  Serial.println(payload);

  http.end();

  delay(5000);
}

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Temperature Sensor GY-906");
  delay(3000);
  Serial.println("Adafruit MLX90614 test");
  
  connectWifi();  
  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX sensor. Check wiring.");
    while (1);
  };
}

void loop() {
  temp_amb = mlx.readAmbientTempC();
  temp_obj = mlx.readObjectTempC();
  
  Serial.print("Room Temp = ");
  Serial.println(temp_amb);
  Serial.print("Object temp = ");
  Serial.println(temp_obj);
  digitalWrite(led, LOW);
  delay(1000);
  digitalWrite(led, HIGH);
  delay(1000);
  Serial.print("Room Temp2 = ");
  Serial.println(temp_amb);
  Serial.print("Object temp1 = ");
  Serial.println(temp_obj);
//  delay(2500);

  sendSensorData();
}
