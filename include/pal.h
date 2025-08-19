/*
        ====================================

                      P A L . H
	            CCOMET PALETTE HEADER FILE
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

#ifndef  PAL_H
#define  PAL_H

#include "video.h"

static RGB default_vga_pal[16] = {

     {0, 0, 0},  {0, 0, 170},   {0, 170, 0},   {0, 170, 170},
   {170, 0, 0},  {170, 0, 170}, {170, 85, 0},  {170, 170, 170}, 
   {85, 85, 85}, {85, 85, 255}, {85, 255, 85}, {255, 255, 255}
  
};

#endif
