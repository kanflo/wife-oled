#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

// Shown on boot
#define happy_mac_width 32
#define happy_mac_height 32
static char happy_mac_bits[] = {
  0xE0, 0xFF, 0xFF, 0x03, 0x10, 0x00, 0x00, 0x04, 0x08, 0x00, 0x00, 0x08, 
  0x88, 0xFF, 0x7F, 0x08, 0x48, 0x00, 0x80, 0x08, 0x48, 0x00, 0x80, 0x08, 
  0x48, 0x00, 0x80, 0x08, 0x48, 0x88, 0x84, 0x08, 0x48, 0x88, 0x84, 0x08, 
  0x48, 0x80, 0x80, 0x08, 0x48, 0x80, 0x80, 0x08, 0x48, 0xC0, 0x80, 0x08, 
  0x48, 0x00, 0x80, 0x08, 0x48, 0x10, 0x82, 0x08, 0x48, 0xE0, 0x81, 0x08, 
  0x48, 0x00, 0x80, 0x08, 0x48, 0x00, 0x80, 0x08, 0x88, 0xFF, 0x7F, 0x08, 
  0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 
  0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0xFC, 0x08, 0xC8, 0x00, 0x00, 0x08, 
  0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 
  0xF0, 0xFF, 0xFF, 0x07, 0x10, 0x00, 0x00, 0x04, 0x10, 0x00, 0x00, 0x04, 
  0x10, 0x00, 0x00, 0x04, 0xF0, 0xFF, 0xFF, 0x07
};

// Shown when whatever goes wrong (DHCP failed, MQTT connect failed, ...)
#define sad_mac_width 32
#define sad_mac_height 32
static char sad_mac_bits[] = {
  0xE0, 0xFF, 0xFF, 0x03, 0x10, 0x00, 0x00, 0x04, 0x08, 0x00, 0x00, 0x08, 
  0x88, 0xFF, 0x7F, 0x08, 0x48, 0x00, 0x80, 0x08, 0x48, 0x00, 0x80, 0x08, 
  0x48, 0x0A, 0x94, 0x08, 0x48, 0x04, 0x88, 0x08, 0x48, 0x0A, 0x94, 0x08, 
  0x48, 0x00, 0x80, 0x08, 0x48, 0x20, 0x81, 0x08, 0x48, 0xC0, 0x80, 0x08, 
  0x48, 0x00, 0x80, 0x08, 0x48, 0xE0, 0x83, 0x08, 0x48, 0x10, 0x8C, 0x08, 
  0x48, 0x00, 0x90, 0x08, 0x48, 0x00, 0x80, 0x08, 0x88, 0xFF, 0x7F, 0x08, 
  0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 
  0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0xFC, 0x08, 0xC8, 0x00, 0x00, 0x08, 
  0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 0x08, 0x00, 0x00, 0x08, 
  0xF0, 0xFF, 0xFF, 0x07, 0x10, 0x00, 0x00, 0x04, 0x10, 0x00, 0x00, 0x04, 
  0x10, 0x00, 0x00, 0x04, 0xF0, 0xFF, 0xFF, 0x07
};

// This is just because I am a sucker for old C64 stuff...
#define commodore_balloon_width 16
#define commodore_balloon_height 21
static char commodore_balloon_bits[] = {
  0xF0, 0x07, 0xFC, 0x1F, 0xFE, 0x3F, 0x3E, 0x3F, 0xDF, 0x7C, 0xDF, 0x7F, 
  0xDF, 0x7C, 0x3E, 0x3F, 0xFE, 0x3F, 0xFE, 0x3F, 0xFA, 0x2F, 0xF4, 0x17, 
  0xE4, 0x13, 0xC8, 0x09, 0xC8, 0x09, 0x90, 0x04, 0x90, 0x04, 0xE0, 0x03, 
  0xE0, 0x03, 0xE0, 0x03, 0xC0, 0x01
};

// Below are small samples of Ubuntu Condensed (font.ubuntu.com) needed
// to display temperatures. The characters represented are -.°0123456789
// in almost ascii order (the slash has been replaced by the degree sign)
#define min_font_ascii '-'
#define max_font_ascii '9'

// As Ubuntu Condensed is not a monospace font we need to keep track of
// the width of each character.
//                              -  .  °   0  1   2   3   4   5   6   7   8   9
static unsigned char small_widths[] = {5, 4, 6, 13, 9, 13, 14, 15, 13, 13, 14, 14, 14};
static unsigned char large_widths[] = {6, 4, 8, 13, 9, 13, 14, 16, 13, 13, 14, 14, 14};

// The fonts are represented as one single image where each character begins
// on an even 8 bit boundary. To find the small character '.' we need to step
// over the character '-' which is 5 pixels wide. Rounding up to 8 we need to
// step over the first full byte on each row in small_digits_bits.

// The small font
#define small_digits_width 184
#define small_digits_height 28
static char small_digits_bits[] = {
  0x00, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x3F, 0xE0, 0x00, 0xC0, 0x01, 0xFE, 0x03, 0xFE, 0x00, 0x00, 0x0F, 
  0xFF, 0x0F, 0x00, 0x07, 0xFF, 0x3F, 0xF0, 0x03, 0xF0, 0x07, 0x00, 0x00, 
  0x33, 0xF8, 0x03, 0xE0, 0x01, 0xFF, 0x07, 0xFF, 0x03, 0x00, 0x0F, 0xFF, 
  0x0F, 0xC0, 0x0F, 0xFF, 0x3F, 0xF8, 0x07, 0xF8, 0x0F, 0x00, 0x00, 0x33, 
  0xFC, 0x07, 0xF0, 0x01, 0xFF, 0x0F, 0xFF, 0x07, 0x80, 0x0F, 0xFF, 0x0F, 
  0xE0, 0x0F, 0xFF, 0x3F, 0xFC, 0x0F, 0xFC, 0x1F, 0x00, 0x00, 0x3F, 0xFE, 
  0x0F, 0xF8, 0x01, 0x07, 0x0F, 0xE6, 0x0F, 0xC0, 0x0F, 0x0F, 0x00, 0xF0, 
  0x03, 0x00, 0x1E, 0x1E, 0x1E, 0x1E, 0x3E, 0x00, 0x00, 0x1E, 0x1E, 0x0F, 
  0xFC, 0x01, 0x00, 0x0F, 0x80, 0x0F, 0xC0, 0x0F, 0x0F, 0x00, 0x78, 0x00, 
  0x00, 0x1E, 0x1E, 0x1E, 0x1E, 0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xFE, 
  0x01, 0x00, 0x1E, 0x00, 0x1F, 0xE0, 0x0F, 0x0F, 0x00, 0x3C, 0x00, 0x00, 
  0x0F, 0x0F, 0x3C, 0x0F, 0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xFF, 0x01, 
  0x00, 0x1E, 0x00, 0x1E, 0xE0, 0x0F, 0x0F, 0x00, 0x3C, 0x00, 0x00, 0x0F, 
  0x0F, 0x3C, 0x0F, 0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xEF, 0x01, 0x00, 
  0x1E, 0x00, 0x1E, 0xF0, 0x0F, 0x0F, 0x00, 0x1E, 0x00, 0x00, 0x07, 0x0F, 
  0x3C, 0x0F, 0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x00, 0x0F, 
  0x00, 0x0F, 0x70, 0x0F, 0x0F, 0x00, 0x1E, 0x00, 0x80, 0x07, 0x1E, 0x1E, 
  0x0F, 0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x00, 0x0F, 0x80, 
  0x07, 0x78, 0x0F, 0x0F, 0x00, 0x0F, 0x00, 0x80, 0x07, 0x1C, 0x0E, 0x0F, 
  0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x80, 0x07, 0xE0, 0x07, 
  0x38, 0x0F, 0xFF, 0x00, 0x0F, 0x00, 0x80, 0x03, 0x3C, 0x0F, 0x1E, 0x3C, 
  0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0xC0, 0x07, 0xF8, 0x03, 0x3C, 
  0x0F, 0xFF, 0x03, 0xFF, 0x03, 0xC0, 0x03, 0xF8, 0x07, 0x1E, 0x3C, 0x1F, 
  0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0xC0, 0x03, 0xF8, 0x03, 0x1C, 0x0F, 
  0xFE, 0x07, 0xFF, 0x07, 0xC0, 0x03, 0xF0, 0x03, 0x3E, 0x3E, 0x1F, 0x00, 
  0x00, 0x0F, 0x1E, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x07, 0x1C, 0x0F, 0xC0, 
  0x0F, 0xFF, 0x0F, 0xC0, 0x01, 0xF8, 0x07, 0xFC, 0x3F, 0x1F, 0x00, 0x00, 
  0x0F, 0x1E, 0xE0, 0x01, 0xF0, 0x01, 0x80, 0x0F, 0x1E, 0x0F, 0x00, 0x0F, 
  0x1F, 0x0F, 0xE0, 0x01, 0x3C, 0x0F, 0xF8, 0x3F, 0x00, 0x00, 0x00, 0x0F, 
  0x1E, 0xE0, 0x01, 0xF0, 0x00, 0x00, 0x1E, 0x0E, 0x0F, 0x00, 0x0F, 0x0F, 
  0x1E, 0xE0, 0x01, 0x1E, 0x1E, 0xF0, 0x3F, 0x00, 0x00, 0x00, 0x0F, 0x1E, 
  0xE0, 0x01, 0x78, 0x00, 0x00, 0x3E, 0x0E, 0x0F, 0x00, 0x1E, 0x0F, 0x1E, 
  0xE0, 0x01, 0x0E, 0x1C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 
  0x01, 0x7C, 0x00, 0x00, 0x3C, 0xFF, 0x7F, 0x00, 0x1E, 0x0F, 0x1E, 0xE0, 
  0x00, 0x0F, 0x3C, 0x00, 0x1C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 
  0x3C, 0x00, 0x00, 0x3C, 0xFF, 0x7F, 0x00, 0x1E, 0x0F, 0x1E, 0xF0, 0x00, 
  0x0F, 0x3C, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x1E, 
  0x00, 0x00, 0x3C, 0xFF, 0x7F, 0x00, 0x1E, 0x0F, 0x1E, 0xF0, 0x00, 0x0F, 
  0x3C, 0x00, 0x1E, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x1E, 0x00, 
  0x00, 0x1E, 0x00, 0x0F, 0x00, 0x1E, 0x0F, 0x1E, 0xF0, 0x00, 0x0F, 0x3C, 
  0x00, 0x0F, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x0F, 0x00, 0x00, 
  0x1E, 0x00, 0x0F, 0x00, 0x0E, 0x0F, 0x1E, 0x70, 0x00, 0x0F, 0x3C, 0x80, 
  0x0F, 0x00, 0x00, 0x00, 0x1E, 0x0F, 0xE0, 0x01, 0x0F, 0x00, 0x00, 0x1F, 
  0x00, 0x0F, 0x00, 0x0F, 0x0F, 0x1E, 0x70, 0x00, 0x1F, 0x1E, 0xC0, 0x07, 
  0x00, 0x06, 0x00, 0xFE, 0x0F, 0xE0, 0x01, 0x0F, 0x00, 0xC6, 0x0F, 0x00, 
  0x0F, 0x83, 0x0F, 0x1E, 0x0F, 0x78, 0x00, 0x3E, 0x1F, 0xF0, 0x03, 0x00, 
  0x0F, 0x00, 0xFC, 0x07, 0xE0, 0x01, 0xFF, 0x1F, 0xFF, 0x0F, 0x00, 0x0F, 
  0xFF, 0x07, 0xFE, 0x0F, 0x78, 0x00, 0xFC, 0x0F, 0xFC, 0x01, 0x00, 0x0F, 
  0x00, 0xF8, 0x03, 0xE0, 0x01, 0xFF, 0x1F, 0xFF, 0x07, 0x00, 0x0F, 0xFF, 
  0x03, 0xFC, 0x07, 0x78, 0x00, 0xF8, 0x07, 0xFC, 0x00, 0x00, 0x06, 0x00, 
  0xE0, 0x00, 0xE0, 0x01, 0xFF, 0x1F, 0xFC, 0x01, 0x00, 0x0F, 0xFF, 0x01, 
  0xF8, 0x03, 0x78, 0x00, 0xE0, 0x01, 0x3C, 0x00
};

// The somewhat larger font
#define large_digits_width 184
#define large_digits_height 32
static char large_digits_bits[] = {
  0x00, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x7E, 0xE0, 0x00, 0xC0, 0x01, 0xFE, 0x03, 0xFE, 0x00, 0x00, 0x1E, 
  0xFF, 0x0F, 0x00, 0x07, 0xFF, 0x3F, 0xF0, 0x03, 0xF0, 0x07, 0x00, 0x00, 
  0xE7, 0xF8, 0x03, 0xE0, 0x01, 0xFF, 0x07, 0xFF, 0x03, 0x00, 0x1F, 0xFF, 
  0x0F, 0xC0, 0x0F, 0xFF, 0x3F, 0xF8, 0x07, 0xF8, 0x0F, 0x00, 0x00, 0xE7, 
  0xFC, 0x07, 0xF0, 0x01, 0xFF, 0x0F, 0xFF, 0x07, 0x00, 0x1F, 0xFF, 0x0F, 
  0xE0, 0x0F, 0xFF, 0x3F, 0xFC, 0x0F, 0xFC, 0x1F, 0x00, 0x00, 0xE7, 0xFE, 
  0x0F, 0xF8, 0x01, 0x07, 0x0F, 0xE6, 0x0F, 0x80, 0x1F, 0x0F, 0x00, 0xF0, 
  0x03, 0x00, 0x3C, 0x1E, 0x1E, 0x3E, 0x1F, 0x00, 0x00, 0x7E, 0x1E, 0x0F, 
  0xFC, 0x01, 0x00, 0x0F, 0x80, 0x0F, 0xC0, 0x1F, 0x0F, 0x00, 0x78, 0x00, 
  0x00, 0x3C, 0x1E, 0x1E, 0x1E, 0x3E, 0x00, 0x00, 0x3C, 0x0F, 0x1E, 0xFE, 
  0x01, 0x00, 0x1E, 0x00, 0x1F, 0xC0, 0x1F, 0x0F, 0x00, 0x3C, 0x00, 0x00, 
  0x1E, 0x0F, 0x3C, 0x1E, 0x3E, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xFF, 0x01, 
  0x00, 0x1E, 0x00, 0x1F, 0xE0, 0x1F, 0x0F, 0x00, 0x3C, 0x00, 0x00, 0x1E, 
  0x0F, 0x3C, 0x0F, 0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xEF, 0x01, 0x00, 
  0x1E, 0x00, 0x1E, 0xE0, 0x1F, 0x0F, 0x00, 0x1E, 0x00, 0x00, 0x0F, 0x0F, 
  0x3C, 0x0F, 0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x00, 0x1E, 
  0x00, 0x1E, 0xF0, 0x1E, 0x0F, 0x00, 0x1E, 0x00, 0x00, 0x0F, 0x0F, 0x3C, 
  0x0F, 0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x00, 0x0F, 0x00, 
  0x1E, 0xF0, 0x1E, 0x0F, 0x00, 0x0F, 0x00, 0x00, 0x07, 0x0F, 0x3C, 0x0F, 
  0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x00, 0x0F, 0x00, 0x0F, 
  0x70, 0x1E, 0x0F, 0x00, 0x0F, 0x00, 0x80, 0x07, 0x1E, 0x1E, 0x0F, 0x3C, 
  0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x00, 0x0F, 0x80, 0x07, 0x78, 
  0x1E, 0x0F, 0x00, 0x0F, 0x00, 0x80, 0x07, 0x1C, 0x0E, 0x0F, 0x3C, 0x00, 
  0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x80, 0x07, 0xE0, 0x07, 0x38, 0x1E, 
  0xFF, 0x00, 0xFF, 0x03, 0x80, 0x03, 0x3C, 0x0F, 0x0F, 0x3C, 0x00, 0x00, 
  0x00, 0x0F, 0x1E, 0xE0, 0x01, 0xC0, 0x07, 0xF8, 0x03, 0x3C, 0x1E, 0xFF, 
  0x03, 0xFF, 0x07, 0xC0, 0x03, 0xF8, 0x07, 0x1E, 0x3C, 0x3F, 0x00, 0x00, 
  0x0F, 0x1E, 0xE0, 0x01, 0xC0, 0x03, 0xF8, 0x03, 0x1C, 0x1E, 0xFE, 0x07, 
  0xFF, 0x0F, 0xC0, 0x03, 0xF0, 0x03, 0x1E, 0x3C, 0x3F, 0x00, 0x00, 0x0F, 
  0x1E, 0xE0, 0x01, 0xE0, 0x01, 0xE0, 0x07, 0x1C, 0x1E, 0xC0, 0x0F, 0x1F, 
  0x0F, 0xC0, 0x01, 0xF8, 0x07, 0x3E, 0x3E, 0x3F, 0x00, 0x00, 0x0F, 0x1E, 
  0xE0, 0x01, 0xF0, 0x01, 0x80, 0x0F, 0x1E, 0x1E, 0x00, 0x0F, 0x0F, 0x1E, 
  0xE0, 0x01, 0x3C, 0x0F, 0xFC, 0x3F, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 
  0x01, 0xF0, 0x00, 0x00, 0x1E, 0x0E, 0x1E, 0x00, 0x0F, 0x0F, 0x1E, 0xE0, 
  0x01, 0x1E, 0x1E, 0xF8, 0x3F, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 
  0x78, 0x00, 0x00, 0x1E, 0x0E, 0x1E, 0x00, 0x1E, 0x0F, 0x1E, 0xE0, 0x01, 
  0x0E, 0x1C, 0xF0, 0x3F, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x7C, 
  0x00, 0x00, 0x3E, 0x0F, 0x1E, 0x00, 0x1E, 0x0F, 0x1E, 0xE0, 0x00, 0x0F, 
  0x3C, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x3C, 0x00, 
  0x00, 0x3C, 0x0F, 0x1E, 0x00, 0x1E, 0x0F, 0x1E, 0xF0, 0x00, 0x0F, 0x3C, 
  0x00, 0x3C, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x1E, 0x00, 0x00, 
  0x3C, 0xFF, 0xFF, 0x00, 0x1E, 0x0F, 0x1E, 0xF0, 0x00, 0x0F, 0x3C, 0x00, 
  0x1E, 0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x1E, 0x00, 0x00, 0x3C, 
  0xFF, 0xFF, 0x00, 0x1E, 0x0F, 0x1E, 0xF0, 0x00, 0x0F, 0x3C, 0x00, 0x1E, 
  0x00, 0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x1E, 0x00, 0x00, 0x3C, 0xFF, 
  0xFF, 0x00, 0x1E, 0x0F, 0x1E, 0xF0, 0x00, 0x0F, 0x3C, 0x00, 0x1E, 0x00, 
  0x00, 0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x0F, 0x00, 0x00, 0x1E, 0x00, 0x1E, 
  0x00, 0x1E, 0x0F, 0x1E, 0x70, 0x00, 0x0F, 0x3C, 0x00, 0x0F, 0x00, 0x00, 
  0x00, 0x0F, 0x1E, 0xE0, 0x01, 0x0F, 0x00, 0x00, 0x1E, 0x00, 0x1E, 0x00, 
  0x0E, 0x0F, 0x1E, 0x70, 0x00, 0x0F, 0x3C, 0x80, 0x0F, 0x00, 0x00, 0x00, 
  0x1E, 0x0F, 0xE0, 0x01, 0x0F, 0x00, 0x00, 0x1F, 0x00, 0x1E, 0x00, 0x0F, 
  0x0F, 0x1E, 0x70, 0x00, 0x1F, 0x1E, 0xC0, 0x07, 0x00, 0x06, 0x00, 0xFE, 
  0x0F, 0xE0, 0x01, 0x0F, 0x00, 0xC6, 0x0F, 0x00, 0x1E, 0x83, 0x0F, 0x1E, 
  0x0F, 0x78, 0x00, 0x3E, 0x1F, 0xF0, 0x03, 0x00, 0x0F, 0x00, 0xFC, 0x07, 
  0xE0, 0x01, 0xFF, 0x1F, 0xFF, 0x0F, 0x00, 0x1E, 0xFF, 0x07, 0xFE, 0x0F, 
  0x78, 0x00, 0xFC, 0x0F, 0xFC, 0x01, 0x00, 0x0F, 0x00, 0xF8, 0x03, 0xE0, 
  0x01, 0xFF, 0x1F, 0xFF, 0x07, 0x00, 0x1E, 0xFF, 0x03, 0xFC, 0x07, 0x78, 
  0x00, 0xF8, 0x07, 0xFC, 0x00, 0x00, 0x06, 0x00, 0xE0, 0x00, 0xE0, 0x01, 
  0xFF, 0x1F, 0xFC, 0x01, 0x00, 0x1E, 0xFF, 0x01, 0xF8, 0x03, 0x78, 0x00, 
  0xE0, 0x01, 0x3C, 0x00
};

#endif // __GRAPHICS_H__
