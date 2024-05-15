#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pins
const byte addresses[][6] = {"1Node", "2Node"}; // Example addresses

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1, addresses[0]);
  radio.startListening();
  Serial.println("Listening for signals...");
}

void loop() {
  if (radio.available()) {
    char data[32] = {0};
    radio.read(&data, sizeof(data));
    Serial.print("Received data: ");
    for (int i = 0; i < sizeof(data); i++) {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}
