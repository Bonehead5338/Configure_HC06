# Configure_HC06
Arduino sketch to configure HC-06 bluetooth module

Setup 3 parameters:

* **BT_NAME** (20 Characters max String)
* **BT_PIN** (4 digit numeric pin)
* **BT_BAUD** (from valid values listed above)

Sketch will search for connected devices and configure as per above parameters

Example Serial Monitor Output:
```
Serial started
Looking for connected HC-06 modules
Found device HC-06 at 4800bps
Device Name successfully set to BT_DEVICE
Device PIN successfully set to 1234
Baud configured at 9600bps
Successfully connected at new baud rate
Configuration completed successfully.
```
