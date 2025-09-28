#include <dpmi.h>
#include <stdio.h>

#define VID_MODE_13H 0x13
#define VID_MODE_TEXT 0x03

void set_mode(int mode) {

  __dpmi_regs r;
  r.x.ax = mode;
  __dpmi_int(0x10, &r);
  
}

int main() {

  printf("\nSETTING MODE TO 13h...\n");
  set_mode(VID_MODE_13H);
  printf("MODE 13H SET! PRESS ANY KEY TO RETURN...!\n");
  getchar();
  set_mode(VID_MODE_13H);
  printf("RETURNED TO TEXT MODE...!\n");
  return 0;
  
}
