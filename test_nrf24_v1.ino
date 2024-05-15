#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(9, 10); // CE, CSN pins

// Function to generate a random address
void generateAddress(byte *address, int length) {
  for (int i = 0; i < length; i++) {
    address[i] = random(256); // Random byte value
  }
}

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.startListening();
  Serial.println("Listening for signals...");
}

void loop() {
  byte address[5]; // NRF24L01 address is 5 bytes long
  generateAddress(address, 5);
  radio.openReadingPipe(1, address);

  if (radio.available()) {
    char data[32] = {0};
    radio.read(&data, sizeof(data));
    Serial.print("Received data from address: ");
    for (int i = 0; i < 5; i++) {
      Serial.print(address[i], HEX);
      Serial.print(" ");
    }
    Serial.print(" -> Data: ");
    for (int i = 0; i < sizeof(data); i++) {
      Serial.print(data[i], HEX);
      Serial.print(" ");
    }
    Serial.println();
  }
}
