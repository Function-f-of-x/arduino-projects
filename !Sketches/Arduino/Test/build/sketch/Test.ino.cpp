#line 1 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Test\\Test.ino"
#include <Arduino.h>
#include <U8g2lib.h>
U8G2_SSD1306_128X64_NONAME_1_HW_I2C u8g2(U8G2_R0);

#line 5 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Test\\Test.ino"
void setup();
#line 18 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Test\\Test.ino"
void loop();
#line 5 "K:\\!!!!Моё\\Arduino\\!Скейчи\\Test\\Test.ino"
void setup() {
  Serial.begin(115200);
  u8g2.begin();

  uint8_t tile_height = u8g2.getBufferTileHeight();
  uint8_t page_height = tile_height * 8;

  Serial.print("Tile height: ");
  Serial.println(tile_height);
  Serial.print("Page height (pixels): ");
  Serial.println(page_height);
}

void loop() {}


