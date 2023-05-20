//goood



#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

String card_id = "";

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

#define TFT_CS 6
#define TFT_DC 5
#define TFT_RST 7

#define DevPin 9

int i = 0;

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);



// pins connection for arduino:
// const int _MISO = 12;
// const int _MOSI = 11;
// const int _CS = 10;
// const int _SCK = 13;


const int chipSelect = 10;

File myFile;

void setup() {
  Serial.begin(9600);
  delay(200);

  nfc.begin();

  pinMode(DevPin, INPUT_PULLUP);

  SPI.begin();
  tft.init(240, 320);
  tft.invertDisplay(false);
  tft.fillScreen(ST77XX_BLACK);


  if (!SD.begin(chipSelect)) {
    Serial.println("SD init error.");
    return;
  }

  Serial.println("SD init good");

  if (SD.exists("database.txt")) {

  } else {
    myFile = SD.open("database.txt", FILE_WRITE);

    if (myFile) {
      Serial.print("Creating file database.txt");

      myFile.println("DoorLock database");
      myFile.println("By Adamoss");
      myFile.println("\nCompatible card IDs:");

      myFile.close();
      Serial.println("done.");

    } else {
      Serial.println("error opening database.txt");
    }
  }
}


void loop() {


  if (nfc.tagPresent()) {

    NfcTag tag = nfc.read();
    card_id = tag.getUidString();


    if (digitalRead(DevPin) == LOW) {

      WriteData(card_id);
    } else {

      ReadAndCheckData(card_id);
    }
  }
}


void WriteData(String data_to_write) {
  delay(300);

  if (SD.exists("database.txt")) {

    myFile = SD.open("database.txt", FILE_WRITE);

    if (myFile) {
      Serial.print("Writing to file");


      myFile.println(data_to_write);
      myFile.close();
      Serial.println("done.");

    } else {
      Serial.println("error opening database.txt 1");
    }
  }
}



void ReadData() {
  myFile = SD.open("database.txt");

  if (myFile) {
    Serial.println("Reading:");


    while (myFile.available()) {
      Serial.write(myFile.read());
    }

    myFile.close();
  } else {

    Serial.println("error opening database.txt 2");
  }
}



void ReadAndCheckData(String toCheck) {
  myFile = SD.open("database.txt");

  if (myFile) {
    Serial.println("Reading:");

    while (myFile.available()) {
      String line = myFile.readStringUntil('\n');
      if (line.indexOf(toCheck) != -1) {
        Serial.println("access granted");
        break;
      } else {
        Serial.println("no access");
      }
    }

    myFile.close();
  } else {
    Serial.println("Error opening database.txt 3");
  }
}
