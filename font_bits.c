#include <stdint.h>

const uint32_t small_widths[] = {5, 4, 6, 13, 9, 13, 14, 15, 13, 13, 14, 14, 14};
const uint32_t large_widths[] = {6, 4, 8, 13, 9, 13, 14, 16, 13, 13, 14, 14, 14};

/** The fonts are represented as one single image where each character begins
 *  on an even 8 bit boundary. To find the small character '.' we need to step
 *  over the character '-' which is 5 pixels wide. Rounding up to 8 we need to
 *  step over the first full byte on each row in small_digits_bits.
 */

const uint8_t small_digits_bits[] = {
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

const uint8_t large_digits_bits[] = {
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
