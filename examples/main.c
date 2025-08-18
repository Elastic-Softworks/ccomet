#include <ccomet.h>
#include <stdio.h>

int main(int argc, char*argv[]) {

  (void)argc;
  (void)argv;

  printf("\nSETTING MODE TO 13h...\n");
  printf("PRESS ENTER TO CONTINUE...\n");

  getchar();
  
  vid_setmode(VID_MODE_13H);

  vid_putpix(10, 10, 1);
  vid_putpix(20, 10, 2);
  vid_putpix(30, 10, 4);
  vid_putpix(160, 100, 15);

  vid_present();

  long i;

  for (i = 0; i < 100000000; i++) {

    /* just a timer nothin to see here  */
    
  }

  vid_close();

  printf("WELCOME BACK TO TEXT MODE...!");
  
  return 0;
  
}
