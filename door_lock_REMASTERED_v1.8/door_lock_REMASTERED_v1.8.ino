#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>
#include <NfcAdapter.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>
#include <SPI.h>


#define TFT_CS 6
#define TFT_DC 5
#define TFT_RST 7
#define open_switch 3
#define door_state 2

#define door_close_led 10
#define lock 8  //door_open_led

String card_id = "";

Adafruit_ST7789 tft = Adafruit_ST7789(TFT_CS, TFT_DC, TFT_RST);

PN532_I2C pn532_i2c(Wire);
NfcAdapter nfc = NfcAdapter(pn532_i2c);

//all allowed cards:

String allowedCards[100] = {

  "23 49 67 A3",
  "43 8E 60 A3",
  "73 FD 84 13"

};


void setup() {

  pinMode(open_switch, INPUT_PULLUP);
  pinMode(door_close_led, OUTPUT);
  pinMode(lock, OUTPUT);
  pinMode(door_state, INPUT_PULLUP);

  Serial.begin(9600);
  SPI.begin();
  nfc.begin();

  Serial.println("Door_lock_REMASTERED v1.8");

  tft.init(240, 320);
  tft.fillScreen(ST77XX_BLACK);
  tft.invertDisplay(false);

  zero();

  digitalWrite(door_close_led, HIGH);
}

void loop() {

  if (digitalRead(door_state) == HIGH) {

    digitalWrite(lock, HIGH);
    digitalWrite(door_close_led, LOW);

    granted();
    Serial.println("granted (door open)");


    while (digitalRead(door_state) == HIGH) {
      delay(100);
    }

    delay(2000);

    digitalWrite(lock, LOW);
    digitalWrite(door_close_led, HIGH);

    zero();

  } else {

    if (digitalRead(open_switch) == LOW) {

      digitalWrite(lock, HIGH);
      digitalWrite(door_close_led, LOW);

      switch_granted();
      Serial.println("granted (open switch)");

      delay(2000);

      digitalWrite(lock, LOW);
      digitalWrite(door_close_led, HIGH);

      zero();

    } else {

      if (nfc.tagPresent()) {

        NfcTag tag = nfc.read();
        card_id = tag.getUidString();

        if (checkCard(card_id)) {
          granted();
          Serial.println("granted (rfid card)");
          digitalWrite(lock, HIGH);
          digitalWrite(door_close_led, LOW);

          delay(2000);

          digitalWrite(lock, LOW);
          digitalWrite(door_close_led, HIGH);

          zero();
        }
      }
    }
  }
}


bool checkCard(String id) {

  for (int i = 0; i < sizeof(allowedCards) / sizeof(allowedCards[0]); i++) {
    if (card_id == allowedCards[i]) {

      return true;
    }
  }
  return false;
}


//graphics:

void zero() {

  tft.setCursor(10, 20);
  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_MAGENTA);
  tft.setTextSize(4);
  tft.println("Scan card");

  tft.fillRoundRect(30, 80, 190, 230, 10, ST77XX_MAGENTA);
  tft.fillRoundRect(35, 85, 180, 220, 10, ST77XX_BLACK);
  tft.fillRect(55, 85, 35, 220, ST77XX_MAGENTA);
  tft.fillCircle(145, 140, 40, ST77XX_MAGENTA);
  tft.fillCircle(145, 140, 25, ST77XX_BLACK);
  tft.fillRoundRect(140, 170, 15, 110, 10, ST77XX_MAGENTA);
  tft.fillRect(155, 240, 15, 10, ST77XX_MAGENTA);
  tft.fillRect(155, 260, 15, 10, ST77XX_MAGENTA);
  tft.fillRect(155, 250, 5, 10, ST77XX_MAGENTA);
}

void danied() {

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(50, 10);
  tft.setTextColor(ST77XX_RED);
  tft.setTextSize(4);

  tft.println("Access");
  tft.setCursor(50, 50);
  tft.println("danied");
  tft.setTextSize(3.5);
  tft.setCursor(30, 100);
  tft.println("wrong card");

  tft.fillCircle(120, 200, 50, ST77XX_RED);
  tft.fillCircle(120, 200, 35, ST77XX_BLACK);
  tft.fillRoundRect(55, 200, 130, 100, 15, ST77XX_RED);
  tft.fillCircle(120, 250, 15, ST77XX_BLACK);
  tft.fillRect(113, 260, 15, 25, ST77XX_BLACK);
}

void granted() {

  tft.fillScreen(ST77XX_BLACK);
  tft.setCursor(50, 20);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(4);
  tft.println("Access");
  tft.setCursor(40, 60);
  tft.println("granted");

  tft.fillCircle(120, 190, 50, ST77XX_GREEN);
  tft.fillCircle(120, 190, 35, ST77XX_BLACK);
  tft.fillRect(70, 180, 60, 20, ST77XX_BLACK);
  tft.fillRoundRect(55, 200, 130, 100, 15, ST77XX_GREEN);
  tft.fillCircle(120, 250, 15, ST77XX_BLACK);
  tft.fillRect(113, 260, 15, 25, ST77XX_BLACK);
}


void switch_granted() {

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_GREEN);
  tft.setTextSize(3);
  tft.setTextSize(3);
  tft.setCursor(15, 20);
  tft.println("Safty switch");
  tft.setCursor(40, 60);
  tft.println("triggered");
  tft.setCursor(30, 100);
  tft.println("doors open");

  tft.fillCircle(120, 190, 50, ST77XX_GREEN);
  tft.fillCircle(120, 190, 35, ST77XX_BLACK);
  tft.fillRect(70, 180, 60, 20, ST77XX_BLACK);
  tft.fillRoundRect(55, 200, 130, 100, 15, ST77XX_GREEN);
  tft.fillCircle(120, 250, 15, ST77XX_BLACK);
  tft.fillRect(113, 260, 15, 25, ST77XX_BLACK);
}
