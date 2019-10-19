# Monochrome graphics library

This library use full display size buffer so MCU must have enough RAM.

### Usage

```cpp
#include <PE_mGFX.h>
#include <PE_mGFX_Font_05x07.h>

static unsigned char bitmap0Data [] = {/* bitma bytes here */};

PE_mGFX_Bitmap_t bitmap = {
    .data = bitmap0Data,
    .width = 128,
    .height = 64,
    .lsb = 0,
};

void mGFX_flush(const uint8_t *data, uint16_t size) {
    //TODO write to display logic here
}

PE_mGFX mGFX = PE_mGFX(128, 64, mGFX_flush);

int main(void) {
    // First need to initialize graphics to create internal buffer
    mGFX.initialize();

    // Then you can draw

    mGFX.line(0, 0, 127, 63, PE_mGFX_WHITE);
    mGFX.line(0, 63, 127, 0, PE_mGFX_WHITE);
    mGFX.rectangle(0, 0, 127, 63, PE_mGFX_WHITE);
    mGFX.circle(63, 31, 31, PE_mGFX_WHITE);

    // Flush buffer to display
    mGFX.flush();

    // Clear buffer
    mGFX.flush();

    // Draw strings
    mGFX.string(0, 0, "Hello World", &PE_mGFX_Font_05x07, PE_mGFX_WHITE);

    // Draw bitmaps
    mGFX.bitmap(0, 16, &bitmap, PE_mGFX_WHITE);

    // Flush buffer to display
    mGFX.flush();
}
```

For more information about methods arguments see in ```PE_mGFX.h``` file.