/*
        ====================================

                    V I D E O . H
	            CCOMET VIDEO HEADER FILE
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

#ifndef VIDEO_H
#define VIDEO_H

/*
              ======================
                 --- CONSTANTS ---
              ======================
*/

#define VID_MODE_TEXT 0x03             /* 80x25 16-COL TEXT MODE          */
#define VID_MODE_13H  0x13             /* 320x200 256 COL GFX MODE        */
#define VGA_MEMBASE   0xA0000L         /* BASE ADDRESS OF VGA MEM IN 13h  */
#define SCREEN_WIDTH  320              /* WIDTH OF SCREEN (IN PIXELS)     */
#define SCREEN_HEIGHT 200              /* HEIGHT OF SCREEN (IN PIXELS)    */

#define SCREEN_SIZE   (SCREEN_WIDTH * SCREEN_HEIGHT)

/*
              ======================
                 --- STRUCTURES  ---
              ======================
*/

typedef struct {

  unsigned char r, g, b;
  
} RGB;

/*
              ======================
                --- PROTOTYPES ---
              ======================
*/

void vid_set_mode(int mode);
void vid_set_pal(const RGB *palette);

void vid_close(void);
void vid_present(void);
void vid_clear_buffer(unsigned char color);

void vid_draw_px(int x, int y, unsigned char color);
void vid_draw_line(int x1, int y1, int x2, int y2, unsigned char color);
void vid_draw_rect(int x, int y, int width, int height, unsigned char color);
void vid_draw_rect_fill(int x, int y, int width, int height, unsigned char color);
void vid_draw_circle(int cX, int cY, int rad, unsigned char color);

#endif
