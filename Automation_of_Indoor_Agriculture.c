#include <math.h> 
#define SensorPin A3 
float moistureSensorValue = 0;
 //Motor A
const int inputPin1  = 10;    // Pin 15 of L293D IC
const int inputPin2  = 11;    // Pin 10 of L293D IC
//Motor B
const int inputPin3  = 8;   // Pin  7 of L293D IC
const int inputPin4  = 9;   // Pin  2 of L293D IC 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  int airSensorValue;
  pinMode(6, INPUT);
  pinMode(inputPin1, OUTPUT);
  pinMode(inputPin2, OUTPUT);
  pinMode(inputPin3, OUTPUT);
  pinMode(inputPin4, OUTPUT);
}
double Thermister(int RawADC) {  //Function to perform the fancy math of the Steinhart-Hart equation
  double Temp;
  Temp = log(((10240000 / RawADC) - 10000));
  Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp )) * Temp );
  Temp = Temp - 273.15;              // Convert Kelvin to Celsius
  // Temp = (Temp * 9.0)/ 5.0 + 32.0; // Celsius to Fahrenheit - comment out this line if you need Celsius
  return Temp;

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(A1);
  int airSensorValue = analogRead(A2);
  moistureSensorValue = analogRead(SensorPin);

  //This function loops while the arduino is powered
  int val;                //Create an integer variable
  double temp;//Variable to hold a temperature value
  int pirSensorValue = digitalRead(6);

  val = analogRead(0);    //Read the analog port 0 and store the value in val
  temp = Thermister(val); //Runs the fancy math on the raw analog value
  Serial.println('*');
  Serial.println(temp);//Print the value to the serial port
  Serial.println(sensorValue);
  Serial.println(pirSensorValue);
  Serial.println(airSensorValue, DEC);
  Serial.println(moistureSensorValue);
  if(moistureSensorValue<300){
    digitalWrite(inputPin1, HIGH);
    digitalWrite(inputPin2, LOW);
  }
  if(temp<30){
    digitalWrite(inputPin3, HIGH);
    digitalWrite(inputPin4, LOW);
  }

}
