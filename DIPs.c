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
            SetPixelB(image,x,y, (blue < 0) ? 0 : (blue > 255) ? 255 : blue);
	
	    redAndGreen = (unsigned char)(GetPixelB(image,x,y)*1.6);
	    SetPixelR(image,x,y,(redAndGreen < 0) ? 0 : (redAndGreen > 255) ? 255 : redAndGreen);
	    SetPixelG(image,x,y,(redAndGreen < 0) ? 0 : (redAndGreen > 255) ? 255 : redAndGreen);
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

    for (x = 0; x < image -> W; x++)
    {   for(y = 0; y < image -> H; y++)
        {   SetPixelR(tempImage,x,y,GetPixelR(image,x,y));
            SetPixelG(tempImage,x,y,GetPixelG(image,x,y));
            SetPixelB(tempImage,x,y,GetPixelB(image,x,y));
        }
    }

    for (x = 1; x < image->W - 1; x++)
    {   for (y = 1; y < image->H - 1; y++)
        {   
	    tmpr = 9 * GetPixelR(image,x,y) - GetPixelR(image,x-1,y-1) - GetPixelR(image,x-1,y) - GetPixelR(image,x-1,y+1) - GetPixelR(image,x,y-1) - GetPixelR(image,x,y+1) - GetPixelR(image,x+1,y-1) - GetPixelR(image,x+1,y) - GetPixelR(image,x+1,y+1);
            tmpg = 9 * GetPixelG(image,x,y) - GetPixelG(image,x-1,y-1) - GetPixelG(image,x-1,y) - GetPixelG(image,x-1,y+1) - GetPixelG(image,x,y-1) - GetPixelG(image,x,y+1) - GetPixelG(image,x+1,y-1) - GetPixelG(image,x+1,y) - GetPixelG(image,x+1,y+1);
            tmpb = 9 * GetPixelB(image,x,y) - GetPixelB(image,x-1,y-1) - GetPixelB(image,x-1,y) - GetPixelB(image,x-1,y+1) - GetPixelB(image,x,y-1) - GetPixelB(image,x,y+1) - GetPixelB(image,x+1,y-1) - GetPixelB(image,x+1,y) - GetPixelB(image,x+1,y+1);
	    
	    SetPixelR(tempImage,x,y,(tmpr > 255)?255:(tmpr < 0)?0:tmpr);
            SetPixelG(tempImage,x,y,(tmpg > 255)?255:(tmpg < 0)?0:tmpg);
            SetPixelB(tempImage,x,y,(tmpb > 255)?255:(tmpb < 0)?0:tmpb);

	    tmpr = tmpg = tmpb = 0;
        }
    }
    
    for (x = 0; x < image -> W; x++)
    {   for(y = 0; y < image -> H; y++)
        {   
	    SetPixelR(image,x,y,GetPixelR(tempImage,x,y));
            SetPixelG(image,x,y,GetPixelG(tempImage,x,y));
            SetPixelB(image,x,y,GetPixelB(tempImage,x,y));
        }
    }
    
    DeleteImage(tempImage);
    return image;
}

// edge detection function
IMAGE *Edge(IMAGE *image)
{   
    int             x, y, m, n, a, b;
    
    IMAGE *tempImage = CreateImage(image->W,image->H);

    for (x = 0; x < image -> W; x++)
    {   for(y = 0; y < image -> H; y++)
	{   SetPixelR(tempImage,x,y,GetPixelR(image,x,y));
	    SetPixelG(tempImage,x,y,GetPixelG(image,x,y));
	    SetPixelB(tempImage,x,y,GetPixelB(image,x,y));
	}
    }

    int sumR = 0;   /* sum of the intensity differences with neighbors */
    int sumG = 0;
    int sumB = 0;
    for (y = 1; y < image -> H - 1; y++){
        for (x = 1; x < image -> W - 1; x++){
            for (n = -1; n <= 1; n++){
                for (m = -1; m <= 1; m++) {
                    a = (x + m >= image -> W) ? image -> W - 1 : (x + m < 0) ? 0 : x + m;
                    b = (y + n >= image -> H) ? image -> H - 1 : (y + n < 0) ? 0 : y + n;
                    sumR += (GetPixelR(tempImage,x,y) - GetPixelR(tempImage,a,b));
                    sumG += (GetPixelG(tempImage,x,y) - GetPixelG(tempImage,a,b));
                    sumB += (GetPixelB(tempImage,x,y) - GetPixelB(tempImage,a,b));
                }
            }
            SetPixelR(image,x,y,(sumR > MAX_PIXEL) ? MAX_PIXEL: (sumR < MIN_PIXEL) ? MIN_PIXEL: sumR);
            SetPixelG(image,x,y,(sumG > MAX_PIXEL) ? MAX_PIXEL: (sumG < MIN_PIXEL) ? MIN_PIXEL: sumG);
            SetPixelB(image,x,y,(sumB > MAX_PIXEL) ? MAX_PIXEL: (sumB < MIN_PIXEL) ? MIN_PIXEL: sumB);
            sumR = sumG = sumB = 0;
        }
    }
    /* set all four borders to 0 */
    for (y = 0; y < image -> H; y++) {
        SetPixelR(image,0,y,0);
        SetPixelG(image,0,y,0);
        SetPixelB(image,0,y,0);
        SetPixelR(image,image->W-1,y,0);
        SetPixelG(image,image->W-1,y,0);
        SetPixelB(image,image->W-1,y,0);
    }
    for (x = 0; x < image -> W; x++) {
        SetPixelR(image,x,0,0);
        SetPixelG(image,x,0,0);
        SetPixelB(image,x,0,0);
        SetPixelR(image,x,image->H-1,0);
        SetPixelG(image,x,image->H-1,0);
        SetPixelB(image,x,image->H-1,0);
    }

    DeleteImage(tempImage);
    return image;
} 

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
