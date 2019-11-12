#ifndef PE_MGFX_H
#define PE_MGFX_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

typedef enum {
    PE_mGFX_BLACK,
    PE_mGFX_WHITE,
} PE_mGFX_Color_t;

typedef struct {
    uint8_t *data;
    uint16_t width;
    uint16_t height;
    uint8_t lsb;
} PE_mGFX_Bitmap_t;

typedef struct {
    const uint16_t *bitmap;
    uint8_t width;
    uint8_t height;
} PE_mGFX_Font_t;

typedef struct {
    uint8_t *data;
    uint8_t width;
    uint8_t height;
} PE_mGFX_Canvas_t;

/**
 * Initialize internal buffer
 *
 * @param canvas
 *
 * @return
 */
uint8_t PE_mGFX_initialize(PE_mGFX_Canvas_t *canvas);

/**
 * Clear buffer data
 *
 * @param canvas
 */
void PE_mGFX_clear(PE_mGFX_Canvas_t *canvas);

/**
 * Draw pixel
 *
 * @param canvas
 * @param x
 * @param y
 * @param color
 */
void PE_mGFX_pixel(PE_mGFX_Canvas_t *canvas, uint16_t x, uint16_t y, PE_mGFX_Color_t color);

/**
 * Draw line
 *
 * @param canvas
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param color
 */
void PE_mGFX_line(PE_mGFX_Canvas_t *canvas, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, PE_mGFX_Color_t color);

/**
 * Draw rectangle
 *
 * @param canvas
 * @param x0
 * @param y0
 * @param x1
 * @param y1
 * @param color
 */
void PE_mGFX_rectangle(PE_mGFX_Canvas_t *canvas, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, PE_mGFX_Color_t color);

/**
 * Draw circle
 *
 * @param canvas
 * @param cx
 * @param cy
 * @param r
 * @param color
 */
void PE_mGFX_circle(PE_mGFX_Canvas_t *canvas, uint16_t cx, uint16_t cy, uint16_t r, PE_mGFX_Color_t color);

/**
 * Draw bitmap
 *
 * @param canvas
 * @param x
 * @param y
 * @param bitmap
 * @param color
 */
void PE_mGFX_bitmap(PE_mGFX_Canvas_t *canvas, uint16_t x, uint16_t y, PE_mGFX_Bitmap_t *bitmap, PE_mGFX_Color_t color);

/**
 * Draw single char
 *
 * @param canvas
 * @param x
 * @param y
 * @param symbol
 * @param font
 * @param color
 */
void PE_mGFX_symbol(PE_mGFX_Canvas_t *canvas, uint16_t x, uint16_t y, char symbol, PE_mGFX_Font_t *font, PE_mGFX_Color_t color);

/**
 * Draw string
 *
 * @param canvas
 * @param x
 * @param y
 * @param string
 * @param font
 * @param color
 */
void PE_mGFX_string(PE_mGFX_Canvas_t *canvas, uint16_t x, uint16_t y, const char *string, PE_mGFX_Font_t *font, PE_mGFX_Color_t color);

#ifdef __cplusplus
}
#endif

#endif //PE_MGFX_H
