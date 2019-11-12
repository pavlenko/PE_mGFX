#ifndef PE_M_GFX_TYPES_H
#define PE_M_GFX_TYPES_H

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

#ifdef __cplusplus
}
#endif

#endif //PE_M_GFX_TYPES_H
