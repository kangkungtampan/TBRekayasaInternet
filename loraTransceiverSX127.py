from time import sleep
from pyLoRa.pyLoRa import LoRa

# Create LoRa object
lora = LoRa()

# Set frequency, bandwidth, and spreading factor
lora.set_frequency(915000000)
lora.set_bandwidth(125000)
lora.set_spreading_factor(7)

# Enable CRC checking
lora.set_crc(True)

# Initialize LoRa
lora.init()

# Infinite loop to receive LoRa messages
while True:
    # Check if a message has been received
    if lora.received_packet():
        # Read the message and print it
        message = lora.read_packet()
        print("Received message: {}".format(message))
    
    sleep(0.1)
