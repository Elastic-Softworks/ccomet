/*
        ====================================

                      P A L . H
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

#ifndef  	PAL_H
#define  	PAL_H

#include 	"video.h"

/*
              ======================
                 --- CONSTANTS ---
              ======================
*/

#define		PAL_MAX 	8
#define		PAL_SIZE	256

/*
              ======================
                 --- STRUCTURES ---
              ======================
*/

typedef struct {

  RGB 	colors[PAL_SIZE];
  char 	name[32];
  int 	active;
  
} Pal;

/*
              ======================
                --- PROTOTYPES ---
              ======================
*/

void	pal_init(void);
int	pal_load(const RGB *pal_data, const char *name);
void	pal_set_active(int pal_id);
int	pal_get_active(void);
void	pal_apply_current(void);

/*
              ======================
                 --- PALETTES ---
              ======================
*/

extern	    RGB	pal_vga[256];
extern	    RGB	pal_gray[256];
extern	    RGB	pal_sepia[256];
extern	    RGB	pal_win256[256];

#endif

