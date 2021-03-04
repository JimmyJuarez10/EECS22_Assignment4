######################################################################
# Makefile: Makefile for Assignment #3 EECS22 Fall 2017
#
# 02/02/21 QV Dang		 : updated for EECS22 Assignment 3 W'21
# 11/08/17 Mina Moghadam : updated for EECS22 Assignment 3 Fall 2017
# 10/08/16 Tim Schmidt   : updated for EECS22 Assignment 3 Fall 2016
# 10/17/15 Tim Schmidt   : updated for EECS22 Assignment 3 Fall 2015
# 10/21/14 Nistha Tandiya: updated for EECS22 Assignment 3 Fall 2014
# 10/27/13 Yasaman Samei : updated for EECS22 Assignment 3 Fall 2013
# 10/16/11 Weiwei Chen   : updated for EECS22 Assignment 3 Fall 2012
# 10/10/11 Weiwei Chen   : initial solution version
#
######################################################################


# design names
DESIGN = PhotoLab_v3 PhotoLabTest

#libs
LIBS   = libfilter.a libFileIO.a

CC     = gcc
DEBUG  = -DDEBUG # used for PhotoLabTest only; for normal program, need to add manually
CFLAGS = -ansi -std=c99 -Wall -c
LFLAGS = -ansi -std=c99 -Wall
AR     = ar rc
RANLIB = ranlib

IMAGES = edge.ppm \
         sharpen.ppm \
         posterize.ppm \
         aging.ppm \
		 negative.ppm \
		 noise.ppm

all: PhotoLab_v3 PhotoLabTest


########### generate object files ###########
#target to generate Test.o
Test.o: Test.h Test.c
	$(CC) $(CFLAGS) Test.c -o Test.c

#target to generate Image.o
Image.o: Image.h Image.c
	$(CC) $(CFLAGS) Image.c -o Image.o

#target to generate FileIO.o
FileIO.o: FileIO.h FileIO.c Constants.h
	$(CC) $(CFLAGS) FileIO.c -o FileIO.o

#target to generate DIPs.o
DIPs.o: DIPs.h DIPs.c Constants.h
	$(CC) $(CFLAGS) DIPs.c -o DIPs.o

#target to generate Advanced.o
Advanced.o: Advanced.h Advanced.c Constants.h
	$(CC) $(CFLAGS) Advanced.c -o Advanced.o

#target to generate PhotoLab.o
#debugging is optional for regular PhotoLab (must hardcode in)
PhotoLab.o: PhotoLab_v3.c DIPs.h Advanced.h FileIO.h Image.o Constants.h
	$(CC) $(CFLAGS) PhotoLab_v3.c -o PhotoLab.o

#target to generate FileIO_DEBUG.o
# hardcoding debug def because DEBUG version should always debug
PhotoLab_DEBUG.o: PhotoLab_v3.c DIPs.h Advanced.h FileIO.h Image.o Constants.h
	$(CC) $(CFLAGS) $(DEBUG) -c PhotoLab_v3.c -o PhotoLab_DEBUG.o


########### generate library files ###########

#target to generate libFilter.a
libfilter.a: DIPs.o Advanced.o
	$(AR) libfilter.a Advanced.o DIPs.o
	$(RANLIB) libfilter.a


########### generate executables ###########

#target to generate PhotoLab
PhotoLab_v3: PhotoLab.o FileIO.o Image.o libfilter.a
	$(CC) $(LFLAGS) PhotoLab.o FileIO.o Image.o -L. -lfilter -o PhotoLab_v3 -lm

#target to generate test
PhotoLabTest: PhotoLab_DEBUG.o FileIO.o Image.o libfilter.a
	$(CC) $(LFLAGS) PhotoLab_DEBUG.o FileIO.o Image.o -L. -lfilter -o PhotoLabTest -lm

#target to clean the directory
clean:
	rm -f *.o *.jpg $(DESIGN) $(IMAGES) $(LIBS)
	rm -f PhotoLab_v3
	rm -f PhotoLabTest

