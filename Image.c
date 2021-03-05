#include "Image.h"

unsigned int ImageWidth(const IMAGE *image)
{
    return image -> W;
}

unsigned int ImageHeight(const IMAGE *image)
{
    return image -> H;
}

unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y)
{
    assert(image);
    return image -> R[x + (y * ImageWidth(image))];
}

unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y)
{
    assert(image);
    return image -> G[x + (y * ImageWidth(image))];
}

unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y)
{
    assert(image);
    return image -> B[x + (y * ImageWidth(image))];
}

void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r )
{
    assert(image);
    image -> R[x+ (y * ImageWidth(image))] = r;
}

void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g)
{
    assert(image);
    image -> G[x+ (y * ImageWidth(image))] = g;
}

void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b)
{
    assert(image);
    image -> B[x+ (y * ImageWidth(image))] = b;
}


IMAGE *CreateImage(unsigned int Width, unsigned int Height)
{
    IMAGE *tempImage = malloc(sizeof(IMAGE));
    if(tempImage == NULL)
    {
        perror("Failure to create image memory.");
        exit(-1);
    }

    tempImage -> W = Width;
    tempImage -> H = Height;
    tempImage -> R = malloc(sizeof(unsigned char) * tempImage -> W * tempImage -> H);
    tempImage -> G = malloc(sizeof(unsigned char) * tempImage -> W * tempImage -> H);
    tempImage -> B = malloc(sizeof(unsigned char) * tempImage -> W * tempImage -> H); 

    return tempImage;
}

void DeleteImage(IMAGE *image)
{
    free(image -> B);    
    free(image -> G); 
    free(image -> R); 
    free(image);

   image = NULL; 
}


IMAGE *CopyImage(IMAGE *image,IMAGE *tempImage)
{
    int x,y;
    for (x = 0; x < image -> W; x++)
    {   for(y = 0; y < image -> H; y++)
        {   SetPixelR(tempImage,x,y,GetPixelR(image,x,y));
            SetPixelG(tempImage,x,y,GetPixelG(image,x,y));
            SetPixelB(tempImage,x,y,GetPixelB(image,x,y));
        }
    }

    return tempImage;
}

int CheckBounds(int value)
{
    return (value < 0) ? 0 : (value > 255) ? 255 : value;
}
