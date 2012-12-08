from buslib import *
import time

cmd(COMMAND_PING, b'PING', quiet=True)
time.sleep(0.2)

while True:
    b = ser.read(1)
    if len(b) == 0:
        continue
    print("%02x" % b[0], end=" ")
    sys.stdout.flush()

