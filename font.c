/*

    Copyright (c) 2019 Johan Kanflo (github.com/kanflo)

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

#include "ssd1306_utils.h"
#include "font.h"
#include "font_bits.h"

/**
 * @brief      Return the width of the string of the given character in the specified font.
 *
 * @param      str      The string
 * @param[in]  size     Font size (FONT_SMALL or FONT_LARGE)
 * @param[in]  kerning  Kerning between characters
 *
 * @return     { description_of_the_return_value }
 */
uint32_t font_string_width(char *str, uint32_t size, int32_t kerning)
{
    uint32_t width = 0;
    uint32_t *widths;
    if (size == FONT_LARGE) {
        widths = (uint32_t*) large_widths;
    } else if (size == FONT_SMALL) {
        widths = (uint32_t*) small_widths;
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

/**
 * @brief      Return the x offset of the given character in the specified font
 *
 * @param[in]  ch         Character in the Ubuntu font
 * @param[in]  font_size  Font size (FONT_SMALL or FONT_LARGE)
 *
 * @return     x offset of character
 */
uint32_t x_offset_of_character(unsigned char ch, uint32_t font_size)
{
    uint32_t *widths;
    if (font_size == FONT_LARGE) {
        widths = (uint32_t*) large_widths;
    } else if (font_size == FONT_SMALL) {
        widths = (uint32_t*) small_widths;
    } else {
        return 0;
    }

    uint32_t offset = 0, cur_char = min_font_ascii;
    if (ch >= min_font_ascii && ch <= max_font_ascii) {
        while(cur_char != ch) {
            uint32_t cur_width;
            cur_width = widths[cur_char - min_font_ascii];
            // All glyphs start at an even 8 bit boundary
            if (cur_width % 8 != 0) {
                cur_width = 8 * ((cur_width + 8) / 8);
            }
            offset += cur_width;
            cur_char++; 
        }
    }
    return offset;
}

// Draw string of given size and kerning at top/left (x, y)

/**
 * @brief      Draw string using the Ubuntu font
 *
 * @param[in]  dev      Our SSD1396 device
 * @param[in]  buffer   Our frame buffer
 * @param[in]  str      The string
 * @param[in]  size     The size (FONT_LARGE or FONT_SMALL)
 * @param[in]  kerning  Kerning between characters
 * @param[in]  x        x pos on display
 * @param[in]  y        y pos on display
 */
void font_draw(const ssd1306_t *dev, uint8_t *buffer, char *str, uint32_t size, int kerning, uint32_t x, uint32_t y)
{
    uint32_t height;
    const uint32_t *widths;
    uint32_t glyph_width;
    const uint8_t *glyphs;
    if (size == FONT_LARGE) {
        height = large_digits_height;
        widths = large_widths;
        glyph_width = large_digits_width;
        glyphs = large_digits_bits;
    } else if (size == FONT_SMALL) {
        height = small_digits_height;
        widths = small_widths;
        glyph_width = small_digits_width;
        glyphs = small_digits_bits;
    } else {
        return;
    }

    while(str && *str) {
        unsigned char cur_char = *str;
        if (cur_char >= min_font_ascii && cur_char <= max_font_ascii) {
            uint32_t x_offs = x_offset_of_character(cur_char, size);
            uint32_t cur_width;
            cur_width = widths[cur_char - min_font_ascii];
            if (cur_width % 8 != 0) {
                cur_width = 8 * ((cur_width + 8) / 8);
            }
            ssd1306_sillydraw_partial_bmp(dev, buffer, x, y, cur_width, height, x_offs, glyph_width, glyphs);
            x += widths[cur_char - min_font_ascii] + kerning;
        }
        str++;
    }
}
