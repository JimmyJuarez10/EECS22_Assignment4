#include "Advanced.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/* Add noise to an image */
IMAGE *Noise(IMAGE *image,int n)
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
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits)
{
	assert(image);
	int x, y;
	unsigned char temp_r,temp_g,temp_b;
	for(x=0; x< ImageWidth(image); x++) {
		for(y=0; y< ImageHeight(image); y++) {
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

	IMAGE *Square(IMAGE *image, int horizontalOffset,int verticalOffset, int L)
	{
		assert(image);
		int x , y; 

		IMAGE *temp = CreateImage(image -> W,image -> H);
		temp = CopyImage(image,temp);
		DeleteImage(image);
		IMAGE *newImage = CreateImage(L,L);

		for(x = 0; x < L; x++)
		{
			for(y=0; y < L; y++)
			{
				SetPixelR(newImage,x,y,GetPixelR(temp,x + horizontalOffset, y + verticalOffset));
				SetPixelG(newImage,x,y,GetPixelG(temp,x + horizontalOffset, y + verticalOffset));
				SetPixelB(newImage,x,y,GetPixelB(temp,x + horizontalOffset, y + verticalOffset));
			}
		}

		DeleteImage(temp);
		return newImage;
	}

	IMAGE *BrightnessandContrast(IMAGE *image, int brightness,int contrast)
	{
		assert(image);
		int x,y;
		int brightnessR,brightnessG,brightnessB;
		int contrastR,contrastG,contrastB;
		IMAGE *tempImage = CreateImage(image -> W, image -> H);
		tempImage = CopyImage(image,tempImage);

		double factor = (double) (259 * (contrast + 255)) / (double)(255 * (259 - contrast));

		for(x=0; x < image -> W; x++)
		{
			for(y=0; y < image -> H; y++)
			{
				brightnessR = GetPixelR(image,x,y) + brightness;
				brightnessG = GetPixelG(image,x,y) + brightness;
				brightnessB = GetPixelB(image,x,y) + brightness;

				contrastR = (int)(factor * (brightnessR - 128) + 128);
				contrastG = (int)(factor * (brightnessG - 128) + 128);
				contrastB = (int)(factor * (brightnessB - 128) + 128);

				SetPixelR(tempImage,x,y,(contrastR < 0) ? 0:(contrastR > 255) ? 255 : contrastR);
				SetPixelG(tempImage,x,y,(contrastG < 0) ? 0:(contrastG > 255) ? 255 : contrastG);
				SetPixelB(tempImage,x,y,(contrastB < 0) ? 0:(contrastB > 255) ? 255 : contrastB);
			} 
		}

		image = CopyImage(tempImage,image);
		DeleteImage(tempImage);
		return image;
	}

	IMAGE *Enlarge(IMAGE *image, int enlarge_percentage)
	{
		assert(image);
		double percentage = enlarge_percentage/100.00;
		int newWidth = (image -> W) * percentage;
		int newHeight = (image -> H) * percentage;
		IMAGE *originalCopy = CreateImage(image -> W,image -> H);
		originalCopy = CopyImage(image,originalCopy);
		DeleteImage(image);	
		image = CreateImage(newWidth,newHeight);
		for(int x=0;x < image -> W; x++)
		{
			for(int y=0; y < image -> H; y++)
			{
				SetPixelR(image, x, y,GetPixelR(originalCopy,x/percentage,y/percentage));		
				SetPixelG(image, x, y,GetPixelG(originalCopy,x/percentage,y/percentage));
				SetPixelB(image, x, y,GetPixelB(originalCopy,x/percentage,y/percentage));
			}
		}

		DeleteImage(originalCopy);
		return image;
	}
	/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
