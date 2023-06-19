#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <RH_RF95.h>

#define RFM95_CS_PIN 6
#define RFM95_IRQ_PIN 7
#define RFM95_RST_PIN 0
#define RFM95_FREQ 915.0

RH_RF95 rf95(RFM95_CS_PIN, RFM95_IRQ_PIN);

void setup()
{
  wiringPiSetup();
  pinMode(RFM95_RST_PIN, OUTPUT);
  digitalWrite(RFM95_RST_PIN, HIGH);
  delay(100);
  digitalWrite(RFM95_RST_PIN, LOW);
  delay(10);
  digitalWrite(RFM95_RST_PIN, HIGH);
  delay(10);

  if (!rf95.init()) {
    printf("RFM95 LoRa init failed\n");
    exit(1);
  }

  rf95.setFrequency(RFM95_FREQ);
  rf95.setTxPower(23, false);

  printf("RFM95 LoRa receiver setup complete\n");
}

void loop()
{
  if (rf95.available()) {
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);

    if (rf95.recv(buf, &len)) {
      // Message received
      buf[len] = '\0';
      printf("Received message: %s\n", (char*)buf);
    } else {
      printf("Error: failed to receive message\n");
    }
  }
}

int main(int argc, char *argv[])
{
  setup();

  while (1) {
    loop();
    delay(10);
  }

  return 0;
}
