/* A simple hello world and rainbow example */
#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include "badge.h"

static const uint16_t colours[8] = {
   0xF800, /* Red */
   0xF300, /* Orange */
   0xF5E0, /* Yellow */
   0x07C0, /* Green */
   0x07FF, /* Cyan */
   0x001F, /* Blue */
   0x7817, /* Purple */
   0xFFFF  /* White */
};

void main(void)
{
   struct framebuf *buf = framebuf_alloc();
   int index;

   printf("Hello World!\n");

   for (index = 0; buf; index++) {
      uint16_t color;
      int i;

      /* Update the color. */
      color = colours[index % (sizeof(colours)/sizeof(colours[0]))];
      for (i = 0; i < (DISPLAY_VRES * DISPLAY_HWIDTH); i++) {
         buf->data[i] = color;
      }
      framebuf_render(buf);

      /* Do nothing for 1 second. */
      usleep(1000000);
   }
}