#include "DIPs.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

/* Example of DIP */
/* age the image to make it look like old picture */
IMAGE *Aging(IMAGE *image)
{
    int x, y;
    int blue, redAndGreen;
    
    for( y = 0; y < image -> H; y++ ) {
        for( x = 0; x < image -> W; x++ ) {
	    blue = (GetPixelR(image,x,y) + GetPixelG(image,x,y) + GetPixelB(image,x,y))/5;
            SetPixelB(image,x,y,CheckBounds(blue));
	
	    redAndGreen = (unsigned char)(GetPixelB(image,x,y)*1.6);
	    SetPixelR(image,x,y,CheckBounds(redAndGreen));
	    SetPixelG(image,x,y,CheckBounds(redAndGreen));
	}
    }

    return image;
}

// Sharpen function
IMAGE *Sharpen(IMAGE *image)
{
    int x, y;
    int tmpr = 0, tmpg = 0, tmpb = 0;	
    IMAGE *tempImage = CreateImage(image->W,image->H);
    tempImage = CopyImage(image,tempImage);
   
    for (x = 1; x < ImageWidth(image) - 1; x++)
    {   for (y = 1; y < ImageHeight(image) - 1; y++)
        {   
	    tmpr = 9 * GetPixelR(image,x,y) - GetPixelR(image,x-1,y-1) - GetPixelR(image,x-1,y) - GetPixelR(image,x-1,y+1) - GetPixelR(image,x,y-1) - GetPixelR(image,x,y+1) - GetPixelR(image,x+1,y-1) - GetPixelR(image,x+1,y) - GetPixelR(image,x+1,y+1);
            tmpg = 9 * GetPixelG(image,x,y) - GetPixelG(image,x-1,y-1) - GetPixelG(image,x-1,y) - GetPixelG(image,x-1,y+1) - GetPixelG(image,x,y-1) - GetPixelG(image,x,y+1) - GetPixelG(image,x+1,y-1) - GetPixelG(image,x+1,y) - GetPixelG(image,x+1,y+1);
            tmpb = 9 * GetPixelB(image,x,y) - GetPixelB(image,x-1,y-1) - GetPixelB(image,x-1,y) - GetPixelB(image,x-1,y+1) - GetPixelB(image,x,y-1) - GetPixelB(image,x,y+1) - GetPixelB(image,x+1,y-1) - GetPixelB(image,x+1,y) - GetPixelB(image,x+1,y+1);
	    
	    SetPixelR(tempImage,x,y,CheckBounds(tmpr));
	    SetPixelG(tempImage,x,y,CheckBounds(tmpg));
            SetPixelB(tempImage,x,y,CheckBounds(tmpb));

	    tmpr = tmpg = tmpb = 0;
        }
    }
    
    image = CopyImage(tempImage,image); 
    DeleteImage(tempImage);
    return image;
}

// edge detection function
IMAGE *EdgeDetection(IMAGE *image)
{   
    int x, y, m, n, a, b;
    int imageHeight = ImageHeight(image);
    int imageWidth = ImageWidth(image);

    int sumR = 0;   /* sum of the intensity differences with neighbors */
    int sumG = 0;
    int sumB = 0;

    IMAGE *tempImage = CreateImage(image->W,image->H);
    tempImage = CopyImage(image,tempImage);
        for (y = 1; y < imageHeight - 1; y++){
        for (x = 1; x < imageWidth - 1; x++){
            for (n = -1; n <= 1; n++){
                for (m = -1; m <= 1; m++) {
                    a = (x + m >= imageWidth) ? imageWidth - 1 : (x + m < 0) ? 0 : x + m;
                    b = (y + n >= imageHeight) ? imageHeight - 1 : (y + n < 0) ? 0 : y + n;
                    sumR += (GetPixelR(tempImage,x,y) - GetPixelR(tempImage,a,b));
                    sumG += (GetPixelG(tempImage,x,y) - GetPixelG(tempImage,a,b));
                    sumB += (GetPixelB(tempImage,x,y) - GetPixelB(tempImage,a,b));
                }
            }
            SetPixelR(image,x,y,CheckBounds(sumR));
            SetPixelG(image,x,y,CheckBounds(sumG));
            SetPixelB(image,x,y,CheckBounds(sumB));
            sumR = sumG = sumB = 0;
        }
    }
    /* set all four borders to 0 */
    for (y = 0; y < imageHeight; y++) {
        SetPixelR(image,0,y,0);
        SetPixelG(image,0,y,0);
        SetPixelB(image,0,y,0);
        SetPixelR(image,imageWidth-1,y,0);
        SetPixelG(image,imageWidth-1,y,0);
        SetPixelB(image,imageWidth-1,y,0);
    }
    for (x = 0; x < imageWidth; x++) {
        SetPixelR(image,x,0,0);
        SetPixelG(image,x,0,0);
        SetPixelB(image,x,0,0);
        SetPixelR(image,x,imageHeight-1,0);
        SetPixelG(image,x,imageHeight-1,0);
        SetPixelB(image,x,imageHeight-1,0);
    }

    DeleteImage(tempImage);
    return image;
} 

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
