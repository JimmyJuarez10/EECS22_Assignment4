#include "Advanced.h"


#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* Add noise to an image */
void Noise(int n, unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	int x, y, i;
	int num; /* number of noise added */
	num = ( n*HEIGHT*WIDTH )/100;
	srand(time(NULL));

	for ( i = 0; i < num; i++ ) {
		x = ( (double)rand()/RAND_MAX )*(WIDTH-1);
		y = ( (double)rand()/RAND_MAX )*(HEIGHT-1);
		R[x][y] = 255;
		G[x][y] = 255;
		B[x][y] = 255;
	}
}

/* make the image posterized */
void Posterize(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT], unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
	int x, y;
	for(x=0; x<WIDTH; x++) {
		for(y=0; y<HEIGHT; y++) {
			unsigned char one = 1;
			int i;
			for(i=0; i<rbits-1; i++) {
				R[x][y] |= one;
				one <<= 1;
			}
			one = ~one;
			R[x][y] &= one;

			one = 1;
			for(i=0; i<gbits-1; i++) {
				G[x][y] |= one;
				one <<= 1;
			}
			one = ~one;
			G[x][y] &= one;

			one = 1;
			for(i=0; i<bbits-1; i++) {
				B[x][y] |= one;
				one <<= 1;
			}
			one = ~one;
			B[x][y] &= one;
		}
	}
}

// Negative Filter
void NegativeFilter(unsigned char R[WIDTH][HEIGHT], unsigned char G[WIDTH][HEIGHT], unsigned char B[WIDTH][HEIGHT])
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			R[x][y] = 255 - R[x][y];
			G[x][y] = 255 - G[x][y];
			B[x][y] = 255 - B[x][y];
		}
	}
}


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
