/*
        ====================================

                    T I M E R . H
	       CCOMET TIMER HEADER FILE
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

#ifndef 	TIMER_H
#define 	TIMER_H

/*
              ======================
                 --- CONSTANTS ---
              ======================
*/

#define 	PIT_FREQUENCY   1193182L
#define 	TARGET_FPS      60

/*
              ======================
                --- PROTOTYPES ---
              ======================
*/

void 		timer_init(void);
void 		timer_close(void);
unsigned long 	timer_get_ticks(void);
void 		timer_wait(unsigned long ticks);
void 		timer_wait_frame(void);

#endif
