#include <stdint.h>
#include "badge.h"

/* Sine table, generated by:
import math
for i in range(0,256,8):
   for j in range(i,i+8):
       val = math.sin(j * math.pi / 128) * 127
       print(" %4d," % int(val), end='')
   print("")
*/
const int8_t sin_table[256] = {
    0,    3,    6,    9,   12,   15,   18,   21,
   24,   27,   30,   33,   36,   39,   42,   45,
   48,   51,   54,   57,   59,   62,   65,   67,
   70,   73,   75,   78,   80,   82,   85,   87,
   89,   91,   94,   96,   98,  100,  102,  103,
  105,  107,  108,  110,  112,  113,  114,  116,
  117,  118,  119,  120,  121,  122,  123,  123,
  124,  125,  125,  126,  126,  126,  126,  126,
  127,  126,  126,  126,  126,  126,  125,  125,
  124,  123,  123,  122,  121,  120,  119,  118,
  117,  116,  114,  113,  112,  110,  108,  107,
  105,  103,  102,  100,   98,   96,   94,   91,
   89,   87,   85,   82,   80,   78,   75,   73,
   70,   67,   65,   62,   59,   57,   54,   51,
   48,   45,   42,   39,   36,   33,   30,   27,
   24,   21,   18,   15,   12,    9,    6,    3,
    0,   -3,   -6,   -9,  -12,  -15,  -18,  -21,
  -24,  -27,  -30,  -33,  -36,  -39,  -42,  -45,
  -48,  -51,  -54,  -57,  -59,  -62,  -65,  -67,
  -70,  -73,  -75,  -78,  -80,  -82,  -85,  -87,
  -89,  -91,  -94,  -96,  -98, -100, -102, -103,
 -105, -107, -108, -110, -112, -113, -114, -116,
 -117, -118, -119, -120, -121, -122, -123, -123,
 -124, -125, -125, -126, -126, -126, -126, -126,
 -127, -126, -126, -126, -126, -126, -125, -125,
 -124, -123, -123, -122, -121, -120, -119, -118,
 -117, -116, -114, -113, -112, -110, -108, -107,
 -105, -103, -102, -100,  -98,  -96,  -94,  -91,
  -89,  -87,  -85,  -82,  -80,  -78,  -75,  -73,
  -70,  -67,  -65,  -62,  -59,  -57,  -54,  -51,
  -48,  -45,  -42,  -39,  -36,  -33,  -30,  -27,
  -24,  -21,  -18,  -15,  -12,   -9,   -6,   -3,
};

static int8_t fp_sin(unsigned int val)
{
	return sin_table[val & 0xff];
}

static void delay(void)
{
	int i;
	for (i = 0; i < 100000; i++) {
		asm volatile("nop");
	}
}

int main(void)
{
	volatile uint16_t *pixbuf = (volatile uint16_t *)0x40020004;

	/* Pick some constants */
	unsigned int rscale = 1;
	unsigned int gscale = 2;
	unsigned int bscale = 5;

	unsigned int rstart = 555;
	unsigned int gstart = 666;
	unsigned int bstart = 777;

	int x, y;

	printf("Starting Northern Lights\n");

	/* Set the display pointer */
	DISPLAY_POINTER = 0x40020004;

	do {
		/* Redraw the frame */
		for (x = 0; x < DISPLAY_HRES; x++) {
			for (y = 0; y < DISPLAY_VRES; y++) {
				uint8_t red = (fp_sin((rstart + x*rscale) >> 4) * fp_sin((rstart + y*rscale) >> 4)) >> 7;
				uint8_t green = (fp_sin((gstart + x*gscale) >> 4) * fp_sin((gstart + y*gscale) >> 4)) >> 7;
				uint8_t blue = (fp_sin((bstart + x*bscale) >> 4) * fp_sin((bstart + y*bscale) >> 4)) >> 7;
				pixbuf[x + y * DISPLAY_HWIDTH] = ((red & 0x1F) << 11) + ((green & 0x3F) << 5) + (blue & 0x1F);
			}
		}

		/* Increment the animation */
		rstart += 11;
		gstart += 7;
		bstart += 5;

		/* Wait for a bit */
		delay();
	} while(1);

	return 1;
}
