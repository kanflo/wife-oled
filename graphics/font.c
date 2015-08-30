/*

	Copyright (c) 2015 Johan Kanflo (github.com/kanflo)

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

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
