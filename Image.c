#include "Image.h"

unsigned char GetPixelR(const IMAGE *image, unsigned int x,  unsigned int y)
{
    assert(image);
    int width = image -> W;
    return image -> R[x + (y * width)];
}

unsigned char GetPixelG(const IMAGE *image, unsigned int x,  unsigned int y)
{
    assert(image);
    int width = image -> W;
    return image -> G[x + (y * width)];
}

unsigned char GetPixelB(const IMAGE *image, unsigned int x,  unsigned int y)
{
    assert(image);
    int width = image -> W;
    return image -> B[x + (y * width)];
}

void SetPixelR(IMAGE *image, unsigned int x, unsigned int y, unsigned char r )
{
    assert(image);
    int width = image -> W;
    image -> R[x+ (y * width)] = r;
}

void SetPixelG(IMAGE *image, unsigned int x, unsigned int y, unsigned char g)
{
    assert(image);
    int width = image -> W;
    image -> G[x+ (y * width)] = g;
}

void SetPixelB(IMAGE *image, unsigned int x, unsigned int y, unsigned char b)
{
    assert(image);
    int width = image -> W;
    image -> B[x+ (y * width)] = b;
}

unsigned int ImageWidth(const IMAGE *image)
{
    return image -> W;
}

unsigned int ImageHeight(const IMAGE *image)
{
    return image -> H;
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

