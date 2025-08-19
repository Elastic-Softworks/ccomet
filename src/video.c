/*
        ====================================

                    V I D E O . C
	         CCOMET VIDEO FILE
           CG MOON / ELASTIC SOFTWORKS 2025
  
        ====================================
*/

#include <dpmi.h>
#include <string.h>
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

  if (mode == VID_MODE_13H) {

    if (mode == VID_MODE_13H) {

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

               vid_putpix()
	       ---
	       Draws a single pixel at the specified
	       (x, y) coordinates on the screen. Also
	       directly writes the 'color' byte to the
	       VGA mem buffer (0xA0000), color being an
	       index to the currently active 256-col
	       palette.

*/   

void vid_putpix(int x, int y, unsigned char color) {

  /* check the boundaries to prevent writing outside vid memory       */
  
  if (x >= 0 && x < SCREEN_WIDTH && y >= 0 && y < SCREEN_HEIGHT) {

    long offset = (long)y * SCREEN_WIDTH + x;   /* calc offset from
						   base of VGA memory */
    screen_buffer[offset] = color;
      
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
		 then being displayed to  the user in
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

                 vid_set_palette()
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

  int i;

  outp(0x3C8, 0);                     /* first tell the VGA card
				         "hey, we're starting at
				         color index 0, just fyi"  */

  
  /* then: write all 256-cols to the palette    !  !  !            */
  
  for (i = 0; i < 256; i++) {
    
    outp(0x3C9, palette[i].r >> 2);
    outp(0x3C9, palette[i].g >> 2);
    outp(0x3C9, palette[i].b >> 2);   /* and finally scale the 8-bit
				         values down to 6-bit so it
				         fits nice in snug in VGA   */
    
  }
  
}
