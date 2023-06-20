import time
from SX127x.LoRa import *
from SX127x.board_config import BOARD

BOARD.setup()

class LoRaReceiver(LoRa):
    def __init__(self, verbose=False):
        super(LoRaReceiver, self).__init__(verbose)
        self.set_mode(MODE.SLEEP)
        self.set_dio_mapping([0] * 6)

    def on_rx_done(self):
        print("Received: {}".format(self.read_payload()))
        self.set_mode(MODE.SLEEP)
        self.reset_ptr_rx()
        self.set_mode(MODE.RXCONT)

    def start(self):
        self.reset_ptr_rx()
        self.set_mode(MODE.RXCONT)
        while True:
            time.sleep(0.1)

lora = LoRaReceiver(verbose=False)
lora.set_frequency(915000000)
lora.set_spreading_factor(7)
lora.set_bw(BW.BW125)
lora.set_cr(CR.CR45)
lora.set_rx_crc(True)

print("LoRa Receiver")
try:
    lora.start()
except KeyboardInterrupt:
    pass

BOARD.teardown()
