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

#ifndef __SSD1306_UTILS_H__
#define __SSD1306_UTILS_H__

#include <stdint.h>
#include <ssd1306/ssd1306.h>


/**
 * @brief      A silly method to draw BMPs.
 *
 * @param[in]  dev     SSD1306 device handle
 * @param      fb      Frame buffer
 * @param[in]  x       x position
 * @param[in]  y       y position
 * @param[in]  w       width of image (must be a multiple of 8)
 * @param[in]  h       height of image
 * @param      bmp     BMP data
 */
void ssd1306_sillydraw_bmp(const ssd1306_t *dev, uint8_t *fb, uint32_t x, uint32_t y, uint32_t w, uint32_t h, const uint8_t *bmp);


/**
 * @brief      A silly method to draw parts of BMPs
 *
 * @param[in]  dev     SSD1306 device handle
 * @param      fb      Frame buffer
 * @param[in]  x       x position
 * @param[in]  y       y position
 * @param[in]  w       width of image (must be a multiple of 8)
 * @param[in]  h       height of image
 * @param[in]  x_skip  number of pixels to skip from left
 * @param[in]  bmp_w   BMP width
 * @param      bmp     BMP data
 */
void ssd1306_sillydraw_partial_bmp(const ssd1306_t *dev, uint8_t *fb, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t x_skip, uint32_t bmp_w, const uint8_t *bmp);

/**
 * @brief      Fade out display
 *
 * @param[in]  dev   SSD1306 device handle
 *
 * @return     always 0
 */
int ssd1306_fade_out(const ssd1306_t *dev);

/**
 * @brief      Fade in display
 *
 * @param[in]  dev   SSD1306 device handle
 *
 * @return     always 0
 */
int ssd1306_fade_in(const ssd1306_t *dev);


#endif // __SSD1306_UTILS_H__
