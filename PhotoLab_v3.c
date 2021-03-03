/*********************************************************************/
/* PhotoLab.c: homework assignment #3, for EECS 22                   */
/*                                                                   */
/* This is an "A" level representation of PhotoLab v1.               */
/* There are improvements that can be made, but this is considered   */
/* very good.                                                        */
/*                                                                   */
/* This solution (and all associated files) is for your reference    */
/* for this course and is copyright belongs to the authors below.    */
/* Reproduction or sharing of this code outside of this class is     */
/* prohibited except with the express written consent of the authors.*/
/*                                                                   */
/* Author: Mina Moghadam, Ned Beigipar, QV Dang                      */
/* Date:   11/8/2017	  08/17/2020    02/02/2021                   */
/*                                                                   */
/* Comments:                                                         */
/* added info about negative filter                                  */
/* Please use this template to submit your hw3.                      */
/*********************************************************************/

#include <stdio.h>
#include <string.h>

#include "DIPs.h"
#include "Advanced.h"
#include "FileIO.h"
#include "Constants.h"
#include "Test.h"
/*** function declarations ***/

/* print a menu */
void PrintMenu();

/* Test all functions */
void AutoTest(void);

int main()
{

#ifdef DEBUG
    AutoTest();
#else
    int rc;
    unsigned char R[WIDTH][HEIGHT];
    unsigned char B[WIDTH][HEIGHT];
    unsigned char G[WIDTH][HEIGHT];

    int option;            /* user input option */
    char fname[SLEN];        /* input file name */

    rc = 1;
    PrintMenu();
    scanf("%d", &option);

    /* Posterize() parameter */
    unsigned char rbits, gbits, bbits;

    /* Noise() parameter */
    int n;

    while (option != EXIT) {
        if (option == 1) {
            printf("Please input the file name to load: ");
            scanf("%s", fname);
            rc = LoadImage(fname, R, G, B);
        }

        /* menu item 2 - 14 requires image is loaded first */
        else if (option >= 2 && option < 9) {
            if (rc != SUCCESS)     {
                printf("No image is read.\n");
            }
            /* now image is loaded */
            else {
                switch (option) {
                    case 2:
                        printf("Please input the file name to save: ");
                        scanf("%s", fname);
                        SaveImage(fname, R, G, B);
                        break;
                    case 3:
                        Aging(R, G, B);
                        printf("\"Aging\" operation is done!\n");
                        break;
                    case 4:
                        Edge(R, G, B);
                        printf("\"Edge Detection\" operation is done!\n");
                        break;
                    case 5:
                        Sharpen(R, G, B);
                        printf("\"Sharpen\" operation is done!\n");
			break;
                    case 6:
                        printf("Please input noise percentage: ");
                        scanf("%d", &n);
                        Noise(n, R, G, B);
                        printf("\"Noise\" operation is done!\n");
                        break;
                    case 7:
                        printf("Enter the number of posterization bits for R chennel (1 to 8):");
                        scanf("%hhu", &rbits);
                        printf("Enter the number of posterization bits for G chennel (1 to 8):");
                        scanf("%hhu", &gbits);
                        printf("Enter the number of posterization bits for B chennel (1 to 8):");
                        scanf("%hhu", &bbits);
                        Posterize(R, G, B, rbits, gbits, bbits);
                        printf("\"Posterize\" operation is done!\n");
                        break;
                    case 8:
                        NegativeFilter(R, G, B);
                        printf("\"Negative Filter\" operation is done!\n");
                        break;
		    default:
                        break;

                }
            }
        }

        else if (option == 22) {
            AutoTest();
            rc = SUCCESS;    /* set returned code SUCCESS, since image is loaded */
        }
        else {
            printf("Invalid selection!\n");
        }

        /* Process finished, waiting for another input */
        PrintMenu();
        scanf("%d", &option);
    }
    printf("You exit the program.\n");
#endif

    return 0;
}


/*******************************************/
/* Function implementations should go here */
/*******************************************/

/* Menu */
void PrintMenu()
{

    printf("\n-------------------------\n");
    printf(" 1: Load a PPM image\n");
    printf(" 2: Save image in PPM and JPEG format\n");
    printf(" 3: Run aging\n");
    printf(" 4: Run edge detection filter\n");
    printf(" 5: Run sharpen filter\n");
    printf(" 6: Run noise filter\n");
    printf(" 7: Run posterize filter\n");
    printf(" 8: Run negative filter\n");
    printf("22: Test all functions\n");
    printf("99: Exit\n");
    printf("\n-------------------------\n");
    printf("Please make your choice: ");
}


/* auto test*/

void AutoTest(void) {
    unsigned char R[WIDTH][HEIGHT] , G[WIDTH][HEIGHT], B[WIDTH][HEIGHT];
    char fname[SLEN] = "pigeon";

    LoadImage(fname, R, G, B);
    Aging(R, G, B);
    SaveImage("aging", R, G, B);
#ifdef DEBUG
    printf("Aging tested!\n\n");
#endif

    LoadImage(fname, R, G, B);
    Sharpen(R, G, B);
    SaveImage("sharpen", R, G, B);
#ifdef DEBUG
    printf("Sharpen tested!\n\n");
#endif

    LoadImage(fname, R, G, B);
    Edge(R, G, B);
    SaveImage("edge", R, G, B);
#ifdef DEBUG
    printf("Edge tested!\n\n");
#endif

    LoadImage(fname, R, G, B);
    Noise(30, R, G, B);
    SaveImage("noise", R, G, B);
#ifdef DEBUG
    printf("Noise tested!\n\n");
#endif

    LoadImage(fname, R, G, B);
    Posterize(R, G, B, 7, 7, 7);
    SaveImage("posterize", R, G, B);
#ifdef DEBUG
    printf("Posterize tested!\n\n");
#endif

    LoadImage(fname, R, G, B);
    NegativeFilter(R, G, B);
    SaveImage("negative", R, G, B);
#ifdef DEBUG
    printf("Negative tested!\n\n");
#endif
}

/* vim: set tabstop=8 softtabstop=8 shiftwidth=8 noexpandtab : */
