#include  <ccomet.h>
#include  <stdio.h>
#include  "pal.h"

int main(int argc, char*argv[]) {

  (void)argc;
  (void)argv;

  printf("\nSETTING MODE TO 13h...\n");
  printf("PRESS ENTER TO CONTINUE...\n");

  getchar();
  
  vid_set_mode(VID_MODE_13H);

  /* --- PIXEL DEMO ---             */

  RGB _grayscale_pal[256];

  int i;

  for (i = 0; i < 256; i++) {

    _grayscale_pal[i].r = i;
    _grayscale_pal[i].g = i;
    _grayscale_pal[i].b = i;
    
  }

  vid_set_pal(_grayscale_pal);
  
  vid_clear_buffer(64);

  vid_draw_px(10, 10, 0);
  vid_draw_px(20, 10, 128);
  vid_draw_px(30, 10, 255);
  
  vid_present();

  long j;

  /* TODO : MAKE A TIMER FUNCTION SO I DON'T
            HAVE TO DO THIS SHIT EVERY TIME LOL */
  
  for (j = 0; j < 100000000; j++) {

    /* just a timer nothin to see here
       just some fuckin pixels lol    */
    
  }

  /* --- LINE DEMO ---                */

  vid_set_pal(default_vga_pal);
  
  vid_clear_buffer(0);

  vid_draw_line(0,    0,  319,  199, 15);
  vid_draw_line(319,  0,    0,  199,  1);
  vid_draw_line(160, 10,  160,  190,  2);
  vid_draw_line(10,  100, 310,  100,  4);

  vid_present();

  for  (j = 0; j < 100000000; j++) {

    /* timerrrrrrrrrr                 */
    
  }
  
  /* --- DEMO CLOSE ---               */
  
  vid_close();

  printf("WELCOME BACK TO TEXT MODE...!");
  
  return 0;
  
}
