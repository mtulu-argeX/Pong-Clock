/*
 * Pacman Clockface
 * A ghost is chasing Pacman accross the screen
 */

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "Clockface_Pacman.h"
#include "State.h"

#define WHITE 1
#define BLACK 0
#define WIDTH 128
#define HEIGHT 64

#define DOTS_SPACE 10

const uint8_t PROGMEM pacman_bmp[13*2*3] = {
  B00000011, B11100000,
  B00001111, B11111000,
  B00011111, B11111100,
  B00011111, B11111100,
  B00111111, B11110000,
  B00111111, B10000000,
  B00111110, B00000000,
  B00111111, B10000000,
  B00111111, B11110000,
  B00011111, B11111100,
  B00011111, B11111100,
  B00001111, B11111000,
  B00000011, B11100000,

  B00000011, B11100000,
  B00001111, B11100000,
  B00011111, B11100000,
  B00011111, B11000000,
  B00111111, B10000000,
  B00111111, B00000000,
  B00111110, B00000000,
  B00111111, B00000000,
  B00111111, B10000000,
  B00011111, B11000000,
  B00011111, B11100000,
  B00001111, B11100000,
  B00000011, B11100000,

  B00000011, B11100000,
  B00001111, B11111000,
  B00011111, B11111100,
  B00011111, B11111100,
  B00111111, B11111110,
  B00111111, B11111110,
  B00111111, B11111110,
  B00111111, B11111110,
  B00111111, B11111110,
  B00011111, B11111100,
  B00011111, B11111100,
  B00001111, B11111000,
  B00000011, B11100000,
};

const uint8_t PROGMEM blinky_bmp[28*2] = {
  B00000011, B11000000,
  B00001111, B11110000,
  B00011111, B11111000,
  B00111111, B11111100,
  B00111001, B11100100,
  B00110000, B11000000,
  B01110011, B11001110,
  B01110011, B11001110,
  B01111001, B11100110,
  B01111111, B11111110,
  B01111111, B11111110,
  B01111111, B11111110,
  B01111011, B11011110,
  B00110001, B10001100,

  B00000011, B11000000,
  B00001111, B11110000,
  B00011111, B11111000,
  B00111111, B11111100,
  B00111001, B11100100,
  B00110000, B11000000,
  B01110011, B11001110,
  B01110011, B11001110,
  B01111001, B11100110,
  B01111111, B11111110,
  B01111111, B11111110,
  B01111111, B11111110,
  B01101110, B01110110,
  B01000110, B01100010,
};

const uint8_t PROGMEM pacman_die[308] = {
		0x00,0x00,
		0x60,0x0c,
		0x70,0x1c,
		0x78,0x3c,
		0x7c,0x7c,
		0x7e,0xfc,
		0x3f,0xf8,
		0x3f,0xf8,
		0x1f,0xf0,
		0x07,0xc0,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x40,0x04,
		0xf0,0x1e,
		0xf8,0x3e,
		0xfe,0xfe,
		0x7f,0xfc,
		0x7f,0xfc,
		0x3f,0xf8,
		0x0e,0xe0,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0xe0,0x0e,
		0xfc,0x7e,
		0xff,0xfe,
		0x7f,0xfc,
		0x3f,0xf8,
		0x0e,0xe0,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0xf0,0x1e,
		0xff,0xfe,
		0xff,0xfe,
		0x7f,0xfc,
		0x1e,0xf0,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x0f,0xe0,
		0xff,0xfe,
		0xff,0xfe,
		0x7f,0xfc,
		0x1e,0xf0,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x03,0x80,
		0x0f,0xe0,
		0x7f,0xfc,
		0xff,0xfe,
		0x7e,0xfc,
		0x1c,0x70,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x01,0x00,
		0x03,0x80,
		0x0f,0xe0,
		0x1f,0xf0,
		0x7f,0xfc,
		0x7e,0xfc,
		0x3c,0x78,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x01,0x00,
		0x03,0x80,
		0x07,0xc0,
		0x07,0xc0,
		0x0f,0xe0,
		0x1f,0xf0,
		0x0e,0xe0,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x01,0x00,
		0x01,0x00,
		0x03,0x80,
		0x03,0x80,
		0x03,0x80,
		0x07,0xc0,
		0x02,0x80,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x01,0x00,
		0x01,0x00,
		0x01,0x00,
		0x01,0x00,
		0x01,0x00,
		0x01,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x00,0x00,
		0x04,0x40,
		0x12,0x80,
		0x08,0x10,
		0x00,0x20,
		0x30,0x00,
		0x00,0x18,
		0x08,0x00,
		0x10,0x20,
		0x02,0x90,
		0x04,0x40
	};

ClockfacePacman::ClockfacePacman()
: blinky_x(0)
, dots_x(0)
, die_timer(0)
{}

void ClockfacePacman::update(uint8_t hour, uint8_t minute) {
  if (state.now.second() >= 5) {
    blinky_x = map(state.now.second(), 5, 60, WIDTH / 2 + 16, 12);
    dots_x = (dots_x + 2) % DOTS_SPACE;
    die_timer = 0;
  } else {
    die_timer += 1;
  }
}

void ClockfacePacman::draw(Adafruit_GFX* display) const {
  char buff[9];

  uint8_t hour = state.now.hour();
  if (!state.mode24h) {
    hour = hour % 12;
    if (hour == 0) hour = 12;
  }
  snprintf_P(buff, 9, PSTR("%02u:%02u")
    , hour
    , state.now.minute()
    );

  // Hour:Minute
  display->setTextColor(WHITE);
  display->setTextSize(2);
  display->setCursor(10, 0);
  display->print(buff);

  // am/pm suffix
  display->setTextSize(1);
  if (!state.mode24h) {
    display->setCursor(70, 7);
    if (state.now.hour() > 11) {
      display->print(F("pm"));
    } else {
      display->print(F("am"));
    }
  }

  // Pacman!
  display->drawFastHLine(0, HEIGHT - 22, WIDTH, WHITE);
  display->drawFastHLine(0, HEIGHT - 24, WIDTH, WHITE);
  display->drawFastHLine(0, HEIGHT - 5, WIDTH, WHITE);
  display->drawFastHLine(0, HEIGHT - 3, WIDTH, WHITE);

  for (uint8_t i = (WIDTH / 2) + DOTS_SPACE * 2 - dots_x; i < WIDTH; i += DOTS_SPACE) {
    display->fillCircle(i, HEIGHT - 14, 1, WHITE);
  }

  uint8_t pac_frame = dots_x < 2 ? 52: (dots_x < 6 ? 26:0);
  uint8_t ghost_frame = dots_x < 5 ? 0:28;

  if (die_timer == 0) {
    // Approach
    display->drawBitmap(WIDTH / 2, HEIGHT - 20, pacman_bmp + pac_frame, 16, 13, WHITE);
    display->drawBitmap(WIDTH / 2 - blinky_x, HEIGHT - 20, blinky_bmp + ghost_frame, 16, 14, WHITE);
  } else {
    // Caught!
    if (die_timer < 5) {
      // Freeze frame
      display->drawBitmap(WIDTH / 2, HEIGHT - 20, pacman_bmp + pac_frame, 16, 13, WHITE);
      display->drawBitmap(WIDTH / 2 - blinky_x, HEIGHT - 20, blinky_bmp + ghost_frame, 16, 14, WHITE);
    } else if ((die_timer - 5) / 2 <= 10) {
      uint16_t frame = constrain((die_timer - 5) / 2, 0, 10) * 28;
      display->drawBitmap(WIDTH / 2, HEIGHT - 20, pacman_die + frame, 15, 14, WHITE);
    }
  }
}

