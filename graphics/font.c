/*

The MIT License (MIT)

Copyright (c) 2015 Johan Kanflo (github.com/kanflo)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "graphics.h"
#include "font.h"

#define FONT_SMALL (0)
#define FONT_LARGE (1)

// Return the width of the string of the given character in the specified font
// (FONT_SMALL or FONT_LARGE). The character spacing may be set with the
// kerning parameter. The small/large font has no kerning in the glyphs.
unsigned int measureString(char *str, unsigned int size, int kerning)
{
	unsigned int width = 0;
	unsigned char *widths;
	if (size == FONT_LARGE) {
		widths = large_widths;
	} else if (size == FONT_SMALL) {
		widths = small_widths;
	} else {
		return 0;
	}

	while(str && *str) {
		unsigned char ch = *str;
		if (ch >= min_font_ascii && ch <= max_font_ascii) {
			width += widths[ch - min_font_ascii] + kerning;
		}
		str++;
	}
	return width;
}

// Return the x offset of the given character in the specified font
// (FONT_SMALL or FONT_LARGE)
unsigned int xOffsetOfCharacter(unsigned char ch, unsigned int size)
{
	unsigned char *widths;
	if (size == FONT_LARGE) {
		widths = large_widths;
	} else if (size == FONT_SMALL) {
		widths = small_widths;
	} else {
		return 0;
	}

	unsigned int offset = 0, curChar = min_font_ascii;
	if (ch >= min_font_ascii && ch <= max_font_ascii) {
		while(curChar != ch) {
			unsigned int curWidth;
			curWidth = widths[curChar - min_font_ascii];
			// All glyphs start at an even 8 bit boundary
			if (curWidth % 8 != 0) {
				curWidth = 8 * ((curWidth + 8) / 8);
			}
			offset += curWidth;
			curChar++; 
		}
	}
	return offset;
}

// Draw string of given size and kerning at top/left (x, y)
void drawString(char *str, unsigned int size, int kerning, unsigned int x, unsigned int y)
{
	unsigned int height;
	unsigned char *widths;
	unsigned int glyphWidth;
	char *glyphs;

	if (size == FONT_LARGE) {
		height = large_digits_height;
		widths = large_widths;
		glyphWidth = large_digits_width;
		glyphs = large_digits_bits;
	} else if (size == FONT_SMALL) {
		height = small_digits_height;
		widths = small_widths;
		glyphWidth = small_digits_width;
		glyphs = small_digits_bits;
	} else {
		return;
	}

	while(str && *str) {
		unsigned char curChar = *str;
		if (curChar >= min_font_ascii && curChar <= max_font_ascii) {
			unsigned int xOffset = xOffsetOfCharacter(curChar, size);
			unsigned int curWidth;
			curWidth = widths[curChar - min_font_ascii];
			if (curWidth % 8 != 0) {
				curWidth = 8 * ((curWidth + 8) / 8);
			}
			OLED_SillyDrawPartialBMP(x, y, curWidth, height, xOffset, glyphWidth, glyphs);
			x += widths[curChar - min_font_ascii] + kerning;
		}
		str++;
	}
}
