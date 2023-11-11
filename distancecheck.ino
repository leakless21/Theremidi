#include <Average.h>
#include <Adafruit_SH110X.h>
Adafruit_SH1106G display(128, 64); 

// Reserve space for 10 entries in the average bucket for each sensor.
Average<float> sensor1Ave(10);
Average<float> sensor2Ave(10);

void setup() {
  Serial.begin(115200);

  delay(50);  // This delay is needed to let the display to initialize
  display.begin(0x3C, true);  // Initialize display with the I2C address of 0x3C
  //display.begin(SSD1306_SWITCHCAPVCC, 0x7A);  // Initialize display with the I2C address of 0x3C
  display.clearDisplay();  // Clear the buffer
  display.setTextColor(SH110X_WHITE);  // Set color of the text
  display.setRotation(0);  // Set orientation. Goes from 0, 1, 2 or 3
  display.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
  display.setTextSize(2);
}

void loop() {
  // Add new random values to the buckets
  float sensor1Value = (13 * pow(analogRead(A0) * 0.0048828125, -1)) + 1.8;
  if (sensor1Value >= 3.0 && sensor1Value <= 40.0) {
    sensor1Ave.push(sensor1Value);
  }

  float sensor2Value = (13 * pow(analogRead(A1) * 0.0048828125, -1)) + 1.8;
  if (sensor2Value >= 3.0 && sensor2Value <= 40.0) {
    sensor2Ave.push(sensor2Value);
  }

  display.clearDisplay();

  // Draw sensor 1 reading
  display.setCursor(0, 10);
  display.print("S1:");
  display.print(sensor1Ave.mean());
  display.println("cm");

  // Draw sensor 2 reading
  display.setCursor(0, 40);
  display.print("S2:");
  display.print(sensor2Ave.mean());
  display.println("cm");

  display.display();

  delay(100);
}

