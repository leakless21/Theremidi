#include <SimpleKalmanFilter.h>
int analogPin = A0;
float sum = 0;
float sensorVal = 0;
SimpleKalmanFilter simpleKalmanFilter(10, 10, 0.1);

void setup()
{
  Serial.begin( 9600 ); //Enable the serial comunication
}

void loop()
{
  float x = simpleKalmanFilter.updateEstimate(analogRead(analogPin));
  sum = 0;
  for (int i=0; i<5; i++)
  {
    sum=sum+x;  
  }
  sensorVal=sum/5;
  float original = (13 * pow(analogRead(analogPin) * 0.0048828125, -1));
  float kal = (13 * pow(x * 0.0048828125, -1));
  float distance = (13 * pow(sensorVal * 0.0048828125, -1)); //Calculate the distance in centimeters and store the value in a variable
  Serial.print("Original:");
  Serial.println(original);
  Serial.print("Kalman:");
  Serial.println(kal);
  Serial.print("Kalman+Average:");
  Serial.println(distance);
  delay(150);
}
