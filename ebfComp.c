#include <stdio.h>
#include <stdlib.h>

#include "Errors.h"
#include "Image.h"
#include "Create.h"
#include "CommonErrors.h"

#define SUCCESS 0
#define BAD_ARGS 1
#define BAD_FILE 2
#define BAD_MAGIC_NUMBER 3
#define BAD_DIM 4
#define BAD_MALLOC 5
#define BAD_DATA 6
#define BAD_OUTPUT 7
#define MAGIC_NUMBER 0x6265
#define MAX_DIMENSION 262144
#define MIN_DIMENSION 1

int main(int argc, char **argv)
{ // main

    Image *image1 = (Image *)malloc(sizeof(Image));
    // open the input file in read mode
    FILE *inputFile1 = fopen(argv[1], "r");

    Image *image2 = (Image *)malloc(sizeof(Image));
    // open the input file in read mode
    FILE *inputFile2 = fopen(argv[2], "r");

    // validate that user has enter 2 arguments (plus the executable name)
    int checkarguments = CheckArguments(argc, "ebfComp");
    if (checkarguments == SUCCESS)
    {
        return SUCCESS;
    }
    else if (checkarguments == BAD_ARGS)
    {
        return BAD_ARGS;
    }

    // initialise the variable
    InitVar(image1);

    // check file opened successfully
    if (BadFileCheck(inputFile1, argv[1]) == BAD_FILE)
    {
        return BAD_FILE;
    }

    // initialise the magic number
    InitMagicNum(image1, inputFile1);

    // checking against the casted value due to endienness.
    if (CheckMagicNumber(image1, argv[1]) == BAD_MAGIC_NUMBER)
    {
        return BAD_MAGIC_NUMBER;
    }

    // check the dimensions
    if (CheckDimensions(image1, argv[1], inputFile1) == BAD_DIM)
    {
        return BAD_DIM;
    }

    // initialise the array
    int returned = InitArray(image1, inputFile1, argv[1]);
    if (returned != 100)
    {
        return returned;
    }

    // initialise the variables
    InitVar(image2);

    // check file opened successfully
    if (BadFileCheck(inputFile2, argv[2]) == BAD_FILE)
    {
        return BAD_FILE;
    }

    // initialise the magic number
    InitMagicNum(image2, inputFile2);

    // checking against the casted value due to endienness.
    if (CheckMagicNumber(image2, argv[2]) == BAD_MAGIC_NUMBER)
    {
        return BAD_MAGIC_NUMBER;
    }

    // check the dimensions
    if (CheckDimensions(image2, argv[2], inputFile2) == BAD_DIM)
    {
        return BAD_DIM;
    }

    // initialise the array
    InitArray(image2, inputFile2, argv[2]);

    // compare the data from the two files:
    if (CheckDifferent(image1, image2) == SUCCESS)
    {
        return SUCCESS;
    }

    // free allocated memory before exit
    free(image1->imageData);
    free(image2->imageData);

    // if we have not exited on different data, must be identical
    printf("IDENTICAL\n");
    return SUCCESS;
} // main()