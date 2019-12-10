#ifndef __FONT_BITS_H__
#define __FONT_BITS_H__

#include <stdint.h>

// Below are small samples of Ubuntu Condensed (font.ubuntu.com) needed
// to display temperatures. The characters represented are -.°0123456789
// in almost ascii order (the slash has been replaced by the degree sign)
#define min_font_ascii '-'
#define max_font_ascii '9'

// As Ubuntu Condensed is not a monospace font we need to keep track of
// the width of each character.
extern const uint32_t small_widths[];
extern const uint32_t large_widths[];

// The fonts are represented as one single image where each character begins
// on an even 8 bit boundary. To find the small character '.' we need to step
// over the character '-' which is 5 pixels wide. Rounding up to 8 we need to
// step over the first full byte on each row in small_digits_bits.

// The small font
#define small_digits_width 184
#define small_digits_height 28
extern const uint8_t small_digits_bits[];

// The somewhat larger font
#define large_digits_width 184
#define large_digits_height 32
extern const uint8_t large_digits_bits[];

#endif // __FONT_BITS_H__
