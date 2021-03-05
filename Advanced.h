#ifndef ADVANCED_H_INCLUDED_
#define ADVANCED_H_INCLUDED_

#include "Constants.h"
#include "Image.h"

/* noise filter */
IMAGE *Noise(IMAGE *image, int percentage);

/* posterize filter */
IMAGE *Posterize(IMAGE *image, int rbits, int gbits, int bbits);

/* negative filter */
IMAGE *NegativeFilter(IMAGE *image);

/* crops image given the x y and L */
IMAGE *Square(IMAGE *image, int x,int y, int L);

/* controls the brightness and contrast */
IMAGE *BrightnessandContrast(IMAGE *image, int brightness,int contrast);

/* creates a new image that is bigger than the orignal */
IMAGE *Enlarge(IMAGE *image, int enlarge_percentage);

#endif /* ADVANCED_H_INCLUDED_ */

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
