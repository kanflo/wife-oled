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
