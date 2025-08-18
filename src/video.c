/*
        ====================================

                    V I D E O . C
	         CCOMET VIDEO FILE
           CG MOON / ELASTIC SOFTWORKS 2025
  
        ====================================
*/

#include <dpmi.h>
#include <string.h>
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

void vid_setmode(int mode) {

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

    vid_setmode(VID_MODE_TEXT);
    
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


