#include "PE_mGFX.h"

#include <malloc.h>
#include <stdlib.h>
#include <string.h>

uint8_t PE_mGFX_initialize(PE_mGFX_Canvas_t *canvas)
{
    if ((canvas->data != NULL) || !(canvas->data = (uint8_t *) malloc(canvas->width * ((canvas->height + 7) / 8)))) {
        return 0;
    }

    PE_mGFX_clear(canvas);

    return 1;
}

void PE_mGFX_clear(PE_mGFX_Canvas_t *canvas)
{
    memset(canvas->data, 0, canvas->width * ((canvas->height + 7) / 8));
}

void PE_mGFX_pixel(PE_mGFX_Canvas_t *canvas, uint16_t x, uint16_t y, PE_mGFX_Color_t color)
{
    if (x >= canvas->width || y >= canvas->height) return;

    if (color == PE_mGFX_WHITE) {
        canvas->data[x + (y / 8) * canvas->width] |= 1u << (y % 8u);
    } else if (color == PE_mGFX_BLACK) {
        canvas->data[x + (y / 8) * canvas->width] &= ~(1u << (y % 8u));
    }
}

void PE_mGFX_line(PE_mGFX_Canvas_t *canvas, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, PE_mGFX_Color_t color)
{
    uint16_t diffX = abs(x1 - x0);
    uint16_t diffY = abs(y1 - y0);

    if (diffX == 0 && diffY == 0) {
        return;
    }

    int stepX = (x0 > x1) ? -1 : 1;
    int stepY = (y0 > y1) ? -1 : 1;

    diffY <<= 1u; // diffY is now 2*diffY
    diffX <<= 1u; // diffX is now 2*diffX

    PE_mGFX_pixel(canvas, x0, y0, color);

    if (diffX > diffY) {
        // Optimization for draw line with width > height
        int fraction = diffY - (diffX >> 1u);

        while (x0 != x1) {
            if (fraction >= 0) {
                y0       += stepY;
                fraction -= diffX;
            }

            x0       += stepX;
            fraction += diffY;

            PE_mGFX_pixel(canvas, x0, y0, color);
        }
    } else {
        // Optimization for draw line with width < height
        int fraction = diffX - (diffY >> 1u);

        while (y0 != y1) {
            if (fraction >= 0) {
                x0       += stepX;
                fraction -= diffY;
            }

            y0       += stepY;
            fraction += diffX;

            PE_mGFX_pixel(canvas, x0, y0, color);
        }
    }
}

void PE_mGFX_rectangle(PE_mGFX_Canvas_t *canvas, uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, PE_mGFX_Color_t color)
{
    PE_mGFX_line(canvas, x0, y0, x1, y0, color);
    PE_mGFX_line(canvas, x0, y1, x1, y1, color);
    PE_mGFX_line(canvas, x0, y0, x0, y1, color);
    PE_mGFX_line(canvas, x1, y0, x1, y1, color);
}

void PE_mGFX_circle(PE_mGFX_Canvas_t *canvas, uint16_t cx, uint16_t cy, uint16_t r, PE_mGFX_Color_t color)
{
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    PE_mGFX_pixel(canvas, cx, cy + r, color);
    PE_mGFX_pixel(canvas, cx, cy - r, color);
    PE_mGFX_pixel(canvas, cx + r, cy, color);
    PE_mGFX_pixel(canvas, cx - r, cy, color);

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        PE_mGFX_pixel(canvas,cx + x, cy + y, color);
        PE_mGFX_pixel(canvas,cx - x, cy + y, color);
        PE_mGFX_pixel(canvas,cx + x, cy - y, color);
        PE_mGFX_pixel(canvas,cx - x, cy - y, color);

        PE_mGFX_pixel(canvas,cx + y, cy + x, color);
        PE_mGFX_pixel(canvas,cx - y, cy + x, color);
        PE_mGFX_pixel(canvas,cx + y, cy - x, color);
        PE_mGFX_pixel(canvas,cx - y, cy - x, color);
    }
}

void PE_mGFX_bitmap(PE_mGFX_Canvas_t *canvas, uint16_t x, uint16_t y, PE_mGFX_Bitmap_t *bitmap, PE_mGFX_Color_t color)
{
    uint16_t width = (bitmap->width + 7) / 8;
    uint8_t byte   = 0;

    for (uint16_t j = 0; j < bitmap->height; j++, y++) {
        for (uint16_t i = 0; i < bitmap->width; i++) {
            if (!bitmap->lsb) {
                if (i & 7u) {
                    byte <<= 1u;
                } else {
                    byte = bitmap->data[j * width + i / 8];
                }

                if (byte & 0x80u) PE_mGFX_pixel(canvas, x + i, y, color);
            } else {
                if (i & 7u) {
                    byte >>= 1u;
                } else {
                    byte = bitmap->data[j * width + i / 8];
                }

                if (byte & 0x01u) PE_mGFX_pixel(canvas, x + i, y, color);
            }
        }
    }
}

void PE_mGFX_symbol(PE_mGFX_Canvas_t *canvas, uint16_t x, uint16_t y, char symbol, PE_mGFX_Font_t *font, PE_mGFX_Color_t color)
{
    uint16_t i, j, b;

    for (i = 0; i < font->height; i++) {
        b = font->bitmap[(symbol - 32) * font->height + i];

        for (j = 0; j < font->width; j++) {
            if ((b << j) & 0x8000) {
                PE_mGFX_pixel(canvas, x + j, y + i, (PE_mGFX_Color_t) color);
            } else {
                PE_mGFX_pixel(canvas, x + j, y + i, (PE_mGFX_Color_t) !color);
            }
        }
    }
}

void PE_mGFX_string(PE_mGFX_Canvas_t *canvas, uint16_t x, uint16_t y, const char *string, PE_mGFX_Font_t *font, PE_mGFX_Color_t color)
{
    while (*string) {
        PE_mGFX_symbol(canvas, x, y, *string, font, color);

        x += font->width;

        string++;
    }
}
