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
RGB pal_doom[256];

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
      case 246: pal_win256[i].r   = 192; pal_win256[i].g  = 192; pal_win256[i].b  = 192;  break;   /* light gray */
      case 247: pal_win256[i].r   = 128; pal_win256[i].g  = 128; pal_win256[i].b  = 128;  break;   /* medium gray */
      case 248: pal_win256[i].r   = 255; pal_win256[i].g  = 0;   pal_win256[i].b  = 0;    break;   /* bright red */
      case 249: pal_win256[i].r   = 0;   pal_win256[i].g  = 255; pal_win256[i].b  = 0;    break;   /* bright green */
      case 250: pal_win256[i].r   = 0;   pal_win256[i].g  = 0;   pal_win256[i].b  = 255;  break;   /* bright blue */
      case 251: pal_win256[i].r   = 255; pal_win256[i].g  = 255; pal_win256[i].b  = 0;    break;   /* bright yellow */
      case 252: pal_win256[i].r   = 255; pal_win256[i].g  = 0;   pal_win256[i].b  = 255;  break;   /* bright magenta */
      case 253: pal_win256[i].r   = 0;   pal_win256[i].g  = 255; pal_win256[i].b  = 255;  break;   /* bright cyan */
      case 254: pal_win256[i].r   = 255; pal_win256[i].g  = 255; pal_win256[i].b  = 255;  break;   /* white */
      case 255: pal_win256[i].r   = 0;   pal_win256[i].g  = 0;   pal_win256[i].b  = 0;    break;   /* black */

    }
  }
  
}

/* generate the DOOM palette  */

static const RGB doom_palette_data[256] = {

  {  0,   0,   0}, { 31,  23,  11}, { 23,  15,   7}, { 75,  75,  75}, {255, 255, 255}, { 27,  27,  27}, { 19,  19,  19}, { 11,  11,  11},
  {199, 199, 199}, {119, 119, 119}, { 83,  83,  83}, { 47,  47,  47}, {255, 155,   0}, {231, 119,   0}, {203,  95,   0}, {175,  71,   0},
  {143,  47,   0}, {119,  31,   0}, { 91,  15,   0}, { 67,   7,   0}, {255, 231,  75}, {255, 199,   0}, {255, 171,   0}, {255, 143,   0},
  {255, 107,   0}, {255,  75,   0}, {255,  43,   0}, {255,   7,   0}, {255,   0,   0}, {239,   0,   0}, {227,   0,   0}, {215,   0,   0},
  {203,   0,   0}, {191,   0,   0}, {179,   0,   0}, {167,   0,   0}, {155,   0,   0}, {139,   0,   0}, {127,   0,   0}, {115,   0,   0},
  {103,   0,   0}, { 87,   0,   0}, { 75,   0,   0}, { 63,   0,   0}, { 51,   0,   0}, { 39,   0,   0}, { 27,   0,   0}, { 15,   0,   0},
  {255, 215, 215}, {255, 199, 199}, {255, 183, 183}, {255, 171, 171}, {255, 155, 155}, {255, 135, 135}, {255, 119, 119}, {255,  99,  99},
  {255,  83,  83}, {255,  63,  63}, {255,  47,  47}, {255,  27,  27}, {255,  11,  11}, {239,   0,   0}, {227,   0,   0}, {215,   0,   0},
  {203,   0,   0}, {191,   0,   0}, {179,   0,   0}, {167,   0,   0}, {155,   0,   0}, {139,   0,   0}, {127,   0,   0}, {115,   0,   0},
  {103,   0,   0}, { 87,   0,   0}, { 75,   0,   0}, { 63,   0,   0}, {255, 235, 223}, {255, 227, 211}, {255, 219, 199}, {255, 211, 187},
  {255, 207, 179}, {255, 199, 167}, {255, 191, 155}, {255, 187, 147}, {255, 179, 135}, {247, 171, 123}, {239, 163, 115}, {231, 155, 107},
  {223, 147,  99}, {215, 139,  91}, {207, 131,  83}, {203, 127,  79}, {191, 123,  75}, {179, 115,  71}, {171, 111,  67}, {163, 107,  63},
  {155,  99,  59}, {143,  95,  55}, {135,  87,  51}, {127,  83,  47}, {119,  79,  43}, {107,  71,  39}, { 99,  67,  35}, { 91,  63,  31},
  { 83,  55,  27}, { 71,  47,  23}, { 63,  43,  19}, { 55,  35,  15}, { 47,  31,  11}, { 35,  23,   7}, { 27,  19,   0}, { 19,  11,   0},
  {255, 255, 239}, {255, 255, 215}, {255, 255, 191}, {255, 255, 167}, {255, 255, 143}, {255, 255, 119}, {255, 255,  95}, {255, 255,  71},
  {255, 255,  47}, {255, 235,  39}, {255, 219,  31}, {255, 203,  23}, {255, 187,  15}, {255, 171,   7}, {255, 155,   0}, {239, 143,   0},
  {227, 135,   0}, {211, 123,   0}, {199, 115,   0}, {187, 107,   0}, {175,  99,   0}, {163,  91,   0}, {151,  83,   0}, {139,  75,   0},
  {127,  67,   0}, {115,  59,   0}, {103,  51,   0}, { 91,  43,   0}, { 79,  35,   0}, { 67,  27,   0}, { 55,  19,   0}, { 43,  11,   0},
  {255, 255, 255}, {255, 235, 219}, {255, 215, 187}, {255, 199, 155}, {255, 179, 123}, {255, 163,  91}, {255, 143,  59}, {255, 127,  27},
  {243, 115,  23}, {235, 111,  15}, {223, 103,  15}, {215,  95,  11}, {203,  87,   7}, {195,  79,   0}, {183,  71,   0}, {175,  63,   0},
  {163,  59,   0}, {155,  51,   0}, {143,  47,   0}, {135,  39,   0}, {123,  35,   0}, {115,  31,   0}, {103,  23,   0}, { 95,  19,   0},
  { 87,  15,   0}, { 75,  11,   0}, { 67,   7,   0}, { 55,   0,   0}, { 47,   0,   0}, { 35,   0,   0}, { 27,   0,   0}, { 19,   0,   0},
  {255, 255, 255}, {255, 255, 215}, {255, 255, 179}, {255, 255, 143}, {255, 255, 107}, {255, 255,  71}, {255, 255,  35}, {255, 255,   0},
  {239, 231,   0}, {227, 219,   0}, {215, 203,   0}, {203, 191,   0}, {191, 179,   0}, {179, 167,   0}, {167, 155,   0}, {155, 143,   0},
  {143, 131,   0}, {131, 119,   0}, {119, 107,   0}, {107,  95,   0}, { 95,  83,   0}, { 83,  71,   0}, { 71,  59,   0}, { 59,  47,   0},
  { 47,  35,   0}, { 35,  23,   0}, { 23,  15,   0}, { 15,   7,   0}, {187, 255, 255}, {155, 255, 255}, {119, 255, 255}, { 83, 255, 255},
  { 47, 255, 255}, { 15, 255, 255}, {  0, 239, 255}, {  0, 203, 255}, {  0, 171, 255}, {  0, 135, 255}, {  0, 103, 255}, {  0,  71, 255},
  {  0,  39, 255}, {  0,   7, 255}, {  0,   0, 255}, {  0,   0, 231}, {  0,   0, 203}, {  0,   0, 179}, {  0,   0, 155}, {  0,   0, 131},
  {  0,   0, 107}, {  0,   0,  83}, {  0,   0,  59}, {  0,   0,  35}, {  0,   0,  15}, { 43,  87,  59}, { 35,  71,  47}, { 27,  55,  35},
  { 19,  43,  27}, { 15,  31,  19}, { 11,  23,  11}, {  7,  15,   7}, {187, 115, 159}, {175, 107, 143}, {163,  95, 131}, {151,  87, 119},
  {139,  79, 107}, {127,  75,  95}, {115,  67,  83}, {107,  59,  75}, { 95,  51,  63}, { 83,  43,  55}, { 71,  35,  43}, { 59,  31,  35},
  { 47,  23,  27}, { 35,  19,  19}, { 23,  11,  11}, { 15,   7,   7}, {219, 195, 187}, {203, 179, 167}, {191, 163, 155}, {175, 151, 139}

};

for (i = 0; i < 256; i++) {

  pal_doom[i] = doom_palette_data[i];

}

/* load the default palettes */

pal_load(pal_gray, "GRAYSCALE");
pal_load(pal_sepia, "SEPIA");
pal_load(pal_vga, "VGA");
pal_load(pal_win256, "WINDOWS");
pal_load(pal_doom, "DOOM");

pal_count = 5;  

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

    return -1;		    /* no free slots available */
    
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
