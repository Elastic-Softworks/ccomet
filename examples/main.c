#include <ccomet.h>
#include <stdio.h>

int main(int argc, char*argv[]) {

  (void)argc;
  (void)argv;

  printf("\nSETTING MODE TO 13h...\n");
  printf("PRESS ENTER TO CONTINUE...\n");

  getchar();
  
  vid_set_mode(VID_MODE_13H);

  RGB _grayscale_pal[256];

  int i;

  for (i = 0; i < 256; i++) {

    _grayscale_pal[i].r = i;
    _grayscale_pal[i].g = i;
    _grayscale_pal[i].b = i;
    
  }

  vid_set_pal(_grayscale_pal);
  
  vid_clear_buffer(64);

  vid_putpix(10, 10, 0);
  vid_putpix(20, 10, 128);
  vid_putpix(30, 10, 255);
  
  vid_present();

  long j;

  for (j = 0; j < 100000000; j++) {

    /* just a timer nothin to see here  */
    
  }

  vid_close();

  printf("WELCOME BACK TO TEXT MODE...!");
  
  return 0;
  
}
