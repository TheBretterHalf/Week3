#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//typedef uint8_t  BYTE;

//this is our 512 block of bytes stored in a block
//address + (sizeof(datatype)*index)
//BYTE *buffer = malloc(sizeof(BYTE)*512);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        //only one argument listed
        fprintf(stderr, "Please enter file to open.\n");
        return 1;
    }

    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    //Output File
    FILE *jpgs = NULL;

    //Buffer Array to control length of file
    unsigned char buffer[512];

    //filename array
    char filename[8];

    //counter for filename
    int counter = 0;

    //beginning of jpg
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {

    }
    //pull bytes and check those bytes
    //if byte1 ==
    //if byte2 ==
    //if byte3 ==
    int x = 0xea;
    //this if statement tests your fourth byte in recover.
    if (x <= 0xef && x >= 0xe0)
    {
        printf("the statement is 0xe0 and 0xef\n");
    }
    else
    {
        printf("the statement is false\n");
    }
    //at end of file fread gives back feof
    //while fread()!=feof
}
