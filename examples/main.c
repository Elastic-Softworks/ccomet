#include  <ccomet.h>
#include  <stdio.h>
#include  <conio.h>

int main(int argc, char*argv[]) {

  (void)argc;
  (void)argv;

  printf("\nSETTING MODE TO 13h...\n");
  printf("PRESS ESC TO EXIT DURING DEMO...\n");
  printf("PRESS ENTER TO CONTINUE...\n");

  getchar();

  timer_init();
  pal_init();
  
  vid_set_mode(VID_MODE_13H);

  /*  demo loop - runs until ESC is pressed */
  
  while (1) {

    /* --- PIXEL DEMO ---             */

    pal_set_active(0);
    
    vid_clear_buffer(64);

    vid_draw_px(10, 10, 0);
    vid_draw_px(20, 10, 128);
    vid_draw_px(30, 10, 255);
    
    vid_present();

    timer_wait_frame();

    /* check for ESC key */
    
    if (kbhit() && getch() == 27) break;

    /* --- LINE DEMO --- */
    
    pal_set_active(2);    vid_clear_buffer(0);

    vid_draw_line(0,    0,  319,  199, 15);
    vid_draw_line(319,  0,    0,  199,  1);
    vid_draw_line(160, 10,  160,  190,  2);
    vid_draw_line(10,  100, 310,  100,  4);

    vid_present();

    timer_wait_frame();

    /* check for ESC key */
    
    if (kbhit() && getch() == 27) break;
    
    /* --- SHAPE DEMO --- */

    vid_clear_buffer(0);

    vid_draw_rect(50, 50, 100, 75, 15);

    vid_draw_rect_fill(200, 30, 80, 40, 4);

    vid_draw_circle(160, 130, 30, 2);

    vid_present();

    timer_wait_frame();

    /* check for ESC key */
    
    if (kbhit() && getch() == 27) break;

    /* --- PALETTE DEMO --- */

    /* show grayscale palette */

    pal_set_active(0);
    vid_clear_buffer(64);

    vid_draw_rect(50, 50,  100, 50, 128);
    vid_draw_rect(50, 110, 100, 50, 200);

    vid_present();
    timer_wait_frame();

    if (kbhit() && getch() == 27) break;

    /* show sepia palette */

    pal_set_active(1);
    vid_clear_buffer(64);

    vid_draw_rect(200,  50, 100,  50, 128);
    vid_draw_rect(200, 110, 100,  50, 200);

    vid_present();
    timer_wait_frame();

    if (kbhit() && getch() == 27) break;

    /* show VGA palette */

    pal_set_active(2);
    vid_clear_buffer(0);

    vid_draw_rect(  50,  50, 100,  50,  4);   /* red    */
    vid_draw_rect( 200,  50, 100,  50,  2);   /* green  */
    vid_draw_rect(  50, 110, 100,  50,  1);   /* blue   */
    vid_draw_rect( 200, 110, 100,  50, 14);   /* yellow */

    vid_present();
    timer_wait_frame();

    if (kbhit() && getch() == 27) break;

    pal_set_active(3);

    vid_clear_buffer(0);
    
    /* 16x16 grid showing all 256 colors */

    {
      int   color, x, y, grid_x, grid_y;

      int   square_size   = 12;      /* 12x12 pixels make a square */
      int   start_x       = 16;      /* 16 px padding from right */
      int   start_y       = 8;       /* 8 px padding from top */
      
      for (color = 0; color < 256; color++) {

        grid_x  = color % 16;           /* 16 colors per row */
        grid_y  = color / 16;           /* 16 rows total */
        
        x   = start_x + (grid_x * square_size);
        y   = start_y + (grid_y * square_size);
        
        /* draw filled rectangle for this color */

        vid_draw_rect_fill(x, y, square_size, square_size, color);
        
        /* draw a thin border around each square for visibility */

        if (color != 0) {  

          vid_draw_rect(x, y, square_size, square_size, 15); 

        }

      }

    }

    vid_present();
    timer_wait_frame();

    if (kbhit() && getch() == 27) break;

    /* --- DOOM PALETTE TEST --- */

    pal_set_active(4);

    vid_clear_buffer(0);
    
    /* 16x16 grid showing all 256 DOOM colors */

    {
      int   color, x, y, grid_x, grid_y;

      int   square_size   = 12;      /* 12x12 pixels make a square */
      int   start_x       = 16;      /* 16 px padding from right */
      int   start_y       = 8;       /* 8 px padding from top */
      
      for (color = 0; color < 256; color++) {

        grid_x  = color % 16;           /* 16 colors per row */
        grid_y  = color / 16;           /* 16 rows total */
        
        x   = start_x + (grid_x * square_size);
        y   = start_y + (grid_y * square_size);
        
        /* draw filled rectangle for this color */

        vid_draw_rect_fill(x, y, square_size, square_size, color);
        
        /* draw a thin border around each square for visibility */

        if (color != 0) {  

          vid_draw_rect(x, y, square_size, square_size, 15); 

        }

      }
      
    }

    vid_present();
    timer_wait_frame();

    if (kbhit() && getch() == 27) break;

    /* --- POLYGON DEMO --- */

    pal_set_active(2);
    vid_clear_buffer(0);

    {
      int triangle[] = {

        160, 50,
        100, 150,
        220, 150
        
      };

      vid_draw_polygon(triangle, 3, 4);
    }

    {
      int diamond[] = {

        50, 100,
        100, 50,
        150, 100,
        100, 150
        
      };

      vid_draw_polygon(diamond, 4, 2);
    }

    {
      int pentagon[] = {

        280, 70,
        310, 100,
        295, 140,
        265, 140,
        250, 100
        
      };

      vid_draw_polygon(pentagon, 5, 3);
    }

    vid_present();

    timer_wait_frame();

    /* check for ESC key */
    
    if (kbhit() && getch() == 27) break;

  } 
  
  /* --- DEMO CLOSE ---               */

  timer_close();
  vid_close();

  printf("WELCOME BACK TO TEXT MODE...!");
  
  return 0;
  
}
