#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

double temp_amb;
double temp_obj;
int led = 2;
void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Temperature Sensor GY-906");
  delay(3000);
  Serial.println("Adafruit MLX90614 test");

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
//  delay(2500);
}
