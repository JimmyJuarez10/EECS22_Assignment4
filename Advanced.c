#include "Advanced.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* Add noise to an image */
IMAGE *Noise(int n,IMAGE *image)
{
	assert(image);
	int x, y, i;
	int num; /* number of noise added */
	int width = ImageWidth(image);
	int height = ImageHeight(image);
	num = ( n * height * width )/100;
	srand(time(NULL));

	for ( i = 0; i < num; i++ ) {
		x = ( (double)rand()/RAND_MAX )*(width-1);
		y = ( (double)rand()/RAND_MAX )*(height-1);
		SetPixelR(image,x,y,255);
		SetPixelG(image,x,y,255);
		SetPixelB(image,x,y,255);
	}

	return image;
}

/* make the image posterized */
IMAGE *Posterize(IMAGE *image, unsigned int rbits, unsigned int gbits, unsigned int bbits)
{
	assert(image);
	int x, y;
	unsigned char temp_r,temp_g,temp_b;
	for(x=0; x< image -> W; x++) {
		for(y=0; y< image -> H; y++) {
			unsigned char one = 1;
			int i;
			for(i=0; i<rbits-1; i++) {
				temp_r = GetPixelR(image,x,y);
				SetPixelR(image,x,y,(temp_r | one));
				one <<= 1;
			}
			one = ~one;
			temp_r = GetPixelR(image,x,y);
			SetPixelR(image,x,y,(temp_r & one));

			one = 1;
			for(i=0; i<gbits-1; i++) {
				temp_g = GetPixelG(image,x,y);
				SetPixelG(image,x,y,(temp_g | one));
				one <<= 1;
			}
			one = ~one;
			temp_g = GetPixelG(image,x,y);
			SetPixelG(image,x,y,(temp_g & one));

			one = 1;
			for(i=0; i<bbits-1; i++) {
				temp_b = GetPixelB(image,x,y);
				SetPixelB(image,x,y,(temp_b | one));
				one <<= 1;
			}
			one = ~one;
			temp_b = GetPixelB(image,x,y);
			SetPixelB(image,x,y,(temp_b & one));
		}
	}

	return image;
}

// Negative Filter
IMAGE *NegativeFilter(IMAGE *image)
{
	assert(image);
	unsigned char temp_r,temp_g,temp_b;

	for (int x = 0; x < image -> W; x++)
	{
		for (int y = 0; y < image -> H; y++)
		{
			temp_r = GetPixelR(image,x,y);
			temp_g = GetPixelG(image,x,y);
			temp_b = GetPixelB(image,x,y);
			
			SetPixelR(image,x,y,255-temp_r);
			SetPixelG(image,x,y,255-temp_g);
			SetPixelB(image,x,y,255-temp_b);
		}
	}
	return image;
}


/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
