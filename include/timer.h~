/*
        ====================================

                    T I M E R . H
	       CCOMET TIMER HEADER FILE
           CG MOON / ELASTIC SOFTWORKS 2025
  
         ====================================
*/

#ifndef TIMER_H
#define TIMER_H

/*
              ======================
                 --- CONSTANTS ---
              ======================
*/

#define PIT_FREQUENCY 1193182L
#define TARGET_FPS    60

/*
              ======================
                --- PROTOTYPES ---
              ======================
*/

void timer_init(void);
void timer_close(void);
unsigned long timer_get_ticks(void);
void timer_wait(unsigned long ticks);
void timer_wait_frame(void);

#endif
