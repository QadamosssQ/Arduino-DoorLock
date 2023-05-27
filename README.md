# DoorLock-Arduino
## Door lock system on Arduino UNO

> Security solution for Smart Home Systems, managing access to the door locking in RFID system.

## How it works?
> If you want to open door you just must to touch rfid sensor with your rfid card with id declared in code in ```allowedCards[]``` array. If you are inside room, to open door you must to hold button until doors open.
> Every action you will see on tft display.

## Features
+ RFID card door access control
+ Easy use
+ Secure and reliable door access management
+ Supports multiple RFID cards or tags

## Components
+ Arduino UNO
+ PN532 (RFID reader)
+ TFT 2.8" 240x320 ST7789 (Display)
+ Electromagnetic door bolt 12V
+ Button, green and red diodes, breadboard, door open sensor
+ power supply 12V 1A

## Connections

### 1. TFT
```
VCC ------ 5V
GND ------ GND
CS  ------ 6
RESET ---- 7
DC  ------ 5
MOSI  ---- 11
SCK  ----- 13
LED  ----- 5V
MISO ----- (no required for display)
```

### 2. PN532
```
VCC ------ 5V
GND ------ GND
SDA  ----- A4
SCL  ----- A5
```

### 3. Others
```
Botton ------------ 4
Green diode  ------ 8
Red diode  -------- 10
Door open sensor -- 2
```


## Libraries
+ Wire (built in)
+ SPI (built in)
+ PN532 and PN532_I2C ([Download here](https://github.com/elechouse/PN532/tree/PN532_HSU/PN532_I2C))
+ NfcAdapter ([Download here](https://github.com/elechouse/PN532/tree/PN532_HSU/NDEF))
+ Adafruit_GFX ([Download here](https://github.com/adafruit/Adafruit-GFX-Library))
+ Adafruit_ST7789 ([Download here](https://github.com/adafruit/Adafruit-ST7735-Library/tree/master))


## Scheme
![Project scheme](https://github.com/QadamosssQ/Arduino-DoorLock/blob/main/img/DoorLock_scheme.png)
<br>
<br>

## About alternative version
> I tried to make database for adding new cards to system and read them to open doors for good ones but I stopped this idea, beacuse sometimes it works but after few seconds I got tons of errors from my SD reader. I don' t know how to solve it. Can you help me?

## 3D printed case
> Not finished yet!
<br>



## License

This project is licensed under the [MIT License](LICENSE).

The MIT License is a permissive open-source license that allows you to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the software. It also includes a disclaimer of warranty and liability.

For more details, please see the [LICENSE](LICENSE) file.




