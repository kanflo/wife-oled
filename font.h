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

#ifndef __FONT_H__
#define __FONT_H__

#include <stdint.h>
#include <ssd1306/ssd1306.h>

#define FONT_SMALL (0)
#define FONT_LARGE (1)


/**
 * @brief      Return the width of the string of the given character in the specified font.
 *
 * @param      str      The string
 * @param[in]  size     Font size (FONT_SMALL or FONT_LARGE)
 * @param[in]  kerning  Kerning between characters
 *
 * @return     { description_of_the_return_value }
 */
uint32_t font_string_width(char *str, uint32_t size, int32_t kerning);

/**
 * @brief      Return the x offset of the given character in the specified font
 *
 * @param[in]  ch         Character in the Ubuntu font
 * @param[in]  font_size  Font size (FONT_SMALL or FONT_LARGE)
 *
 * @return     x offset of character
 */
uint32_t x_offset_of_character(unsigned char ch, uint32_t font_size);

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
void font_draw(const ssd1306_t *dev, uint8_t *buffer, char *str, uint32_t size, int kerning, uint32_t x, uint32_t y);

#endif // __FONT_H__
