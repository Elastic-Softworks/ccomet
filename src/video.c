/* 
        ====================================

                    V I D E O . C
	         CCOMET VIDEO FILE
           CG MOON / ELASTIC SOFTWORKS 2025
  
        ====================================
*/

```c
/* CCOMET - OPEN-SOURCE GAME AND VISUAL ENGINE FOR DOS COMPATIBLES
 * Copyright (C) 2025  CG MOON / ELASTIC SOFTWORKS
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
```

#include <dpmi.h>
#include <string.h>
#include <stdlib.h>
#include <pc.h>
#include <dos.h>
#include "ccomet.h"

static unsigned char screen_buffer[SCREEN_SIZE];

/*

	       vid_setmode()
	       ---
	       Sets the DPMI video mode to the
	       mode of your choice. See video.h for
	       the different modes defined in the
	       constants.
	      
*/

void vid_set_mode(int mode) {

  __dpmi_regs r;
  r.x.ax = mode;
  __dpmi_int(0x10, &r);

  if  (mode == VID_MODE_13H) {

    if  (mode == VID_MODE_13H) {

      memset(screen_buffer, 0, SCREEN_SIZE);
      
    }
    
  }
  
}

/*

               vid_close()
	       ---
	       A wrapper function to close out
	       of the 13h mode and switch back
	       to text mode. That's all it does
	       for now, but just you wait. There's
	       a bright future in store for this
	       function, I'll tell you hwat.
  
*/

void vid_close(void) {

    vid_set_mode(VID_MODE_TEXT);
    
}

/*

               vid_draw_px()
	       ---
	       Draws a single pixel at the specified
	       (x, y) coordinates on the screen. Also
	       directly writes the 'color' byte to the
	       VGA mem buffer (0xA0000), 'color' being an
	       index to the currently active 256-col
	       palette.

*/   

void vid_draw_px(int x, int y, unsigned char color) {

  /* check the boundaries to prevent writing outside vid memory       */
  
  if  (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {

    long  offset = (long)y * SCREEN_WIDTH + x;   /* calc offset from
						   base of VGA memory */
    screen_buffer[offset]  = color;
      
    }
  
}

/*

        vid_present()
		 ---
		 Copies the entire contents of the
		 off-screen drawing buffer to VGA
		 video mem. Must-have function for
		 any kind of double-buffering, as
		 it ensures that all drawing
		 operations are done OFF SCREEN,
		 then being displayed to the player in
		 one quick flicker-free update.

*/

void vid_present(void) {

  dosmemput(screen_buffer, SCREEN_SIZE, VGA_MEMBASE);
  
}

/*

         vid_clearbuffer()
		 ---
		 Clears entire off-screen buffer
		 to a single color (the BG in
		 most instances) using memset()
		 to fill the buffer with the color
		 specified by whatever byte. 
		 Typically, you'd want to call this
		 at the beginning of each frame so
		 as to erase the contents of the last
		 frame.
*/

void vid_clear_buffer(unsigned char color) {

  memset(screen_buffer, color, SCREEN_SIZE);
  
}

/*

                 vid_set_pal()
		 ---
		 Loads a fresh 256-col palette into
		 the VGA hardware. Takes a pointer
		 to an array of 256 RGB structures
		 as the input. Basically it just
		 writes the RGB values to the VGAs
		 I/O ports (0x3c8 and 0x3C9). The
		 8-bit values then get shrunk to
		 6-bit (0-63) format.
  
*/

void vid_set_pal(const RGB *palette) {

  int  i;

  outp(0x3C8, 0);                     /* first tell the VGA card
				         "hey, we're starting at
				         color index 0, just fyi"  */

  
  /* then: write all 256-cols to the palette    !  !  !            */
  
  for  (i = 0; i < 256; i++) {
    
    outp(0x3C9, palette[i].r >> 2);
    outp(0x3C9, palette[i].g >> 2);
    outp(0x3C9, palette[i].b >> 2);   /* and finally scale the 8-bit
				         				 values down to 6-bit so it
				         			     fits nice n snug in VGA   */
    
  }
  
}

/*

          vid_draw_line()
		  ---
		  Use's Bresenham's line algo
		  to draw a line between 2 points
		  (x1, y1) and (x2, y2) with a
		  given color. It calculates the
		  journey of the line on a horizontal
		  (dx) and vertical (dy) basis to
		  find the end point. As it does this,
		  the algo keeps track of a running
		  "error" count, which tracks how
		  far the pixels of the line have
		  drifted apart from the 'perfect'
		  mathetmatical line.
		  
		  Once the algo figure
		  out which of the possible pixel
		  spaces to fill the line it calls
		  upon vid_draw_px() to draw the
		  pixels and their color values to
		  the corresponding spaces.
  
*/

void vid_draw_line(int x1, int y1, int x2, int y2, unsigned char color) {

  int    dx, dy, sx, sy, err, e2;

  dx   =  abs(x2 - x1);
  dy   = -abs(y2 - y1);

  sx   =  x1 < x2 ? 1 : -1;
  sy   =  y1 < y2 ? 1 : -1;

  err  =  dx + dy;

  while (1) {

    vid_draw_px(x1, y1, color);

    if  (x1 == x2 && y1 == y2) break;

    e2  = 2 * err;

    if  (e2 >= dy) {

      err  += dy;
       x1  += sx; 
      
    }

    if  (e2 <= dx) {

      err += dx;
      y1 += sy;
      
    }
    
  }
  
}

/*

                 vid_draw_rect()
				 ---
				 Draws the outline of a rectangle
				 using whatever color is specified.
				 (x, y) is top-left corner. It calls
				 upon vid_draw_line() four times to
				 accomplish its rectangle drawing goal.
  
*/ 

/*

                 vid_draw_rect_fill()
				 ---
				 Same as above, only now the rectangle
				 has the (_fill) tag and as with any
				 (_draw) func ending with a (_fill) tag
				 it will draw this rectangle full up.
  
*/ 

/* TODO : REMOVE (_FILL) AND MAKE A FUNC EXCLUSIVELY FOR
          FILLING SHAPES SO THAT WE DON'T HAVE TO MAKE A
		  BUNCH OF EXTRA VARIABLES THAT WE DON'T HAVE TO
		  (HAVING (_FILL) IS A STOP-GAP SOLUTION FOR NOW)  */

/*

                 vid_draw_circle()
				 ---
				 Similar to above methods, draws a circle
				 via (cX, cY) for the centerX and centerY
				 respectively. Once pulling the radius,
				 it uses the Midpoint Circle Algorithm for
				 efficient, inter-only calculations.
  
*/ 
