//File Name: gfx.cpp
//Description: This defines the implementation for the graphics fx library

//Include Files
#include "gfx.h"
#include "hspi.h"

//Defines
#ifndef _swap_int16_t
#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#endif

#ifndef abs
#define abs(x) (x < 0 ? (x * -1) : x)
#endif
//Private Constants

//Private Variables

//Public Constants

//Public Variables

//Private Function Prototypes

//Public Function Prototypes

//Private Function Definitions

//Public Function Definitions
void TFT_GFX::setAddrWindow(uint16_t x1, uint16_t y1, uint16_t w, uint16_t h)
{
    uint16_t x2 = (x1 + w - 1);
    uint16_t y2 = (y1 + h - 1);
	// Set column range.
	hspi_cmd(this->spiInstance, 0x2A);
	hspi_w16(this->spiInstance, x1);
	hspi_w16(this->spiInstance, x2);
	
	// Set row range.
	hspi_cmd(this->spiInstance, 0x2B);
	hspi_w16(this->spiInstance, y1);
	hspi_w16(this->spiInstance, y2);
	
	// Set 'write to RAM'
	hspi_cmd(this->spiInstance, 0x2C);
}

void TFT_GFX::writePixel(int16_t x, int16_t y, uint16_t color) 
{
    if((x >= 0) && (x < TFT_WIDTH) && (y >= 0) && (y < TFT_HEIGHT)) 
    {
        setAddrWindow(x, y, 1, 1);
        hspi_w16(this->spiInstance, color);
    }
}

void TFT_GFX::writeFillRect(int16_t x, int16_t y,
  int16_t w, int16_t h, uint16_t color) {
    if(w && h) {                            // Nonzero width and height?
        if(w < 0) {                         // If negative width...
            x +=  w + 1;                    //   Move X to left edge
            w  = -w;                        //   Use positive width
        }
        if(x < TFT_WIDTH) {                    // Not off right
            if(h < 0) {                     // If negative height...
                y +=  h + 1;                //   Move Y to top edge
                h  = -h;                    //   Use positive height
            }
            if(y < TFT_HEIGHT) {               // Not off bottom
                int16_t x2 = x + w - 1;
                if(x2 >= 0) {               // Not off left
                    int16_t y2 = y + h - 1;
                    if(y2 >= 0) {           // Not off top
                        // Rectangle partly or fully overlaps screen
                        if(x  <  0)       { x = 0; w = x2 + 1; } // Clip left
                        if(y  <  0)       { y = 0; h = y2 + 1; } // Clip top
                        if(x2 >= TFT_WIDTH)  { w = TFT_WIDTH  - x;   } // Clip right
                        if(y2 >= TFT_HEIGHT) { h = TFT_HEIGHT - y;   } // Clip bottom
                        writeFillRectPreclipped(x, y, w, h, color);
                    }
                }
            }
        }
    }
}

inline void TFT_GFX::writeFillRectPreclipped(int16_t x, int16_t y,
  int16_t w, int16_t h, uint16_t color) {
    setAddrWindow(x, y, w, h);
    writeColor(color, (uint32_t)w * h);
}

void TFT_GFX::writeColor(uint16_t color, uint32_t len){
	for(int i = 0; i < len; i++){
		hspi_w16(this->spiInstance, color);
	}
}

void inline TFT_GFX::writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    if((x >= 0) && (x < TFT_WIDTH) && h) { // X on screen, nonzero height
        if(h < 0) {                     // If negative height...
            y +=  h + 1;                //   Move Y to top edge
            h  = -h;                    //   Use positive height
        }
        if(y < TFT_HEIGHT) {               // Not off bottom
            int16_t y2 = y + h - 1;
            if(y2 >= 0) {               // Not off top
                // Line partly or fully overlaps screen
                if(y  <  0)       { y = 0; h = y2 + 1; } // Clip top
                if(y2 >= TFT_HEIGHT) { h = TFT_HEIGHT - y;   } // Clip bottom
                writeFillRectPreclipped(x, y, 1, h, color);
            }
        }
    }
}

void inline TFT_GFX::writeFastHLine(int16_t x, int16_t y, int16_t w,
  uint16_t color) {
    if((y >= 0) && (y < TFT_HEIGHT) && w) { // Y on screen, nonzero width
        if(w < 0) {                      // If negative width...
            x +=  w + 1;                 //   Move X to left edge
            w  = -w;                     //   Use positive width
        }
        if(x < TFT_WIDTH) {                 // Not off right
            int16_t x2 = x + w - 1;
            if(x2 >= 0) {                // Not off left
                // Line partly or fully overlaps screen
                if(x  <  0)       { x = 0; w = x2 + 1; } // Clip left
                if(x2 >= TFT_WIDTH)  { w = TFT_WIDTH  - x;   } // Clip right
                writeFillRectPreclipped(x, y, w, 1, color);
            }
        }
    }
}