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

#ifndef __FONT_H__
#define __FONT_H__

#define FONT_SMALL (0)
#define FONT_LARGE (1)

// Return the width of the string of the given character in the specified font
// (FONT_SMALL or FONT_LARGE). The character spacing may be set with the
// kerning parameter. The small/large font has no kerning in the glyphs.
unsigned int measureString(char *str, unsigned int size, int kerning);

// Return the x offset of the given character in the specified font
// (FONT_SMALL or FONT_LARGE)
unsigned int xOffsetOfCharacter(unsigned char ch, unsigned int size);

// Draw string of given size and kerning at top/left (x, y)
void drawString(char *str, unsigned int size, int kerning, unsigned int x, unsigned int y);


#endif // __FONT_H__
