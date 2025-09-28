/*
        ====================================

                      P A L . C
	     CCOMET PALETTE HEADER FILE
           CG MOON / ELASTIC SOFTWORKS 2025
  
         ====================================
*/

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

/* 
              ======================
	           --- SETUP ---
              ======================
*/

#include	<string.h>
#include	<stdio.h>

#include	"pal.h"
#include	"video.h"

static		Pal		pal[PAL_MAX];
static int	pal_active	= -1;
static int	pal_count	= 0;

/*
              ======================
                 --- ARRAYS ---
              ======================
*/

RGB pal_vga[256];

RGB pal_vga_16[16] = {

  {0, 0, 0},        	/* 0 - black */
  {0, 0, 170},      	/* 1 - blue */
  {0, 170, 0},      	/* 2 - green */
  {0, 170, 170},    	/* 3 - cyan */
  {170, 0, 0},      	/* 4 - red */
  {170, 0, 170},    	/* 5 - magenta */
  {170, 85, 0},     	/* 6 - brown */
  {170, 170, 170},  	/* 7 - light gray */
  {85, 85, 85},     	/* 8 - dark gray */
  {85, 85, 255},    	/* 9 - light blue */
  {85, 255, 85},    	/* 10 - light green */
  {85, 255, 255},   	/* 11 - light cyan */
  {255, 85, 85},    	/* 12 - light red */
  {255, 85, 255},   	/* 13 - light magenta */
  {255, 255, 85},   	/* 14 - yellow */
  {255, 255, 255}   	/* 15 - white */
    
};

RGB pal_gray[256];
RGB pal_sepia[256];
RGB pal_win256[256];

/*

  		pal_init();
		  ---
		  Initialize the palette manager
		  and create default palettes
  
*/

void pal_init(void) {

  int i;

  /* clear all of the palette slots */

  for (i = 0; i < PAL_MAX; i++) {

    pal[i].active 	= 0;
    
    strcpy(pal[i].name, "");
    
  }

  /* generate the grayscale palette */

  for (i = 0; i < 256; i++) {

    pal_gray[i].r 	= i;
    pal_gray[i].g 	= i;
    pal_gray[i].b	= i;
    
  }

  /* generate the sepia palette */

  for (i = 0; i < 256; i++) {

    int _gray 	= i;
    
    pal_sepia[i].r	= (_gray > 206) ? 255 : _gray + 49;
    pal_sepia[i].g	= (_gray > 227) ? 255 : _gray + 28;
    pal_sepia[i].b	= (_gray > 150) ? _gray - 105 : 0;
    
  }

/* generate the 256-color VGA palette */

for (i = 0; i < 256; i++) {

  if (i < 16) {

    pal_vga[i] = pal_vga_16[i];

  } else {

    pal_vga[i].r = (i >> 5) * 36;        /* =ed: 0-7 * 36 */
    pal_vga[i].g = ((i >> 2) & 7) * 36;  /* Green: 0-7 * 36 */
    pal_vga[i].b = (i & 3) * 85;         /* Blue: 0-3 * 85 */

  }
  
}

/* generate the Windows 95/98/NT 256-color palette */

for (i = 0; i < 256; i++) {

  if (i < 16) {

    /* first 16 colors - standard VGA colors */

    pal_win256[i] = pal_vga_16[i];

  } else if (i >= 16 && i < 232) {

    /* colors 16-231: 6x6x6 RGB color cube */

    int idx = i - 16;
    int r = idx / 36;         /* red: 0-5 (idx / 36) */
    int g = (idx % 36) / 6;   /* green: 0-5 ((idx % 36) / 6) */
    int b = idx % 6;          /* blue: 0-5 (idx % 6) */
    
    pal_win256[i].r = (r * 255) / 5;    /* scale 0-5 to 0-255 */
    pal_win256[i].g = (g * 255) / 5;
    pal_win256[i].b = (b * 255) / 5;

  } else if (i >= 232 && i < 246) {

    /* colors 232-245: 14 shades of gray */

    int gray = 17 + ((i - 232) * 238) / 13; 

    pal_win256[i].r = gray;
    pal_win256[i].g = gray;
    pal_win256[i].b = gray;

  } else {

    /* colors 246-255: system colors (approximated) */

    switch (i) {
      case 246: pal_win256[i].r = 192; pal_win256[i].g = 192; pal_win256[i].b = 192; break;   /* Light gray */
      case 247: pal_win256[i].r = 128; pal_win256[i].g = 128; pal_win256[i].b = 128; break;   /* Medium gray */
      case 248: pal_win256[i].r = 255; pal_win256[i].g = 0;   pal_win256[i].b = 0;   break;   /* Bright red */
      case 249: pal_win256[i].r = 0;   pal_win256[i].g = 255; pal_win256[i].b = 0;   break;   /* Bright green */
      case 250: pal_win256[i].r = 0;   pal_win256[i].g = 0;   pal_win256[i].b = 255; break;   /* Bright blue */
      case 251: pal_win256[i].r = 255; pal_win256[i].g = 255; pal_win256[i].b = 0;   break;   /* Bright yellow */
      case 252: pal_win256[i].r = 255; pal_win256[i].g = 0;   pal_win256[i].b = 255; break;   /* Bright magenta */
      case 253: pal_win256[i].r = 0;   pal_win256[i].g = 255; pal_win256[i].b = 255; break;   /* Bright cyan */
      case 254: pal_win256[i].r = 255; pal_win256[i].g = 255; pal_win256[i].b = 255; break;   /* White */
      case 255: pal_win256[i].r = 0;   pal_win256[i].g = 0;   pal_win256[i].b = 0;   break;   /* Black */

    }
  }
  
}

/* load the default palettes */

pal_load(pal_gray, "GRAYSCALE");
pal_load(pal_sepia, "SEPIA");
pal_load(pal_vga, "VGA");
pal_load(pal_win256, "WINDOWS");

pal_count = 4;  

}

/*

  		pal_load()
		---
		Load the palette data
		into a slot
  
*/

int pal_load(const RGB *pal_data, const char *name) {

  int i;

  if (pal_count >= PAL_MAX) {

    return -1;		/* no free slots available */
    
  }

  /* copy over the palette data */

  for (i = 0; i < PAL_SIZE; i++) {

    pal[pal_count].colors[i] = pal_data[i];
    
  }

  /* set the palette name and mark it as active */

  strncpy(pal[pal_count].name, name, 31);
  
  pal[pal_count].name[31] 	= '\0';
  pal[pal_count].active 	= 1;

  return pal_count++;
  
}

/*

  		pal_set_active()
  		---
  		Set the active palette
  		and apply it
  
 */

void pal_set_active(int pal_id) {

  if (pal_id >= 0 && pal_id < pal_count &&
      pal[pal_id].active) {

    pal_active = pal_id;

    pal_apply_current();
    
  }
  
}

int pal_get_active(void) {

  return pal_active;
  
}

/*

  		pal_apply_current();
		---
		Apply the current palette
		to the video hardware.
  
 */

void pal_apply_current(void) {

  if (pal_active >= 0 && pal_active < pal_count) {

    vid_set_pal(pal[pal_active].colors);
    
  }
  
}
