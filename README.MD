# Monochrome graphics library

This library use full display size buffer so MCU must have enough RAM.

### Usage

```cpp
#include <PE_mGFX.h>

PE_mGFX mGFX = PE_mGFX(128, 64);

int main(void) {
    // First need to initialize graphics to create internal buffer
    mGFX.initialize();

    // Then you can draw

    // Draw pixel
    mGFX.pixel(/*x*/ 5, /*y*/ 5, /*color*/ PE_mGFX_WHITE);
    
    // Draw line
    mGFX.line(/*x1*/ 15, /*y1*/ 15, /*x2*/ 30, /*y2*/ 10, /*color*/ PE_mGFX_WHITE);

    // Draw rectangle
    mGFX.rectangle(/*x1*/ 64, /*y1*/ 32, /*x2*/ 127, /*y2*/ 63, /*color*/ PE_mGFX_WHITE);

    // Draw rectangle
    mGFX.circle(/*x*/ 64, /*x*/ 32, /*radius*/ 20, /*color*/ PE_mGFX_WHITE);

    //TODO draw bitmap and strings
}
```