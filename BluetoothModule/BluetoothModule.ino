#include <SoftwareSerial.h>

SoftwareSerial rybSerial(0, 1); // RX, TX

void setup() {
  Serial.begin(9600);
  while (!Serial);

  rybSerial.begin(9600);
  while (!rybSerial);

  Serial.println("Connected!");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    if (command.length() > 0) { // Check if the String is not empty
      rybSerial.println(command);
    }
  }
  
  if (rybSerial.available()) {
    String response = rybSerial.readStringUntil('\n');
    String hexResponse = stringToHex(response); // Convert response to hexadecimal
    Serial.println(response + ": " + hexResponse); // Use Serial.print instead of Serial.write
  }

  delay(20);
}

String stringToHex(String input) {
  String hex = "";
  for (int i = 0; i < input.length(); i++) {
    char buf[4];
    sprintf(buf, "%02X ", input[i]);
    hex += buf;
  }
  return hex;
}