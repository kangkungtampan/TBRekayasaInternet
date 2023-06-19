#include <RH_RF95.h>
#include <wiringPi.h>

#define RFM95_CS_PIN 6
#define RFM95_IRQ_PIN 7
#define RFM95_RST_PIN 0

// Change to your frequency and spreading factor
#define RFM95_FREQ 915.0
#define RFM95_SF 7

// Create an instance of the RH_RF95 class
RH_RF95 rf95(RFM95_CS_PIN, RFM95_IRQ_PIN);

int main() {
    // Initialize wiringPi library
    wiringPiSetup();

    // Reset the RFM95 module
    pinMode(RFM95_RST_PIN, OUTPUT);
    digitalWrite(RFM95_RST_PIN, HIGH);
    delay(10);
    digitalWrite(RFM95_RST_PIN, LOW);
    delay(10);
    digitalWrite(RFM95_RST_PIN, HIGH);
    delay(10);

    // Initialize the RFM95 module
    if (!rf95.init()) {
        printf("RFM95 module initialization failed!\n");
        exit(1);
    }

    // Set the frequency and spreading factor
    rf95.setFrequency(RFM95_FREQ);
    rf95.setSpreadingFactor(RFM95_SF);

    // Print a message and wait for packets
    printf("Waiting for LoRa packets...\n");
    while (1) {
        // Check if a packet has been received
        if (rf95.available()) {
            // Read the packet and print its contents
            uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
            uint8_t len = sizeof(buf);
            if (rf95.recv(buf, &len)) {
                buf[len] = '\0';
                printf("Received packet: %s\n", buf);
            }
        }

        delay(1000);
    }

    return 0;
}